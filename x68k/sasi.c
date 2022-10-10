/*
 *  SASI.C - Shugart Associates System Interface (SASI HDD)
 */

#include "../x11/common.h"

#include "../win32api/dosio.h"

#include "../x11/prop.h"
#include "../x11/status.h"

#include "sasi.h"
#include "ioc.h"
#include "irqh.h"
#include "sram.h"

static uint8_t SASI_Cmd[6];
static uint8_t SASI_Buf[256];
static uint8_t SASI_Phase   = 0;
static uint32_t SASI_Sector = 0;
static uint32_t SASI_Blocks = 0;
static uint8_t SASI_CmdPtr  = 0;
static uint16_t SASI_Device = 0;
static uint8_t SASI_Unit    = 0;
static int16_t SASI_BufPtr  = 0;
static uint8_t SASI_RW      = 0;
static uint8_t SASI_Stat    = 0;
static uint8_t SASI_Error   = 0;
static uint8_t SASI_SenseStatBuf[4];
static uint8_t SASI_SenseStatPtr = 0;

int SASI_IsReady(void)
{
	if ((SASI_Phase == 2) || (SASI_Phase == 3) || (SASI_Phase == 9))
		return 1;
	else
		return 0;
}

/* わりこみ~ */
static int32_t FASTCALL SASI_Int(int32_t irq)
{
	IRQH_IRQCallBack(irq);

	if (irq == 1)
		return ((int32_t)IOC_IntVect + 2);

	return IRQ_DEFAULT_VECTOR;
}

/* 初期化 */
void SASI_Init(void)
{
	SASI_Phase        = 0;
	SASI_Sector       = 0;
	SASI_Blocks       = 0;
	SASI_CmdPtr       = 0;
	SASI_Device       = 0;
	SASI_Unit         = 0;
	SASI_BufPtr       = 0;
	SASI_RW           = 0;
	SASI_Stat         = 0;
	SASI_Error        = 0;
	SASI_SenseStatPtr = 0;

	/* $ed005a - Always enable SASI-HD */
	if (Config.XVIMode >= 2)
		SRAM_SetMem(0x5a, 0x01);
}

/* し−く（リード時）*/
static int SASI_Seek(void)
{
	FILEH fp;

	memset(SASI_Buf, 0, 256);
	fp = file_open_rb(Config.HDImage[SASI_Device * 2 + SASI_Unit]);
	if (!fp)
	{
		memset(SASI_Buf, 0, 256);
		return -1;
	}
	if (file_seek(fp, SASI_Sector << 8, FSEEK_SET) != 0)
	{
		file_close(fp);
		return 0;
	}
	if (file_read(fp, SASI_Buf, 256) != 256)
	{
		file_close(fp);
		return 0;
	}
	file_close(fp);

	return 1;
}

/*
 *   しーく（ライト時）
 */
static int SASI_Flush(void)
{
	FILEH fp;

	fp = file_open(Config.HDImage[SASI_Device * 2 + SASI_Unit]);
	if (!fp)
		return -1;
	if (file_seek(fp, SASI_Sector << 8, FSEEK_SET) != 0)
	{
		file_close(fp);
		return 0;
	}
	if (file_write(fp, SASI_Buf, 256) != 256)
	{
		file_close(fp);
		return 0;
	}
	file_close(fp);

	return 1;
}

/*
 *   I/O Read
 */
uint8_t FASTCALL SASI_Read(uint32_t adr)
{
	uint8_t ret = 0;
	int16_t result;

	if (adr == 0xe96003)
	{
		if (SASI_Phase)
			ret |= 2;                       /* Busy */
		if (SASI_Phase > 1)
			ret |= 1;                       /* Req */
		if (SASI_Phase == 2)
			ret |= 8;                       /* C/D */
		if ((SASI_Phase == 3) && (SASI_RW)) /* SASI_RW=1:Read */
			ret |= 4;                       /* I/O */
		if (SASI_Phase == 9)                /* Phase=9:SenseStatus中 */
			ret |= 4;                       /* I/O */
		if ((SASI_Phase == 4) || (SASI_Phase == 5))
			ret |= 0x0c;                    /* I/O & C/D */
		if (SASI_Phase == 5)
			ret |= 0x10;                    /* MSG */
	}
	else if (adr == 0xe96001)
	{
		if ((SASI_Phase == 3) && (SASI_RW)) /* データリード中~ */
		{
			ret = SASI_Buf[SASI_BufPtr++];
			if (SASI_BufPtr == 256)
			{
				SASI_Blocks--;
				if (SASI_Blocks)             /* まだ読むブロックがある？ */
				{
					SASI_Sector++;
					SASI_BufPtr = 0;
					result      = SASI_Seek(); /* 次のセクタをバッファに読む */
					if (!result)               /* result=0：イメージの最後（＝無効なセクタ）なら */
					{
						SASI_Error = 0x0f;
						SASI_Phase++;
					}
				}
				else
					SASI_Phase++; /* 指定ブロックのリード完了 */
			}
		}
		else if (SASI_Phase == 4) /* Status Phase */
		{
			if (SASI_Error)
				ret = 0x02;
			else
				ret = SASI_Stat;
			SASI_Phase++;
		}
		else if (SASI_Phase == 5) /* MessagePhase */
		{
			SASI_Phase = 0; /* 0を返すだけ~。BusFreeに帰ります */
		}
		else if (SASI_Phase == 9) /* DataPhase(SenseStat専用) */
		{
			ret = SASI_SenseStatBuf[SASI_SenseStatPtr++];
			if (SASI_SenseStatPtr == 4)
			{
				SASI_Error = 0;
				SASI_Phase = 4; /* StatusPhaseへ */
			}
		}
		if (SASI_Phase == 4)
		{
			IOC_IntStat |= 0x10;
			if (IOC_IntStat & 8)
				IRQH_Int(1, &SASI_Int);
		}
	}

	StatBar_HDD((SASI_Phase) ? 2 : 0);

	return ret;
}

/* コマンドのチェック。正直、InsideX68k内の記述ではちと足りない ^^;。
 * 未記述のものとして、
 *   - C2h（初期化系？）。Unit以外のパラメータは無し。DataPhaseで10個のデータを書きこむ。
 *   - 06h（フォーマット？）。論理ブロック指定あり（21hおきに指定している）。ブロック数のとこは6が指定されている。
 */
static void SASI_CheckCmd(void)
{
	int result;

	SASI_Unit = (SASI_Cmd[1] >> 5) & 1; /* X68kでは、ユニット番号は0か1しか取れない */
	switch (SASI_Cmd[0])
	{
	case 0x00: /* Test Drive Ready */
		if (Config.HDImage[SASI_Device * 2 + SASI_Unit][0])
			SASI_Stat = 0;
		else
		{
			SASI_Stat  = 0x02;
			SASI_Error = 0x7f;
		}
		SASI_Phase += 2;
		break;
	case 0x01: /* Recalibrate */
		if (Config.HDImage[SASI_Device * 2 + SASI_Unit][0])
		{
			SASI_Sector = 0;
			SASI_Stat   = 0;
		}
		else
		{
			SASI_Stat  = 0x02;
			SASI_Error = 0x7f;
		}
		SASI_Phase += 2;
		break;
	case 0x03: /* Request Sense Status */
		SASI_SenseStatBuf[0] = SASI_Error;
		SASI_SenseStatBuf[1] = (uint8_t)((SASI_Unit << 5) | ((SASI_Sector >> 16) & 0x1f));
		SASI_SenseStatBuf[2] = (uint8_t)(SASI_Sector >> 8);
		SASI_SenseStatBuf[3] = (uint8_t)SASI_Sector;
		SASI_Error           = 0;
		SASI_Phase           = 9;
		SASI_Stat            = 0;
		SASI_SenseStatPtr    = 0;
		break;
	case 0x04: /* Format Drive */
		SASI_Phase += 2;
		SASI_Stat = 0;
		break;
	case 0x08: /* Read Data */
		SASI_Sector = (((uint32_t)SASI_Cmd[1] & 0x1f) << 16) | (((uint32_t)SASI_Cmd[2]) << 8) | ((uint32_t)SASI_Cmd[3]);
		SASI_Blocks = (uint32_t)SASI_Cmd[4];
		SASI_Phase++;
		SASI_RW     = 1;
		SASI_BufPtr = 0;
		SASI_Stat   = 0;
		result      = SASI_Seek();
		if ((result == 0) || (result == -1))
		{
#if 0
			//SASI_Phase++;
#endif
			SASI_Error = 0x0f;
		}
		break;
	case 0x0a: /* Write Data */
		SASI_Sector = (((uint32_t)SASI_Cmd[1] & 0x1f) << 16) | (((uint32_t)SASI_Cmd[2]) << 8) | ((uint32_t)SASI_Cmd[3]);
		SASI_Blocks = (uint32_t)SASI_Cmd[4];
		SASI_Phase++;
		SASI_RW     = 0;
		SASI_BufPtr = 0;
		SASI_Stat   = 0;
		memset(SASI_Buf, 0, 256);
		result = SASI_Seek();
		if ((result == 0) || (result == -1))
		{
#if 0
			//SASI_Phase++;
#endif
			SASI_Error = 0x0f;
		}
		break;
	case 0x0b: /* Seek */
		if (Config.HDImage[SASI_Device * 2 + SASI_Unit][0])
		{
			SASI_Stat = 0;
		}
		else
		{
			SASI_Stat  = 0x02;
			SASI_Error = 0x7f;
		}
		SASI_Phase += 2;
#if 0
		//SASI_Phase = 9;
#endif
		break;
	case 0xc2:
		SASI_Phase        = 10;
		SASI_SenseStatPtr = 0;
		if (Config.HDImage[SASI_Device * 2 + SASI_Unit][0])
			SASI_Stat = 0;
		else
		{
			SASI_Stat  = 0x02;
			SASI_Error = 0x7f;
		}
		break;
	default:
		SASI_Phase += 2;
	}
}

/* I/O Write */
void FASTCALL SASI_Write(uint32_t adr, uint8_t data)
{
	int result, i;
	uint8_t bit;

	if ((adr == 0xe96007) && (SASI_Phase == 0))
	{
		SASI_Device = 0x7f;
		if (data)
		{
			for (i = 0, bit = 1; bit; i++, bit <<= 1)
			{
				if (data & bit)
				{
					SASI_Device = i;
					break;
				}
			}
		}
		if ((Config.HDImage[SASI_Device * 2][0]) || (Config.HDImage[SASI_Device * 2 + 1][0]))
		{
			SASI_Phase++;
			SASI_CmdPtr = 0;
		}
		else
		{
			SASI_Phase = 0;
		}
	}
	else if ((adr == 0xe96003) && (SASI_Phase == 1))
	{
		SASI_Phase++;
	}
	else if (adr == 0xe96005) /* SASI Reset */
	{
		SASI_Phase        = 0;
		SASI_Sector       = 0;
		SASI_Blocks       = 0;
		SASI_CmdPtr       = 0;
		SASI_Device       = 0;
		SASI_Unit         = 0;
		SASI_BufPtr       = 0;
		SASI_RW           = 0;
		SASI_Stat         = 0;
		SASI_Error        = 0;
		SASI_SenseStatPtr = 0;
	}
	else if (adr == 0xe96001)
	{
		if (SASI_Phase == 2)
		{
			SASI_Cmd[SASI_CmdPtr++] = data;
			if (SASI_CmdPtr == 6) /* コマンド発行終了 */
			{
#if 0
				//SASI_Phase++;
#endif
				SASI_CheckCmd();
			}
		}
		else if ((SASI_Phase == 3) && (!SASI_RW)) /* データライト中~ */
		{
			SASI_Buf[SASI_BufPtr++] = data;
			if (SASI_BufPtr == 256)
			{
				result = SASI_Flush(); /* 現在のバッファを書き出す */
				SASI_Blocks--;
				if (SASI_Blocks) /* まだ書くブロックがある？ */
				{
					SASI_Sector++;
					SASI_BufPtr = 0;
					result      = SASI_Seek(); /* 次のセクタをバッファに読む */
					if (!result)               /* result=0：イメージの最後（＝無効なセクタ）なら */
					{
						SASI_Error = 0x0f;
						SASI_Phase++;
					}
				}
				else
					SASI_Phase++; /* 指定ブロックのライト完了 */
			}
		}
		else if (SASI_Phase == 10)
		{
			SASI_SenseStatPtr++;
			if (SASI_SenseStatPtr == 10) /* コマンド発行終了 */
			{
				SASI_Phase = 4;
			}
		}
		if (SASI_Phase == 4)
		{
			IOC_IntStat |= 0x10;
			if (IOC_IntStat & 8)
				IRQH_Int(1, &SASI_Int);
		}
	}
	StatBar_HDD((SASI_Phase) ? 2 : 0);
}
