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

uint8_t FASTCALL DMA_Read(uint32_t adr)
{
	uint8_t ret = 0;
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
			Mcry_LRTiming ^= 1;
#endif
		}
		ret = DMA[ch].CSR;
		break;

	case 0x01:
		ret = DMA[ch].CER;
		break;

	case 0x04:
		ret = DMA[ch].DCR;
		break;

	case 0x05:
		ret = DMA[ch].OCR;
		break;

	case 0x06:
		ret = DMA[ch].SCR;
		break;

	case 0x07:
		ret = DMA[ch].CCR;
		break;

	case 0x0a:
		ret = (DMA[ch].MTC >> 8) & 0xff;
		break;
	case 0x0b:
		ret = DMA[ch].MTC & 0xff;
		break;

	case 0x0c:
		ret = (DMA[ch].MAR >> 24) & 0xff;
		break;
	case 0x0d:
		ret = (DMA[ch].MAR >> 16) & 0xff;
		break;
	case 0x0e:
		ret = (DMA[ch].MAR >> 8) & 0xff;
		break;
	case 0x0f:
		ret = DMA[ch].MAR & 0xff;
		break;

	case 0x14:
		ret = (DMA[ch].DAR >> 24) & 0xff;
		break;
	case 0x15:
		ret = (DMA[ch].DAR >> 16) & 0xff;
		break;
	case 0x16:
		ret = (DMA[ch].DAR >> 8) & 0xff;
		break;
	case 0x17:
		ret = DMA[ch].DAR & 0xff;
		break;

	case 0x1a:
		ret = (DMA[ch].BTC >> 8) & 0xff;
		break;
	case 0x1b:
		ret = DMA[ch].BTC & 0xff;
		break;

	case 0x1c:
		ret = (DMA[ch].BAR >> 24) & 0xff;
		break;
	case 0x1d:
		ret = (DMA[ch].BAR >> 16) & 0xff;
		break;
	case 0x1e:
		ret = (DMA[ch].BAR >> 8) & 0xff;
		break;
	case 0x1f:
		ret = DMA[ch].BAR & 0xff;
		break;

	case 0x25:
		ret = DMA[ch].NIV;
		break;

	case 0x27:
		ret = DMA[ch].EIV;
		break;

	case 0x29:
		ret = DMA[ch].MFC;
		break;

	case 0x2d:
		ret = DMA[ch].CPR;
		break;

	case 0x31:
		ret = DMA[ch].DFC;
		break;

	case 0x39:
		ret = DMA[ch].BFC;
		break;

	case 0x3f:
		ret = DMA[ch].GCR;
		break;
	}

	return ret;
}

void FASTCALL DMA_Write(uint32_t adr, uint8_t data)
{
	int off = adr & 0x3f;
	int ch = (adr >> 6) & 0x03;
	uint8_t old = 0;

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
		old         = DMA[ch].CCR;
		DMA[ch].CCR = (data & 0xef) | (DMA[ch].CCR & 0x80); /* CCRのSTRは書き込みでは落とせない */
		if ((data & 0x10) && (DMA[ch].CCR & 0x80))
		{
			/* Software Abort */
			DMAERR(ch, 0x11)
			break;
		}
		if (data & 0x20) /* Halt */
		{
			/* 本来は落ちるはず。Nemesis'90で調子悪いので… */
			/* DMA[ch].CSR &= 0xf7; */
			break;
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
					break;
				}
				DMA[ch].CSR |= 0x08;
				if ((DMA[ch].OCR & 8) /*&&(!DMA[ch].MTC)*/)
				{
					/* アレイ／リンクアレイチェイン */
					DMA[ch].MAR = dma_readmem24_dword(DMA[ch].BAR) & 0xffffff;
					DMA[ch].MTC = dma_readmem24_word(DMA[ch].BAR + 4);
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
							break;
						}
					}
				}
				if (!DMA[ch].MTC)
				{
					/* カウントエラー */
					DMAERR(ch, 0x0d)
					break;
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
						DMA[ch].CSR |= 0x40; /* ブロック転送終了ビット／割り込み ? */
						DMAINT(ch)
						break;
					}
					else if (!DMA[ch].MTC)
					{
						DMAERR(ch, 0x0d)
						break;
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
		if (ch == 3)
			DMA[ch].GCR = data;
		break;
	}
}

int FASTCALL DMA_Exec(int ch)
{
	uint32_t *src, *dst;

	/* if ( DMA_IntCH&(1<<ch) ) return 1; */

	if (DMA[ch].OCR & 0x80)
	{
		/* Device->Memory */
		src = &DMA[ch].DAR;
		dst = &DMA[ch].MAR;
	}
	else
	{
		/* Memory->Device */
		src = &DMA[ch].MAR;
		dst = &DMA[ch].DAR;
	}

	while ((DMA[ch].CSR & 0x08) && (!(DMA[ch].CCR & 0x20)) && (!(DMA[ch].CSR & 0x80)) && (DMA[ch].MTC) &&
	       (((DMA[ch].OCR & 3) != 2) || (IsReady[ch]())))
	{
		BusErrFlag = 0;
		switch (((DMA[ch].OCR >> 4) & 3) + ((DMA[ch].DCR >> 1) & 4))
		{
		case 0:
		case 3:
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			break;
		case 1:
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			break;
		case 2:
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			break;
		case 4:
			dma_writemem24(*dst, dma_readmem24(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 1;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 1;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 1;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 1;
			break;
		case 5:
			dma_writemem24_word(*dst, dma_readmem24_word(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 2;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 2;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 2;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 2;
			break;
		case 6:
			dma_writemem24_dword(*dst, dma_readmem24_dword(*src));
			if (DMA[ch].SCR & 4)
				DMA[ch].MAR += 4;
			else if (DMA[ch].SCR & 8)
				DMA[ch].MAR -= 4;
			if (DMA[ch].SCR & 1)
				DMA[ch].DAR += 4;
			else if (DMA[ch].SCR & 2)
				DMA[ch].DAR -= 4;
			break;
		}

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
			break;
		}

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
						DMA[ch].MTC = dma_readmem24_word(DMA[ch].BAR + 4);
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
						DMA[ch].MTC = dma_readmem24_word(DMA[ch].BAR + 4);
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
