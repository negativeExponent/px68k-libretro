/*
 *  SASI.C - Shugart Associates System Interface (SASI HDD)
 */

#include "../x11/common.h"
#include "../x11/state.h"

#include "dosio.h"

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

static int32_t FASTCALL SASI_Int(int32_t irq)
{
	IRQH_IRQCallBack(irq);

	if (irq == 1)
		return ((int32_t)IOC_IntVect + 2);

	return IRQ_DEFAULT_VECTOR;
}

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

static int SASI_Seek(void)
{
	FILEH *fp;

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

static int SASI_Flush(void)
{
	FILEH *fp;

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

/* Check the command. To be honest, the description in InsideX68k is not enough ^^;.
* As for what is not described,
* - C2h (initialization?). No parameters other than Unit. Write 10 pieces of data in DataPhase.
* - 06h (format?). Logical block specified (specified every 21h). 6 is specified for the number of blocks.
*/
static void SASI_CheckCmd(void)
{
	int result;

	SASI_Unit = (SASI_Cmd[1] >> 5) & 1; /* On X68k, unit numbers can only be 0 or 1 */
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

static uint8_t SASI_ReadData(void)
{
	uint8_t ret = 0;
	int result = 0;

	if ((SASI_Phase == 3) && (SASI_RW)) /* Reading data ~ */
	{
		ret = SASI_Buf[SASI_BufPtr++];
		if (SASI_BufPtr == 256)
		{
			SASI_Blocks--;
			if (SASI_Blocks) /* More blocks to read? */
			{
				SASI_Sector++;
				SASI_BufPtr = 0;
				result = SASI_Seek(); /* Read next sector into buffer */
				if (!result)          /* result=0: if it is the end of the image (= invalid sector) */
				{
					SASI_Error = 0x0f;
					SASI_Phase++;
				}
			}
			else
				SASI_Phase++; /* Specified block read complete */
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
		SASI_Phase = 0; /* Just return 0. Return to BusFree */
	}
	else if (SASI_Phase == 9) /* DataPhase(SenseStatExclusive) */
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

	return ret;
}

static void SASI_WriteData(uint32_t data)
{
	int i, result;
	uint8_t bit;

	if (SASI_Phase == 0)
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
	else if (SASI_Phase == 2)
	{
		SASI_Cmd[SASI_CmdPtr++] = data;
		if (SASI_CmdPtr == 6) /* Command completed */
		{
#if 0
				//SASI_Phase++;
#endif
			SASI_CheckCmd();
		}
	}
	else if ((SASI_Phase == 3) && (!SASI_RW)) /* Data writing in progress */
	{
		SASI_Buf[SASI_BufPtr++] = data;
		if (SASI_BufPtr == 256)
		{
			result = SASI_Flush(); /* Write the current buffer */
			SASI_Blocks--;
			if (SASI_Blocks) /* More blocks to write? */
			{
				SASI_Sector++;
				SASI_BufPtr = 0;
				result = SASI_Seek(); /* Read next sector into buffer */
				if (!result) /* result=0: if it is the end of the image (=
				                invalid sector) */
				{
					SASI_Error = 0x0f;
					SASI_Phase++;
				}
			}
			else
				SASI_Phase++; /* Specified block write complete */
		}
	}
	else if (SASI_Phase == 10)
	{
		SASI_SenseStatPtr++;
		if (SASI_SenseStatPtr == 10) /* Command issuance completed */
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

uint8_t FASTCALL SASI_Read(uint32_t adr)
{
	if ((adr & 1) != 0)
	{
		adr &= 7;

		if (adr == 1)
		{
			uint8_t ret = SASI_ReadData();
			StatBar_HDD((SASI_Phase) ? 2 : 0);
			return ret;
		}
		else if (adr == 3)
		{
			uint8_t ret = 0;

			if (SASI_Phase)
				ret |= 2; /* Busy */
			if (SASI_Phase > 1)
				ret |= 1; /* Req */
			if (SASI_Phase == 2)
				ret |= 8;                       /* C/D */
			if ((SASI_Phase == 3) && (SASI_RW)) /* SASI_RW=1:Read */
				ret |= 4;                       /* I/O */
			if (SASI_Phase == 9)                /* Phase=9:SenseStatusExclusive */
				ret |= 4;                       /* I/O */
			if ((SASI_Phase == 4) || (SASI_Phase == 5))
				ret |= 0x0c; /* I/O & C/D */
			if (SASI_Phase == 5)
				ret |= 0x10; /* MSG */
			
			StatBar_HDD((SASI_Phase) ? 2 : 0);
			return ret;
		}

		/* other registers are write-only */
		return 0xff;
	}

	/* Even addresses not decoded. */
	return 0xff;
}

/* I/O Write */
void FASTCALL SASI_Write(uint32_t adr, uint8_t data)
{
	int result, i;
	uint8_t bit;

	if ((adr & 1) != 0)
	{
		adr &= 7;

		if (adr == 1)
		{
			SASI_WriteData(data);
		}
		else if (adr == 3)
		{
			if (SASI_Phase == 1)
			{
				SASI_Phase++;
			}
		}
		else if (adr == 5)
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
		else if (adr == 7)
		{
			if (SASI_Phase == 0)
			{
				SASI_WriteData(data);
			}
		}
	}

	StatBar_HDD((SASI_Phase) ? 2 : 0);
}

int SASI_StateContext(void *f, int writing) {
	state_context_f(SASI_Cmd, sizeof(SASI_Cmd));
	state_context_f(SASI_Buf, sizeof(SASI_Buf));
	state_context_f(&SASI_Phase, sizeof(SASI_Phase));
	state_context_f(&SASI_Sector, sizeof(SASI_Sector));
	state_context_f(&SASI_Blocks, sizeof(SASI_Blocks));
	state_context_f(&SASI_CmdPtr, sizeof(SASI_CmdPtr));
	state_context_f(&SASI_Device, sizeof(SASI_Device));
	state_context_f(&SASI_Unit, sizeof(SASI_Unit));
	state_context_f(&SASI_BufPtr, sizeof(SASI_BufPtr));
	state_context_f(&SASI_RW, sizeof(SASI_RW));
	state_context_f(&SASI_Stat, sizeof(SASI_Stat));
	state_context_f(&SASI_Error, sizeof(SASI_Error));
	state_context_f(SASI_SenseStatBuf, sizeof(SASI_SenseStatBuf));
	state_context_f(&SASI_SenseStatPtr, sizeof(SASI_SenseStatPtr));

	return 1;

}
