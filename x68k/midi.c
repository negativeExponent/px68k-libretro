/*
 * MIDI.C - MIDI Board (CZ-6BM1) emulator
 * Powered by Punyu-san
 */

/* 4/18 dawn:      Fixed exclusive not working properly
 * 4/18 morning:   Fixed not working with Lenam
 * 4/18 afternoon: Dracula is OK by waiting for exclusive transmission to be completed
 */

/* ToDo: - During exclusive transmission (e.g. while setting the Dracula tone)
 *         As expected, it will drop to 1MHz...
 *         Get the port that returns the MIDI status
 *       - Check the specifications of the running status in MT-32
 *       - Reset the sound source when exiting
 *       - It shouldn't be reset on the actual machine when the IPL is reset,
 *         This is a matter of preference, so it might be nice to
 *         be able to set it in the config
 */

#include "../x11/common.h"
#include "../x11/state.h"

#include "dosio.h"
#include "mmsystem.h"

#include "../x11/prop.h"

#include "midi.h"
#include "irqh.h"
#include "x68kmemory.h"

enum
{
	MIDIBUFFERS  = 1024, /* 1024 (should never needed more than this) */
	MIDIBUFTIMER = 3200, /* 10MHz / (31.25K / 10bit) = 3200 */
	MIDIFIFOSIZE = 256,
	MIDIDELAYBUF = 4096 /* is it ok to have 31250/10 = 3125 byts (1sec)?  */
};

enum
{
	MIDI_NOTUSED = 0,
	MIDI_DEFAULT,
	MIDI_MT32,
	MIDI_CM32L,
	MIDI_CM64,
	MIDI_CM300,
	MIDI_CM500,
	MIDI_SC55,
	MIDI_SC88,
	MIDI_LA,
	MIDI_GM,
	MIDI_GS,
	MIDI_XG,
};

static void *hOut = 0;
static MIDIHDR hHdr;

static int MIDI_CTRL;
static int MIDI_POS;
static int MIDI_SYSCOUNT;

static uint8_t MIDI_LAST;
static uint8_t MIDI_BUF[MIDIBUFFERS];
static uint8_t MIDI_EXCVBUF[MIDIBUFFERS];
static uint8_t MIDI_EXCVWAIT;

static uint8_t MIDI_RegHigh    = 0;
static uint8_t MIDI_Vector     = 0;
static uint8_t MIDI_IntEnable  = 0;
static uint8_t MIDI_IntVect    = 0;
static uint8_t MIDI_IntFlag    = 0;
static uint32_t MIDI_Buffered  = 0;
static int32_t MIDI_BufTimer   = 3333;
static uint8_t MIDI_R05        = 0;
static uint32_t MIDI_GTimerMax = 0;
static uint32_t MIDI_MTimerMax = 0;
static int32_t MIDI_GTimerVal  = 0;
static int32_t MIDI_MTimerVal  = 0;
static uint8_t MIDI_MODULE     = MIDI_NOTUSED;

static uint8_t MIDI_ResetType[5] = {
	MIDI_LA, MIDI_GM, MIDI_GS, MIDI_XG
};

typedef struct
{
	uint32_t time;
	uint8_t msg;
} DELAYBUFITEM;

static DELAYBUFITEM DelayBuf[MIDIDELAYBUF];
static int DBufPtrW = 0;
static int DBufPtrR = 0;

/* Nekomichi 6, MIMPI tone map compatibility */

enum
{
	MIMPI_LA = 0,
	MIMPI_PCM,
	MIMPI_GS,
	MIMPI_RHYTHM
};

static uint8_t LOADED_TONEMAP = 0;
static uint8_t ENABLE_TONEMAP = 0;
static uint8_t TONE_CH[16];
static uint8_t TONEBANK[3][128];
static uint8_t TONEMAP[3][128];

static uint8_t EXCV_MTRESET[] = { 0xf0, 0x41, 0x10, 0x16, 0x12, 0x7f, 0x00, 0x00, 0x00, 0x01, 0xf7 };
static uint8_t EXCV_GMRESET[] = { 0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7 };
static uint8_t EXCV_GSRESET[] = { 0xf0, 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7f, 0x00, 0x41, 0xf7 };
static uint8_t EXCV_XGRESET[] = { 0xf0, 0x43, 0x10, 0x4c, 0x00, 0x00, 0x7e, 0x00, 0xf7 };

enum
{
	MIDICTRL_READY = 0,
	MIDICTRL_2BYTES,
	MIDICTRL_3BYTES,
	MIDICTRL_EXCLUSIVE,
	MIDICTRL_TIMECODE,
	MIDICTRL_SYSTEM
};

enum
{
	MIDI_EXCLUSIVE   = 0xf0,
	MIDI_TIMECODE    = 0xf1,
	MIDI_SONGPOS     = 0xf2,
	MIDI_SONGSELECT  = 0xf3,
	MIDI_TUNEREQUEST = 0xf6,
	MIDI_EOX         = 0xf7,
	MIDI_TIMING      = 0xf8,
	MIDI_START       = 0xfa,
	MIDI_CONTINUE    = 0xfb,
	MIDI_STOP        = 0xfc,
	MIDI_ACTIVESENSE = 0xfe,
	MIDI_SYSTEMRESET = 0xff
};

#define MIDIOUTS(a, b, c) (((uint32_t)c << 16) | ((uint32_t)b << 8) | (uint32_t)a)

static int32_t FASTCALL MIDI_Int(int32_t irq)
{
	IRQH_IRQCallBack(irq);
	if (irq == 4)
		return (int32_t)(MIDI_Vector | MIDI_IntVect);

	return IRQ_DEFAULT_VECTOR;
}

void FASTCALL MIDI_Timer(uint32_t clk)
{
	if (!Config.MIDI_SW)
		return; /* return when MIDI is OFF */

	MIDI_BufTimer -= clk;
	if (MIDI_BufTimer < 0)
	{
		MIDI_BufTimer += MIDIBUFTIMER;
		if (MIDI_Buffered)
		{
			MIDI_Buffered--;
			if ((MIDI_Buffered < MIDIFIFOSIZE) && (MIDI_IntEnable & 0x40)) /* Tx FIFO Empty Interrupt�ʥ��ȥץ�� */
			{
				MIDI_IntFlag |= 0x40;
				MIDI_IntVect = 0x0c;
				IRQH_Int(4, &MIDI_Int);
			}
		}
	}

	if (MIDI_MTimerMax)
	{
		MIDI_MTimerVal -= clk;
		if (MIDI_MTimerVal < 0) /* Midi timer interrup (Magic Bottle) */
		{
			while (MIDI_MTimerVal < 0)
				MIDI_MTimerVal += MIDI_MTimerMax * 80;
			if ((!(MIDI_R05 & 0x80)) && (MIDI_IntEnable & 0x02))
			{
				MIDI_IntFlag |= 0x02;
				MIDI_IntVect = 0x02;
				IRQH_Int(4, &MIDI_Int);
			}
		}
	}

	if (MIDI_GTimerMax)
	{
		MIDI_GTimerVal -= clk;
		if (MIDI_GTimerVal < 0) /* General timer interrupt (RCD.X) */
		{
			while (MIDI_GTimerVal < 0)
				MIDI_GTimerVal += MIDI_GTimerMax * 80;
			if (MIDI_IntEnable & 0x80)
			{
				MIDI_IntFlag |= 0x80;
				MIDI_IntVect = 0x0e;
				IRQH_Int(4, &MIDI_Int);
			}
		}
	}
}

static void MIDI_SetModule(void)
{
	if (Config.MIDI_SW)
		MIDI_MODULE = MIDI_ResetType[Config.MIDI_Type];
	else
		MIDI_MODULE = MIDI_NOTUSED;
}

static void MIDI_Sendexclusive(uint8_t *excv, int length)
{
	memcpy(MIDI_EXCVBUF, excv, length);
	hHdr.lpData         = MIDI_EXCVBUF;
	hHdr.dwFlags        = 0;
	hHdr.dwBufferLength = length;
	midiOutPrepareHeader(hOut, &hHdr, sizeof(MIDIHDR));
	midiOutLongMsg(hOut, &hHdr, sizeof(MIDIHDR));
	MIDI_EXCVWAIT = 1;
}

static void MIDI_Waitlastexclusiveout(void)
{
#if 1
	MIDI_EXCVWAIT = 0;
#else
	/* Let's wait until the exclusive transmission is complete~ */
	if (MIDI_EXCVWAIT)
	{
		while (midiOutUnprepareHeader(hOut, &hHdr, sizeof(MIDIHDR)) == MIDIERR_STILLPLAYING)
			;
		MIDI_EXCVWAIT = 0;
	}
#endif
}

static void MIDI_AllNoteOff(void)
{
	if (hOut)
	{
		int i;
		MIDI_Waitlastexclusiveout();
		for (i = 0; i < 16; i++)
		{
			midiOutShortMsg(hOut, (uint32_t)(0x7bb0 + i));
		}
	}
}

void MIDI_Reset(void)
{
	memset(DelayBuf, 0, sizeof(DelayBuf));
	DBufPtrW = DBufPtrR = 0;

	if (hOut)
	{
		uint8_t *excv;
		uint32_t excv_len;

		switch (MIDI_MODULE)
		{
		case MIDI_NOTUSED:
			return;
		case MIDI_MT32:
		case MIDI_CM32L:
		case MIDI_CM64:
		case MIDI_LA:
			excv = EXCV_MTRESET;
			excv_len = sizeof(EXCV_MTRESET);
			break;
		case MIDI_CM300:
		case MIDI_SC55:
		case MIDI_SC88:
		case MIDI_GS:
			excv = EXCV_GSRESET;
			excv_len = sizeof(EXCV_GSRESET);
			break;
		case MIDI_XG:
			excv = EXCV_XGRESET;
			excv_len = sizeof(EXCV_XGRESET);
			break;
		default: /* GM */
			excv = EXCV_GMRESET;
			excv_len = sizeof(EXCV_GMRESET);
			break;
		}
		if (excv && hOut)
		{
			MIDI_Waitlastexclusiveout();
			MIDI_Sendexclusive(excv, excv_len);
		}
		MIDI_AllNoteOff();
	}
}

void MIDI_Init(void)
{
	memset(DelayBuf, 0, sizeof(DelayBuf));
	DBufPtrW = DBufPtrR = 0;

	MIDI_SetModule();
	MIDI_RegHigh   = 0;
	MIDI_Vector    = 0;
	MIDI_IntEnable = 0;
	MIDI_IntVect   = 0x10;
	MIDI_IntFlag   = 0;
	MIDI_R05       = 0;

	MIDI_CTRL     = MIDICTRL_READY;
	MIDI_LAST     = 0x80;
	MIDI_EXCVWAIT = 0;

	if (!hOut)
	{
		if (midiOutOpen(&hOut, MIDI_MAPPER, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR)
		{
			midiOutReset(hOut);
		}
		else
			hOut = 0;
	}
}

void MIDI_Stop(void)
{
	MIDI_AllNoteOff();
}

void MIDI_Cleanup(void)
{
	if (hOut)
	{
		MIDI_Stop();
		MIDI_Reset();
		MIDI_Waitlastexclusiveout();
		midiOutReset(hOut);
		midiOutClose(hOut);
		hOut = 0;
	}
}

static void MIDI_Message(uint8_t mes)
{
	if (!hOut)
	{
		return;
	}

	switch (mes)
	{
	case MIDI_TIMING:
	case MIDI_START:
	case MIDI_CONTINUE:
	case MIDI_STOP:
	case MIDI_ACTIVESENSE:
	case MIDI_SYSTEMRESET:
		return;
	}
	if (MIDI_CTRL == MIDICTRL_READY)
	{
		if (mes & 0x80)
		{
			/* status */
			MIDI_POS = 0;
			switch (mes & 0xf0)
			{
			case 0xc0:
			case 0xd0:
				MIDI_LAST = mes;
				MIDI_CTRL = MIDICTRL_2BYTES;
				break;
			case 0x80:
			case 0x90:
			case 0xa0:
			case 0xb0:
			case 0xe0:
				MIDI_LAST = mes;
				MIDI_CTRL = MIDICTRL_3BYTES;
				break;
			default:
				switch (mes)
				{
				case MIDI_EXCLUSIVE:
					MIDI_CTRL = MIDICTRL_EXCLUSIVE;
					break;
				case MIDI_TIMECODE:
					MIDI_CTRL = MIDICTRL_TIMECODE;
					break;
				case MIDI_SONGPOS:
					MIDI_CTRL     = MIDICTRL_SYSTEM;
					MIDI_SYSCOUNT = 3;
					break;
				case MIDI_SONGSELECT:
					MIDI_CTRL     = MIDICTRL_SYSTEM;
					MIDI_SYSCOUNT = 2;
					break;
				case MIDI_TUNEREQUEST:
					MIDI_CTRL     = MIDICTRL_SYSTEM;
					MIDI_SYSCOUNT = 1;
					break;
				default:
					return;
				}
				break;
			}
		}
		else
		{
			/* running status */
			MIDI_BUF[0] = MIDI_LAST;
			MIDI_POS    = 1;
			switch (MIDI_LAST & 0xf0)
			{
			case 0xc0:
			case 0xd0:
				MIDI_CTRL = MIDICTRL_2BYTES;
				break;
			case 0x80:
			case 0x90:
			case 0xa0:
			case 0xb0:
			case 0xe0:
				MIDI_CTRL   = MIDICTRL_3BYTES;
				break;
			default:
				return;
			}
		}
	}
	else if ((mes & 0x80) && ((MIDI_CTRL != MIDICTRL_EXCLUSIVE) || (mes != MIDI_EOX))) /* When a control byte appears in the data section of a message... (GENOCIDE2)*/
	{
		/* status */
		MIDI_POS = 0;
		switch (mes & 0xf0)
		{
		case 0xc0:
		case 0xd0:
			MIDI_CTRL = MIDICTRL_2BYTES;
			break;
		case 0x80:
		case 0x90:
		case 0xa0:
		case 0xb0:
		case 0xe0:
			MIDI_LAST = mes;
			MIDI_CTRL = MIDICTRL_3BYTES;
			break;
		default:
			switch (mes)
			{
			case MIDI_EXCLUSIVE:
				MIDI_CTRL = MIDICTRL_EXCLUSIVE;
				break;
			case MIDI_TIMECODE:
				MIDI_CTRL = MIDICTRL_TIMECODE;
				break;
			case MIDI_SONGPOS:
				MIDI_CTRL     = MIDICTRL_SYSTEM;
				MIDI_SYSCOUNT = 3;
				break;
			case MIDI_SONGSELECT:
				MIDI_CTRL     = MIDICTRL_SYSTEM;
				MIDI_SYSCOUNT = 2;
				break;
			case MIDI_TUNEREQUEST:
				MIDI_CTRL     = MIDICTRL_SYSTEM;
				MIDI_SYSCOUNT = 1;
				break;
			default:
				return;
			}
			break;
		}
	}

	MIDI_BUF[MIDI_POS] = mes;
	MIDI_POS++;

	switch (MIDI_CTRL)
	{
	case MIDICTRL_2BYTES:
		if (MIDI_POS >= 2)
		{
			if (ENABLE_TONEMAP)
			{
				if (((MIDI_BUF[0] & 0xf0) == 0xc0) && (TONE_CH[MIDI_BUF[0] & 0x0f] < MIMPI_RHYTHM))
				{
					MIDI_BUF[1] = TONEMAP[TONE_CH[MIDI_BUF[0] & 0x0f]][MIDI_BUF[1] & 0x7f];
				}
			}
			MIDI_Waitlastexclusiveout();
			midiOutShortMsg(hOut, MIDIOUTS(MIDI_BUF[0], MIDI_BUF[1], 0));
			MIDI_CTRL = MIDICTRL_READY;
		}
		break;
	case MIDICTRL_3BYTES:
		if (MIDI_POS >= 3)
		{
			MIDI_Waitlastexclusiveout();
			midiOutShortMsg(hOut, MIDIOUTS(MIDI_BUF[0], MIDI_BUF[1], MIDI_BUF[2]));
			MIDI_CTRL = MIDICTRL_READY;
		}
		break;
	case MIDICTRL_EXCLUSIVE:
		if (mes == MIDI_EOX)
		{
			MIDI_Waitlastexclusiveout();
			MIDI_Sendexclusive(MIDI_BUF, MIDI_POS);
			MIDI_CTRL = MIDICTRL_READY;
		}
		else if (MIDI_POS >= MIDIBUFFERS)  /* overflow */
		{
			MIDI_CTRL = MIDICTRL_READY;
		}
		break;
	case MIDICTRL_TIMECODE:
		if (MIDI_POS >= 2)
		{
			if ((mes == 0x7e) || (mes == 0x7f)) /* it should be the same as exclusive */
			{
				MIDI_CTRL = MIDICTRL_EXCLUSIVE;
			}
			else
			{
				MIDI_CTRL = MIDICTRL_READY;
			}
		}
		break;
	case MIDICTRL_SYSTEM:
		if (MIDI_POS >= MIDI_SYSCOUNT)
		{
			MIDI_CTRL = MIDICTRL_READY;
		}
		break;
	}
}

static void AddDelayBuf(uint8_t msg)
{
	int newptr = (DBufPtrW + 1) % MIDIDELAYBUF;
	if (newptr != DBufPtrR)
	{
		DelayBuf[DBufPtrW].time = timeGetTime();
		DelayBuf[DBufPtrW].msg  = msg;
		DBufPtrW                = newptr;
	}
}

void MIDI_DelayOut(uint32_t delay)
{
	uint32_t t = timeGetTime();
	while (DBufPtrW != DBufPtrR)
	{
		if ((t - DelayBuf[DBufPtrR].time) >= delay)
		{
			MIDI_Message(DelayBuf[DBufPtrR].msg);
			DBufPtrR = (DBufPtrR + 1) % MIDIDELAYBUF;
		}
		else
			break;
	}
}

uint8_t FASTCALL MIDI_Read(uint32_t adr)
{
	uint8_t ret = 0;

	if ((adr < 0xeafa01) || (adr >= 0xeafa10) || (!Config.MIDI_SW))
	{
		/* when MIDI is OFF, a bus error occurs */
		BusErrFlag = 1;
		BusErrAdr  = adr;
		return 0xff;
	}

	adr -= 0xeafa00;
	adr >>= 1;

	switch (adr)
	{
	case 0x00: /* R00 */
		ret          = (MIDI_Vector | MIDI_IntVect);
		MIDI_IntVect = 0x10;
		break;
	case 0x01: /* R01 */
		break;
	case 0x02: /* R02 */
		return MIDI_IntFlag;
		break;
	case 0x03: /* R03 */
		break;
	case 0x04: /* R04, 14, ... 94 */
		switch (MIDI_RegHigh)
		{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: break;

		case 5:
#if 0
			if (MIDI_Buffered >= MIDIFIFOSIZE)
			{
				ret = 0x01; /* Tx full/not ready */
			}
			else
			{
				ret = 0xc0; /* Tx empty/ready */
			}
#endif
			if (MIDI_Buffered == 0)
			{
				ret = 0xc0; /* FIFO empty & Tx ready */
			}
			else
			{
				if (MIDI_Buffered < MIDIFIFOSIZE)
				{
					ret = 0x41; /* FIFO has free space. Transmitting */
				}
				else
				{
					ret = 0x01; /* No free space in FIFO. Transmitting */
				}
			}
			break;
		}
		break;
	case 0x05: /* R05, 15, ... 95 */
		switch (MIDI_RegHigh)
		{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: break;
		}
		break;
	case 0x06: /* R06, 16, ... 96 */
		switch (MIDI_RegHigh)
		{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: break;
		}
		break;
	case 0x07: /* R07, 17, ... 97 */
		switch (MIDI_RegHigh)
		{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		case 9: break;
		}
		break;
	}

	/* undefined register returns 0 */
	return ret;
}

void FASTCALL MIDI_Write(uint32_t adr, uint8_t data)
{
	if ((adr < 0xeafa01) || (adr >= 0xeafa10) || (!Config.MIDI_SW))
	{
		/* when MIDI is OFF, a bus error occurs */                                                /* MIDI OFF���ˤϥХ����顼�ˤ��� */
		BusErrFlag = 2;
		BusErrAdr = adr;
		return;
	}

	adr -= 0xeafa00;
	adr >>= 1;

	switch (adr)
	{
	case 0x00: /* R00 */
		break;
	case 0x01: /* R01 */
		if (data & 0x80)
		{
			MIDI_Init();
		}
		MIDI_RegHigh = data & 0x0f;
		break;
	case 0x02: /* R02 */
		break;
	case 0x03: /* R03 */
		MIDI_IntFlag &= ~data;
		break;
	case 0x04: /* R04, 14, ... 94 */
		switch (MIDI_RegHigh)
		{
		case 0:
			MIDI_Vector = (data & 0xe0);
			break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8:
			MIDI_GTimerMax = (MIDI_GTimerMax & 0xff00) | (uint32_t)data;
			break;
		case 9: break;
		}
		break;
	case 0x05: /* R05, 15, ... 95 */
		switch (MIDI_RegHigh)
		{
		case 0:
			MIDI_R05 = data;
			break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8:
			MIDI_GTimerMax = (MIDI_GTimerMax & 0xff) | (((uint32_t)(data & 0x3f)) * 256);
			if (data & 0x80)
				MIDI_GTimerVal = MIDI_GTimerMax * 80;
			break;
		case 9: break;
		}
		break;
	case 0x06: /* R06, 16, ... 96 */
		switch (MIDI_RegHigh)
		{
		case 0:
			MIDI_IntEnable = data;
			break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: /* Out Data Byte */
			if (!MIDI_Buffered)
				MIDI_BufTimer = MIDIBUFTIMER;
			MIDI_Buffered++;
			AddDelayBuf(data);
			break;
		case 6: break;
		case 7: break;
		case 8:
			MIDI_MTimerMax = (MIDI_MTimerMax & 0xff00) | (uint32_t)data;
			break;
		case 9: break;
		}
		break;
	case 0x07: /* R07, 17, ... 97 */
		switch (MIDI_RegHigh)
		{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8:
			MIDI_MTimerMax = (MIDI_MTimerMax & 0xff) | (((uint32_t)(data & 0x3f)) * 256);
			if (data & 0x80)
				MIDI_MTimerVal = MIDI_MTimerMax * 80;
			break;
		case 9: break;
		}
		break;
	}
}

int MIDI_StateContext(void *f, int writing) {
	state_context_f(&MIDI_CTRL, sizeof(MIDI_CTRL));
	state_context_f(&MIDI_POS, sizeof(MIDI_POS));
	state_context_f(&MIDI_SYSCOUNT, sizeof(MIDI_SYSCOUNT));

	state_context_f(&MIDI_LAST, sizeof(MIDI_LAST));
	state_context_f(MIDI_BUF, sizeof(MIDI_BUF));
	state_context_f(MIDI_EXCVBUF, sizeof(MIDI_EXCVBUF));
	state_context_f(&MIDI_EXCVWAIT, sizeof(MIDI_EXCVWAIT));

	state_context_f(&MIDI_RegHigh, sizeof(MIDI_RegHigh));
	state_context_f(&MIDI_Vector, sizeof(MIDI_Vector));
	state_context_f(&MIDI_IntEnable, sizeof(MIDI_IntEnable));
	state_context_f(&MIDI_IntVect, sizeof(MIDI_IntVect));
	state_context_f(&MIDI_IntFlag, sizeof(MIDI_IntFlag));
	state_context_f(&MIDI_Buffered, sizeof(MIDI_Buffered));
	state_context_f(&MIDI_BufTimer, sizeof(MIDI_BufTimer));
	state_context_f(&MIDI_R05, sizeof(MIDI_R05));
	state_context_f(&MIDI_GTimerMax, sizeof(MIDI_GTimerMax));
	state_context_f(&MIDI_MTimerMax, sizeof(MIDI_MTimerMax));
	state_context_f(&MIDI_GTimerVal, sizeof(MIDI_GTimerVal));
	state_context_f(&MIDI_MTimerVal, sizeof(MIDI_MTimerVal));
	state_context_f(&MIDI_MODULE, sizeof(MIDI_MODULE));

	state_context_f(DelayBuf, sizeof(DelayBuf));
	state_context_f(&DBufPtrW, sizeof(DBufPtrW));
	state_context_f(&DBufPtrR, sizeof(DBufPtrR));

	return 1;
}

/* Load MIMPI tone file (Nekomichi 6) */

static int exstrcmp(char *str, char *cmp)
{
	uint8_t c;

	while (*cmp)
	{
		c = *str++;
		if ((c >= 'a') && (c <= 'z'))
		{
			c -= 0x20;
		}
		if (c != *cmp++)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

static void cutdelimita(char **buf)
{
	uint8_t c;

	for (;;)
	{
		c = **buf;
		if (!c)
		{
			break;
		}
		if (c > ' ')
		{
			break;
		}
		(*buf)++;
	}
}

static int getvalue(char **buf, int cutspace)
{
	int ret    = 0;
	int valhit = 0;
	uint8_t c;

	if (cutspace)
	{
		cutdelimita(buf);
	}
	for (;; valhit = 1)
	{
		c = **buf;
		if (!c)
		{
			if (!valhit)
			{
				return (-1);
			}
			else
			{
				break;
			}
		}
		if ((c < '0') || (c > '9'))
		{
			break;
		}
		ret = ret * 10 + (c - '0');
		(*buf)++;
	}
	return (ret);
}

static int file_readline(FILEH *fh, char *buf, int len)
{
	int64_t pos;
	int64_t readsize;
	int i;

	if (len < 2)
	{
		return -1;
	}
	pos = file_seek(fh, 0, FSEEK_CUR);
	if (pos != 0)
	{
		return -1;
	}
	readsize = file_read(fh, buf, len - 1);
	if (readsize == -1)
	{
		return -1;
	}
	if (!readsize)
	{
		return -1;
	}
	for (i = 0; i < readsize; i++)
	{
		pos++;
		if ((buf[i] == 0x0a) || (buf[i] == 0x0d))
		{
			break;
		}
	}
	buf[i] = '\0';
	if (file_seek(fh, pos, FSEEK_SET) != 0)
	{
		return -1;
	}
	return i;
}

static void mimpidefline_analaize(char *buf)
{
	cutdelimita(&buf);
	if (*buf == '@')
	{
		int ch;
		buf++;
		ch = getvalue(&buf, FALSE);
		if ((ch < 1) || (ch > 16))
		{
			return;
		}
		ch--;
		cutdelimita(&buf);
		if (!exstrcmp(buf, "LA"))
		{
			TONE_CH[ch] = MIMPI_LA;
		}
		else if (!exstrcmp(buf, "PCM"))
		{
			TONE_CH[ch] = MIMPI_PCM;
		}
		else if (!exstrcmp(buf, "GS"))
		{
			TONE_CH[ch] = MIMPI_GS;
		}
		else if (!exstrcmp(buf, "RHYTHM"))
		{
			TONE_CH[ch] = MIMPI_RHYTHM;
		}
	}
	else
	{
		int mod, num, bank, tone;
		mod = getvalue(&buf, FALSE);
		if ((mod < 0) || (mod >= MIMPI_RHYTHM))
		{
			return;
		}
		num = getvalue(&buf, TRUE);
		if ((num < 1) || (num > 128))
		{
			return;
		}
		num--;
		tone = getvalue(&buf, TRUE);
		if ((tone < 1) || (tone > 128))
		{
			return;
		}
		if (*buf == ':')
		{
			buf++;
			bank = tone - 1;
			tone = getvalue(&buf, TRUE);
			if ((tone < 1) || (tone > 128))
			{
				return;
			}
			TONEBANK[mod][num] = bank;
		}
		TONEMAP[mod][num] = tone - 1;
	}
}

int MIDI_SetMimpiMap(char *filename)
{
	uint8_t b;
	FILEH *fh;
	char buf[128];

	LOADED_TONEMAP = 0;
	memset(TONE_CH, 0, sizeof(TONE_CH));
	memset(TONEBANK[0], 0, sizeof(TONEBANK));
	for (b = 0; b < 128; b++)
	{
		TONEMAP[0][b] = b;
		TONEMAP[1][b] = b;
		TONEMAP[2][b] = b;
	}
	TONE_CH[9] = MIMPI_RHYTHM;

	if ((filename == NULL) || (!filename[0]))
	{
		ENABLE_TONEMAP = 0;
		return (FALSE);
	}
	fh = file_open_rb(filename);
	if (fh == NULL)
	{
		ENABLE_TONEMAP = 0;
		return (FALSE);
	}
	while (file_readline(fh, buf, sizeof(buf)) >= 0)
	{
		mimpidefline_analaize(buf);
	}
	file_close(fh);

	LOADED_TONEMAP = 1;
	return (TRUE);
}

int MIDI_EnableMimpiDef(int enable)
{
	ENABLE_TONEMAP = 0;
	if ((enable) && (LOADED_TONEMAP))
	{
		ENABLE_TONEMAP = 1;
		return (TRUE);
	}
	return (FALSE);
}
