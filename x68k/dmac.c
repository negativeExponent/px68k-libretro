/*
 *  DMAC.C - DMAコントローラ（HD63450）
 *  ToDo : もっと奇麗に ^^;
 */

#include "../x11/common.h"

#include "dmac.h"
#include "adpcm.h"
#include "fdc.h"
#include "irqh.h"
#include "mercury.h"
#include "sasi.h"
#include "x68kmemory.h"

dmac_ch DMA[4];

static int DMA_IntCH           = 0;
static int DMA_LastInt         = 0;
static int (*IsReady[4])(void) = { 0, 0, 0, 0 };

static const int MACUpdateTable[8][4] = {
	{ 0, 1, -1, 0 }, /* 8bit port, byte transfer      */
	{ 0, 2, -2, 0 }, /* 8bit port, word transfer      */
	{ 0, 4, -4, 0 }, /* 8bit port, longword transfer  */
	{ 0, 1, -1, 0 }, /* 8bit port, packed bytes       */
	{ 0, 1, -1, 0 }, /* 16bit port, byte transfer     */
	{ 0, 2, -2, 0 }, /* 16bit port, word transfer     */
	{ 0, 4, -4, 0 }, /* 16bit port, longword transfer */
	{ 0, 1, -1, 0 }  /* 16bit port, packed bytes      */
};

static const int DACUpdateTable[8][4] = {
	{ 0, 2, -2, 0 }, /* 8bit port, byte transfer      */
	{ 0, 4, -4, 0 }, /* 8bit port, word transfer      */
	{ 0, 8, -8, 0 }, /* 8bit port, longword transfer  */
	{ 0, 2, -2, 0 }, /* 8bit port, packed bytes       */
	{ 0, 1, -1, 0 }, /* 16bit port, byte transfer     */
	{ 0, 2, -2, 0 }, /* 16bit port, word transfer     */
	{ 0, 4, -4, 0 }, /* 16bit port, longword transfer */
	{ 0, 1, -1, 0 }  /* 16bit port, packed bytes      */
};

static int32_t FASTCALL DMA_Int(int32_t irq);

#define DMAINT(ch)                                                                                                     \
	if (DMA[ch].CCR & 0x08)                                                                                            \
	{                                                                                                                  \
		DMA_IntCH |= (1 << ch);                                                                                        \
		IRQH_Int(3, &DMA_Int);                                                                                         \
	}
#define DMAERR(ch, err)                                                                                                \
	{                                                                                                                  \
		DMA[ch].CER = err;                                                                                             \
		DMA[ch].CSR |= 0x10;                                                                                           \
		DMA[ch].CSR &= 0xf7;                                                                                           \
		DMA[ch].CCR &= 0x7f;                                                                                           \
		DMAINT(ch)                                                                                                     \
	}

static int DMA_DummyIsReady(void)
{
	return 0;
}

static void DMA_SetReadyCB(int ch, int (*func)(void))
{
	if ((ch >= 0) && (ch <= 3))
		IsReady[ch] = func;
}

static int32_t FASTCALL DMA_Int(int32_t irq)
{
	int32_t ret = IRQ_DEFAULT_VECTOR;
	int bit     = 0;
	int i       = DMA_LastInt;

	IRQH_IRQCallBack(irq);
	if (irq == 3)
	{
		do
		{
			bit = 1 << i;
			if (DMA_IntCH & bit)
			{
				if ((DMA[i].CSR) & 0x10)
					ret = ((int32_t)(DMA[i].EIV));
				else
					ret = ((int32_t)(DMA[i].NIV));
				DMA_IntCH &= ~bit;
				break;
			}
			i = (i + 1) & 3;
		} while (i != DMA_LastInt);
	}
	DMA_LastInt = i;
	if (DMA_IntCH)
		IRQH_Int(3, &DMA_Int);
	return ret;
}

static void FASTCALL SetCCR(int ch, uint8_t data)
{
	uint8_t old = DMA[ch].CCR;

	DMA[ch].CCR = (data & 0xef) |
	              (DMA[ch].CCR & 0x80); /* CCRのSTRは書き込みでは落とせない */

	if ((data & 0x10) && (DMA[ch].CCR & 0x80))
	{
		/* Software Abort */
		DMAERR(ch, 0x11)
		return;
	}

	if (data & 0x20) /* Halt */
	{
		/* 本来は落ちるはず。Nemesis'90で調子悪いので… */
		/* DMA[ch].CSR &= 0xf7; */
		return;
	}

	if (data & 0x80)
	{
		/* 動作開始 */
		if (old & 0x20)
		{
			/* Halt解除 */
			DMA[ch].CSR |= 0x08;
			DMA_Exec(ch);
		}
		else
		{
			if (DMA[ch].CSR & 0xf8)
			{
				/* タイミングエラー */
				DMAERR(ch, 0x02)
				return;
			}
			DMA[ch].CSR |= 0x08;
			if ((DMA[ch].OCR & 8) /*&&(!DMA[ch].MTC)*/)
			{
				/* アレイ／リンクアレイチェイン */
				DMA[ch].MAR = dma_readmem24_dword(DMA[ch].BAR) & 0xffffff;
				DMA[ch].MTC = dma_readmem24_word(DMA[ch].BAR + 4) & 0xffff;
				if (DMA[ch].OCR & 4)
				{
					DMA[ch].BAR = dma_readmem24_dword(DMA[ch].BAR + 6);
				}
				else
				{
					DMA[ch].BAR += 6;
					if (!DMA[ch].BTC)
					{
						/* これもカウントエラー */
						DMAERR(ch, 0x0f)
						return;
					}
				}
			}
			if (!DMA[ch].MTC)
			{
				/* カウントエラー */
				DMAERR(ch, 0x0d)
				return;
			}
			DMA[ch].CER = 0x00;
			DMA_Exec(ch); /* 開始直後にカウンタを見て動作チェックする場合があるので、少しだけ実行しておく */
		}
	}

	if ((data & 0x40) && (!DMA[ch].MTC))
	{
		/* Continuous Op. */
		if (DMA[ch].CCR & 0x80)
		{
			if (DMA[ch].CCR & 0x40)
			{
				DMAERR(ch, 0x02)
			}
			else if (DMA[ch].OCR & 8)
			{
				/* アレイ／リンクアレイチェイン */
				DMAERR(ch, 0x01)
			}
			else
			{
				DMA[ch].MAR = DMA[ch].BAR;
				DMA[ch].MTC = DMA[ch].BTC;
				DMA[ch].CSR |= 0x08;
				DMA[ch].BAR = 0;
				DMA[ch].BTC = 0;
				if (!DMA[ch].MAR)
				{
					DMA[ch].CSR |=
					    0x40; /* ブロック転送終了ビット／割り込み ? */
					DMAINT(ch)
					return;
				}
				else if (!DMA[ch].MTC)
				{
					DMAERR(ch, 0x0d)
					return;
				}
				DMA[ch].CCR &= 0xbf;
				DMA_Exec(ch);
			}
		}
		else
		{
			/* 非Active時のCNTビットは動作タイミングエラー */
			DMAERR(ch, 0x02)
		}
	}
}

uint8_t FASTCALL DMA_Read(uint32_t adr)
{
	int off = adr & 0x3f;
	int ch = (adr >> 6) & 0x03;

	if (adr >= 0xe84100)
		return 0; /* ばすえらー？ */

	switch (off)
	{
	case 0x00:
		if ((ch == 2) && (off == 0))
		{
#ifndef NO_MERCURY
			DMA[ch].CSR = (DMA[ch].CSR & 0xfe) | (Mcry_LRTiming & 1);
#else
			DMA[ch].CSR = (DMA[ch].CSR & 0xfe);
			/* Mcry_LRTiming ^= 1; */
#endif
		}
		return DMA[ch].CSR;

	case 0x01:
		return DMA[ch].CER;

	case 0x04:
		return DMA[ch].DCR;

	case 0x05:
		return DMA[ch].OCR;

	case 0x06:
		return DMA[ch].SCR;

	case 0x07:
		return DMA[ch].CCR;

	case 0x0a:
		return (DMA[ch].MTC >> 8) & 0xff;
	case 0x0b:
		return DMA[ch].MTC & 0xff;

	case 0x0c:
		return 0;
	case 0x0d:
		return (DMA[ch].MAR >> 16) & 0xff;
	case 0x0e:
		return (DMA[ch].MAR >> 8) & 0xff;
	case 0x0f:
		return DMA[ch].MAR & 0xff;

	case 0x14:
		return 0;
	case 0x15:
		return (DMA[ch].DAR >> 16) & 0xff;
	case 0x16:
		return (DMA[ch].DAR >> 8) & 0xff;
	case 0x17:
		return DMA[ch].DAR & 0xff;

	case 0x1a:
		return (DMA[ch].BTC >> 8) & 0xff;
	case 0x1b:
		return DMA[ch].BTC & 0xff;

	case 0x1c:
		return 0;
	case 0x1d:
		return (DMA[ch].BAR >> 16) & 0xff;
	case 0x1e:
		return (DMA[ch].BAR >> 8) & 0xff;
	case 0x1f:
		return DMA[ch].BAR & 0xff;

	case 0x25:
		return DMA[ch].NIV;

	case 0x27:
		return DMA[ch].EIV;

	case 0x29:
		return DMA[ch].MFC;

	case 0x2d:
		return DMA[ch].CPR;

	case 0x31:
		return DMA[ch].DFC;

	case 0x39:
		return DMA[ch].BFC;

	case 0x3f:
		/* only return for channel 3 */
		if (ch == 3) return DMA[ch].GCR;
	}

	return 0xff;
}

void FASTCALL DMA_Write(uint32_t adr, uint8_t data)
{
	int off = adr & 0x3f;
	int ch = (adr >> 6) & 0x03;

	if (adr >= 0xe84100)
		return; /* ばすえらー？ */

	switch (off)
	{
	case 0x00:
		DMA[ch].CSR &= ((~data) | 0x09);
		break;

	case 0x01:
		DMA[ch].CER &= (~data);
		break;

	case 0x04:
		DMA[ch].DCR = data;
		break;

	case 0x05:
		DMA[ch].OCR = data;
		break;

	case 0x06:
		DMA[ch].SCR = data;
		break;

	case 0x07:
		SetCCR(ch, data);
		break;

	case 0x0a:
		DMA[ch].MTC &= 0x00ff;
		DMA[ch].MTC |= (data << 8);
		break;
	case 0x0b:
		DMA[ch].MTC &= 0xff00;
		DMA[ch].MTC |= data;
		break;

	case 0x0c:
		break;
	case 0x0d:
		DMA[ch].MAR &= 0x0000ffff;
		DMA[ch].MAR |= (data << 16);
		break;
	case 0x0e:
		DMA[ch].MAR &= 0x00ff00ff;
		DMA[ch].MAR |= (data << 8);
		break;
	case 0x0f:
		DMA[ch].MAR &= 0x00ffff00;
		DMA[ch].MAR |= data;
		break;

	case 0x14:
		break;
	case 0x15:
		DMA[ch].DAR &= 0x0000ffff;
		DMA[ch].DAR |= (data << 16);
		break;
	case 0x16:
		DMA[ch].DAR &= 0x00ff00ff;
		DMA[ch].DAR |= (data << 8);
		break;
	case 0x17:
		DMA[ch].DAR &= 0x00ffff00;
		DMA[ch].DAR |= data;
		break;

	case 0x1a:
		DMA[ch].BTC &= 0x00ff;
		DMA[ch].BTC |= (data << 8);
		break;
	case 0x1b:
		DMA[ch].BTC &= 0xff00;
		DMA[ch].BTC |= data;
		break;

	case 0x1c:
		break;
	case 0x1d:
		DMA[ch].BAR &= 0x0000ffff;
		DMA[ch].BAR |= (data << 16);
		break;
	case 0x1e:
		DMA[ch].BAR &= 0x00ff00ff;
		DMA[ch].BAR |= (data << 8);
		break;
	case 0x1f:
		DMA[ch].BAR &= 0x00ffff00;
		DMA[ch].BAR |= data;
		break;

	case 0x25:
		DMA[ch].NIV = data;
		break;

	case 0x27:
		DMA[ch].EIV = data;
		break;

	case 0x29:
		DMA[ch].MFC = data;
		break;

	case 0x2d:
		DMA[ch].CPR = data;
		break;

	case 0x31:
		DMA[ch].DFC = data;
		break;

	case 0x39:
		DMA[ch].BFC = data;
		break;

	case 0x3f:
		if (ch == 3) DMA[ch].GCR = data;
		break;
	}
}

int FASTCALL DMA_Exec(int ch)
{
	while ((DMA[ch].CSR & 0x08) && (!(DMA[ch].CCR & 0x20)) &&
	       (!(DMA[ch].CSR & 0x80)) && (DMA[ch].MTC) &&
	       (((DMA[ch].OCR & 3) != 2) || (IsReady[ch]())))
	{
		uint32_t data     = 0;
		uint32_t dma_type = ((DMA[ch].OCR >> 4) & 3) + ((DMA[ch].DCR >> 1) & 4);

		BusErrFlag = 0;
		switch (dma_type)
		{
		case 0:
		case 3:
		case 7:
			if (DMA[ch].OCR & 0x80) /* Device->Memory */
			{
				data = dma_readmem24(DMA[ch].DAR);
				dma_writemem24(DMA[ch].MAR, (uint8_t)data);
			}
			else                   /* Memory->Device */
			{
				data = dma_readmem24(DMA[ch].MAR);
				dma_writemem24(DMA[ch].DAR, (uint8_t)data);
			}
			break;

		case 1:
			if (DMA[ch].OCR & 0x80)
			{
				data  = ((uint8_t)dma_readmem24(DMA[ch].DAR)) << 8;
				data |= (uint8_t)dma_readmem24(DMA[ch].DAR + 2);
				dma_writemem24_word(DMA[ch].MAR, data);
			}
			else
			{
				data = dma_readmem24_word(DMA[ch].MAR);
				dma_writemem24(DMA[ch].DAR,     (uint8_t)(data >> 8));
				dma_writemem24(DMA[ch].DAR + 2, (uint8_t)data);
			}
			break;

		case 2:
			if (DMA[ch].OCR & 0x80)
			{
				data  = ((uint8_t)dma_readmem24(DMA[ch].DAR)) << 24;
				data |= ((uint8_t)dma_readmem24(DMA[ch].DAR + 2)) << 16;
				data |= ((uint8_t)dma_readmem24(DMA[ch].DAR + 4)) << 8;
				data |= (uint8_t)dma_readmem24(DMA[ch].DAR + 6);
				dma_writemem24_word(DMA[ch].MAR,     (uint16_t)(data >> 16));
				dma_writemem24_word(DMA[ch].MAR + 2, (uint16_t)data);
			}
			else
			{
				data  = ((uint16_t)dma_readmem24_word(DMA[ch].MAR)) << 16;
				data |= (uint16_t)dma_readmem24_word(DMA[ch].MAR + 2);
				dma_writemem24(DMA[ch].DAR,     (uint8_t)(data >> 24));
				dma_writemem24(DMA[ch].DAR + 2, (uint8_t)(data >> 16));
				dma_writemem24(DMA[ch].DAR + 4, (uint8_t)(data >> 8));
				dma_writemem24(DMA[ch].DAR + 6, (uint8_t)data);
			}
			break;

		case 4:
			if (DMA[ch].OCR & 0x80)
			{
				data = dma_readmem24(DMA[ch].DAR);
				dma_writemem24(DMA[ch].MAR, data);
			}
			else
			{
				data = dma_readmem24(DMA[ch].MAR);
				dma_writemem24(DMA[ch].DAR, data);
			}
			break;

		case 5:
			if (DMA[ch].OCR & 0x80)
			{
				data = dma_readmem24_word(DMA[ch].DAR);
				dma_writemem24_word(DMA[ch].MAR, data);
			}
			else
			{
				data = dma_readmem24_word(DMA[ch].MAR);
				dma_writemem24_word(DMA[ch].DAR, data);
			}
			break;

		case 6:
			if (DMA[ch].OCR & 0x80)
			{
				data = dma_readmem24_dword(DMA[ch].DAR);
				dma_writemem24_dword(DMA[ch].MAR, data);
			}
			else
			{
				data = dma_readmem24_dword(DMA[ch].MAR);
				dma_writemem24_dword(DMA[ch].DAR, data);
			}
			break;
		}

		/* transfer error check (bus error/address error) */
		if (BusErrFlag)
		{
			switch (BusErrFlag)
			{
			case 1:                     /* BusErr/Read */
				if (DMA[ch].OCR & 0x80) /* Device->Memory */
					DMAERR(ch, 0x0a)
				else
					DMAERR(ch, 0x09)
				break;
			case 2:                     /* BusErr/Write */
				if (DMA[ch].OCR & 0x80) /* Device->Memory */
					DMAERR(ch, 0x09)
				else
					DMAERR(ch, 0x0a)
				break;
			case 3:                     /* AdrErr/Read */
				if (DMA[ch].OCR & 0x80) /* Device->Memory */
					DMAERR(ch, 0x06)
				else
					DMAERR(ch, 0x05)
				break;
			case 4:                     /* BusErr/Write */
				if (DMA[ch].OCR & 0x80) /* Device->Memory */
					DMAERR(ch, 0x05)
				else
					DMAERR(ch, 0x06)
				break;
			}

			BusErrFlag = 0;

			/* exit before addres update */
			break;
		}

		DMA[ch].MAR += MACUpdateTable[dma_type][(DMA[ch].SCR >> 2) & 3];	/* mac */
		DMA[ch].MAR &= 0xffffff;
		DMA[ch].DAR += DACUpdateTable[dma_type][DMA[ch].SCR & 3];			/* dac */
		DMA[ch].DAR &= 0xffffff;

		DMA[ch].MTC--;
		if (!DMA[ch].MTC)
		{
			/* 指定分のバイト数転送終了 */
			if (DMA[ch].OCR & 8)
			{
				/* チェインモードで動いている場合 */
				if (DMA[ch].OCR & 4)
				{
					/* リンクアレイチェイン */
					if (DMA[ch].BAR)
					{
						DMA[ch].MAR = dma_readmem24_dword(DMA[ch].BAR);
						DMA[ch].MTC = dma_readmem24_word(DMA[ch].BAR + 4) & 0xffff;
						DMA[ch].BAR = dma_readmem24_dword(DMA[ch].BAR + 6);
						if (BusErrFlag)
						{
							if (BusErrFlag == 1)
								DMAERR(ch, 0x0b)
							else
								DMAERR(ch, 0x07)
							BusErrFlag = 0;
							break;
						}
						else if (!DMA[ch].MTC)
						{
							DMAERR(ch, 0x0d)
							break;
						}
					}
				}
				else
				{
					/* アレイチェイン */
					DMA[ch].BTC--;
					if (DMA[ch].BTC)
					{
						/* 次のブロックがある */
						DMA[ch].MAR = dma_readmem24_dword(DMA[ch].BAR);
						DMA[ch].MTC = dma_readmem24_word(DMA[ch].BAR + 4) & 0xffff;
						DMA[ch].BAR += 6;
						if (BusErrFlag)
						{
							if (BusErrFlag == 1)
								DMAERR(ch, 0x0b)
							else
								DMAERR(ch, 0x07)
							BusErrFlag = 0;
							break;
						}
						else if (!DMA[ch].MTC)
						{
							DMAERR(ch, 0x0d)
							break;
						}
					}
				}
			}
			else
			{
				/* 通常モード（1ブロックのみ）終了 */
				if (DMA[ch].CCR & 0x40)
				{                        /* Countinuous動作中 */
					DMA[ch].CSR |= 0x40; /* ブロック転送終了ビット／割り込み */
					DMAINT(ch)
					if (DMA[ch].BAR)
					{
						DMA[ch].MAR = DMA[ch].BAR;
						DMA[ch].MTC = DMA[ch].BTC;
						DMA[ch].CSR |= 0x08;
						DMA[ch].BAR = 0x00;
						DMA[ch].BTC = 0x00;
						if (!DMA[ch].MTC)
						{
							DMAERR(ch, 0x0d)
							break;
						}
						DMA[ch].CCR &= 0xbf;
					}
				}
			}
			if (!DMA[ch].MTC)
			{
				DMA[ch].CSR |= 0x80;
				DMA[ch].CSR &= 0xf7;
				DMAINT(ch)
			}
		}
		if ((DMA[ch].OCR & 3) != 1)
			break;
	}
	return 0;
}

void DMA_Init(void)
{
	int i;

	DMA_IntCH   = 0;
	DMA_LastInt = 0;
	for (i = 0; i < 4; i++)
	{
		memset(&DMA[i], 0, sizeof(dmac_ch));
		DMA[i].CSR = 0;
		DMA[i].CCR = 0;
		DMA_SetReadyCB(i, DMA_DummyIsReady);
	}
	DMA_SetReadyCB(0, FDC_IsDataReady);
	DMA_SetReadyCB(1, SASI_IsReady);
#ifndef NO_MERCURY
	DMA_SetReadyCB(2, Mcry_IsReady);
#endif
	DMA_SetReadyCB(3, ADPCM_IsReady);
}
