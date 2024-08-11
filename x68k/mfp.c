/* MFP.C - MFP (Multi-Function Periferal) */

#include "../x11/common.h"
#include "../m68000/m68000.h"

#include "../x11/keyboard.h"
#include "../x11/winx68k.h"

#include "mfp.h"
#include "crtc.h"
#include "irqh.h"
#include "../x11/state.h"

uint8_t MFP[24];
uint8_t LastKey                     = 0;
uint8_t Timer_TBO                   = 0;
static uint8_t Timer_Reload[4]      = { 0, 0, 0, 0 };
static int32_t Timer_Tick[4]        = { 0, 0, 0, 0 };
static const int Timer_Prescaler[8] = { 1, 10, 25, 40, 125, 160, 250, 500 };
static const int TimerInt[4]        = { 2, 7, 10, 11 };

/* Check for priority interrupt and return the corresponding vector */
static int32_t FASTCALL MFP_IntCallback(int32_t irq)
{
	uint8_t flag;
	int32_t vect;
	int offset = 0;

	IRQH_IRQCallBack(irq);

	if (irq != 6)
		return IRQ_DEFAULT_VECTOR;

	for (flag = 0x80, vect = 15; flag; flag >>= 1, vect--)
	{
		if ((MFP[MFP_IPRA] & flag) && (MFP[MFP_IMRA] & flag) && (!(MFP[MFP_ISRA] & flag)))
			break;
	}
	if (!flag)
	{
		offset = 1;
		for (flag = 0x80, vect = 7; flag; flag >>= 1, vect--)
		{
			if ((MFP[MFP_IPRB] & flag) && (MFP[MFP_IMRB] & flag) && (!(MFP[MFP_ISRB] & flag)))
				break;
		}
	}
	if (!flag)
	{
		Error("MFP Int w/o Request. Default Vector(-1) has been returned.");
		return IRQ_DEFAULT_VECTOR;
	}

	MFP[MFP_IPRA + offset] &= (~flag);
	if (MFP[MFP_VR] & 8)
		MFP[MFP_ISRA + offset] |= flag;
	vect |= (MFP[MFP_VR] & 0xf0);
	for (flag = 0x80; flag; flag >>= 1)
	{
		if ((MFP[MFP_IPRA] & flag) && (MFP[MFP_IMRA] & flag) && (!(MFP[MFP_ISRA] & flag)))
		{
			IRQH_Int(6, &MFP_IntCallback);
			break;
		}
		if ((MFP[MFP_IPRB] & flag) && (MFP[MFP_IMRB] & flag) && (!(MFP[MFP_ISRB] & flag)))
		{
			IRQH_Int(6, &MFP_IntCallback);
			break;
		}
	}
	return vect;
}

/* Check if the interrupt has been cancelled */
static void MFP_RecheckInt(void)
{
	uint8_t flag;
	IRQH_IRQCallBack(6);
	for (flag = 0x80; flag; flag >>= 1)
	{
		if ((MFP[MFP_IPRA] & flag) && (MFP[MFP_IMRA] & flag) && (!(MFP[MFP_ISRA] & flag)))
		{
			IRQH_Int(6, &MFP_IntCallback);
			break;
		}
		if ((MFP[MFP_IPRB] & flag) && (MFP[MFP_IMRB] & flag) && (!(MFP[MFP_ISRB] & flag)))
		{
			IRQH_Int(6, &MFP_IntCallback);
			break;
		}
	}
}

/* Interrupt occurred */
void MFP_Int(int irq)
{
	uint8_t flag = 0x80;

	/* 'irq' has the highest priority of 0 (HSYNC/GPIP7) and the lowest priority of 15 (ALARM)*/
	/* Note that the numbering is the opposite to that of vectors. */

	if (irq < 8)
	{
		flag >>= irq;
		if (MFP[MFP_IERA] & flag)
		{
			MFP[MFP_IPRA] |= flag;
			if ((MFP[MFP_IMRA] & flag) && (!(MFP[MFP_ISRA] & flag)))
			{
				IRQH_Int(6, &MFP_IntCallback);
			}
		}
	}
	else
	{
		irq -= 8;
		flag >>= irq;
		if (MFP[MFP_IERB] & flag)
		{
			MFP[MFP_IPRB] |= flag;
			if ((MFP[MFP_IMRB] & flag) && (!(MFP[MFP_ISRB] & flag)))
			{
				IRQH_Int(6, &MFP_IntCallback);
			}
		}
	}
}

void MFP_Init(void)
{
	static const uint8_t initregs[24] = {
		0x7b, 0x06, 0x00, 0x18, 0x3e, 0x00, 0x00, 0x00,
		0x00, 0x18, 0x3e, 0x40, 0x08, 0x01, 0x77, 0x01,
		0x0d, 0xc8, 0x14, 0x00, 0x88, 0x01, 0x81, 0x00
	};
	int i;

	memcpy(MFP, initregs, 24);
	for (i = 0; i < 4; i++)
		Timer_Tick[i] = 0;
}

static uint8_t GetGPIP(void)
{
	uint8_t ret = 0x20; /* bit 5 is always 1 */
	int hpos    = (int)(ICount % HSYNC_CLK);

	if ((vline >= CRTC_VSTART) && (vline < CRTC_VEND))
	{
		ret |= 0x13;
	}
	else
	{
		ret |= 0x03;
	}

	if ((hpos >= ((int)CRTC_Regs[0x05] * HSYNC_CLK / CRTC_Regs[0x01])) &&
		(hpos < ((int)CRTC_Regs[0x07] * HSYNC_CLK / CRTC_Regs[0x01])))
	{
		ret &= 0x7f;
	}
	else
	{
		ret |= 0x80;
	}

	if (vline != CRTC_IntLine)
	{
		ret |= 0x40;
	}

	return ret;
}

static uint8_t GetRSR(void)
{
	if (KeyBufRP != KeyBufWP)
		return MFP[MFP_RSR] & 0x7f;
	return MFP[MFP_RSR] | 0x80;
}

static uint8_t GetUDR(void)
{
	uint8_t ret = LastKey;
	KeyIntFlag = 0;
	return ret;
}

/* I/O Read */
uint8_t FASTCALL MFP_Read(uint32_t adr)
{
	if ((adr & 1) != 0)
	{
		uint8_t reg = (adr & 0x3f) >> 1;

		switch (reg)
		{
		case MFP_GPIP:
			return GetGPIP();

		case MFP_RSR:
			return GetRSR();

		case MFP_UDR:
			return GetUDR();

		default:
			if (reg <= MFP_UDR)
			{
				return MFP[reg];
			}

			p6logd(" Read unimplemented register $%06x\n", adr);
			return 0xff;
		}
	}

	return 0xff;
}

/* I/O Write */
void FASTCALL MFP_Write(uint32_t adr, uint8_t data)
{
	uint8_t reg;

	if ((adr & 1) == 0)
		return;

	reg = (adr & 0x3f) >> 1;

	switch (reg)
	{
	case MFP_IERA:
	case MFP_IERB:
		MFP[reg] = data;
		MFP[reg + 2] &= data; /* Prohibited items drop IPRA/B */
		MFP_RecheckInt();
		return;

	case MFP_IPRA:
	case MFP_IPRB:
	case MFP_ISRA:
	case MFP_ISRB:
		MFP[reg] &= data;
		MFP_RecheckInt();
		return;

	case MFP_IMRA:
	case MFP_IMRB:
		MFP[reg] = data;
		MFP_RecheckInt();
		return;

	case MFP_TACR:
		MFP[reg] = data;
		return;

	case MFP_TBCR:
		MFP[reg] = data;
#if 0
			if (MFP[reg] & 0x10)
				Timer_TBO = 0; /* then what? */
#endif
		return;

	case MFP_TCDCR:
		MFP[reg] = data;
		return;

	case MFP_TADR:
		Timer_Reload[0] = MFP[reg] = data;
		return;

	case MFP_TBDR:
		Timer_Reload[1] = MFP[reg] = data;
		return;

	case MFP_TCDR:
		Timer_Reload[2] = MFP[reg] = data;
		return;

	case MFP_TDDR:
		Timer_Reload[3] = MFP[reg] = data;
		return;

	case MFP_TSR:
		MFP[reg] = data | 0x80; /* Tx is always enabled */
		return;

	case MFP_UDR:
		return;

	default:
		if (reg <= MFP_UDR)
		{
			MFP[reg] = data;
			return;
		}
		break;
	}

	p6logd(" Write unimplemented register $%06x <- $%02x\n", adr, data);
}

/* Advance the current time (let's rewrite it a bit more neatly...) */
void FASTCALL MFP_Timer(int32_t clock)
{
	int chan;

	for (chan = 0; chan < 4; chan++)
	{
		int mode;

		switch (chan)
		{
		case 2:
			mode = MFP[MFP_TCDCR] >> 4;
			break;

		case 3:
			mode = MFP[MFP_TCDCR];
			break;

		default:
			mode = MFP[MFP_TACR + chan];
			break;
		}

		if (!((chan == 0) && (mode & 8)) && (mode & 7))
		{
			int t = Timer_Prescaler[mode & 7];
			Timer_Tick[chan] += clock;
			while (Timer_Tick[chan] >= t)
			{
				Timer_Tick[chan] -= t;
				MFP[MFP_TADR + chan]--;
				if (MFP[MFP_TADR + chan] == 0)
				{
					MFP[MFP_TADR + chan] = Timer_Reload[chan];
					MFP_Int(TimerInt[chan]);
				}
			}
		}
	}
}

void FASTCALL MFP_TimerA(void)
{
	if ((MFP[MFP_TACR] & 15) == 8)
	{
		/* Event and count mode (counted by VDisp) */
		if (MFP[MFP_AER] & 0x10)
		{
			/* If you're wondering about the difference in timing with the VDisp interrupt, that's a bit concerning (lol) */
			if (vline == CRTC_VSTART)
				MFP[MFP_TADR]--; /* I think it's the same thing but... it won't work (sweat */
		}
		else
		{
			if (CRTC_VEND >= VLINE_TOTAL)
			{
				if ((long)vline == (VLINE_TOTAL - 1))
					MFP[MFP_TADR]--; /* Counting at the end of the display period... (load) */
			}
			else
			{
				if (vline == CRTC_VEND)
					MFP[MFP_TADR]--;
			}
		}
		if (!MFP[MFP_TADR])
		{
			MFP[MFP_TADR] = Timer_Reload[0];
			MFP_Int(2);
		}
	}
}

int MFP_StateContext(void *f, int writing) {
	state_context_f(MFP, sizeof(MFP));
	state_context_f(&LastKey, sizeof(LastKey));
	state_context_f(&Timer_TBO, sizeof(Timer_TBO));
	state_context_f(Timer_Reload, sizeof(Timer_Reload));
	state_context_f(Timer_Tick, sizeof(Timer_Tick));

	return 1;
}
