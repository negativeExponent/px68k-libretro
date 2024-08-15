/*
 *  ADPCM.C - ADPCM (OKI MSM6258V)
 *    For some reason, the sound is more scratchy than with X68Sound.dll...
 *    It could be a quirk of DSound, but I don't think that's the only reason
 */

#include <math.h>

#include "../x11/common.h"
#include "../x11/prop.h"
#include "../x11/state.h"

#include "adpcm.h"
#include "dmac.h"
#include "pia.h"

#define ADPCM_BufSize 48000 * 2
#define ADPCMMAX      2047
#define ADPCMMIN      -2048
#define FM_IPSCALE    256L

#define OVERSAMPLEMUL 2

#define INTERPOLATE(y, x)	\
	(((((((-y[0]+3*y[1]-3*y[2]+y[3]) * x + FM_IPSCALE/2) / FM_IPSCALE \
	+ 3 * (y[0]-2*y[1]+y[2])) * x + FM_IPSCALE/2) / FM_IPSCALE \
	- 2*y[0]-3*y[1]+6*y[2]-y[3]) * x + 3*FM_IPSCALE) / (6*FM_IPSCALE) + y[1])

static const int32_t index_shift[8] = {
	-1, -1, -1, -1, 2, 4, 6, 8
};
static const int32_t index_table[58] = {
	0, 0,
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 26,	27,	28, 29, 30,	31, 32,
	33, 34,	35, 36, 37, 38,	39, 40,
	41, 42,	43, 44, 45, 46,	47, 48,
	48, 48, 48, 48, 48, 48,	48, 48
};
static const int32_t ADPCM_Clocks[8] = {
	93750, 125000, 187500, 125000, 46875, 62500, 93750, 62500
};
static int32_t dif_table[49 * 16];

static int16_t ADPCM_BufR[ADPCM_BufSize];
static int16_t ADPCM_BufL[ADPCM_BufSize];

static int32_t ADPCM_VolumeShift = 65536;
static int32_t ADPCM_WrPtr       = 0;
static int32_t ADPCM_RdPtr       = 0;

static uint32_t ADPCM_SampleRate = 44100 * 12;
static uint32_t ADPCM_ClockRate  = 7800 * 12;
static uint32_t ADPCM_Count      = 0;

static int32_t ADPCM_Step        = 0;
static int32_t ADPCM_Out         = 0;
static uint8_t ADPCM_Playing     = 0;
static uint8_t ADPCM_Clock       = 0;
static int32_t ADPCM_PreCounter  = 0;
static int32_t ADPCM_DifBuf      = 0;
static uint8_t ADPCM_Ratio       = 0;
static uint8_t ADPCM_Pan         = 0;

static int32_t OldR = 0, OldL = 0;
static int32_t Outs[8];
static int32_t OutsIp[4];
static int32_t OutsIpR[4];
static int32_t OutsIpL[4];

int ADPCM_IsReady(void)
{
	return 1;
}

static void ADPCM_InitTable(void)
{
	static int32_t bit[16][4] = {
		{ 1, 0, 0, 0 },  { 1, 0, 0, 1 },  { 1, 0, 1, 0 },  { 1, 0, 1, 1 },
		{ 1, 1, 0, 0 },  { 1, 1, 0, 1 },  { 1, 1, 1, 0 },  { 1, 1, 1, 1 },
		{ -1, 0, 0, 0 }, { -1, 0, 0, 1 }, { -1, 0, 1, 0 }, { -1, 0, 1, 1 },
		{ -1, 1, 0, 0 }, { -1, 1, 0, 1 }, { -1, 1, 1, 0 }, { -1, 1, 1, 1 }
	};
	int32_t step, n;
	double val;

	for (step = 0; step <= 48; step++)
	{
		val = floor(16.0 * pow((double)1.1, (double)step));
		for (n = 0; n < 16; n++)
		{
			dif_table[step * 16 + n] =
			    bit[n][0] * (int32_t)(val * bit[n][1] +
				val / 2 * bit[n][2] +
				val / 4 * bit[n][3] +
				val / 8);
		}
	}
}

/* Store data in the buffer for the number of MPU clock cycles */
void FASTCALL ADPCM_PreUpdate(int32_t clock)
{
#if 0
	/*if (!ADPCM_Playing) return;*/
#endif
	ADPCM_PreCounter += ((ADPCM_ClockRate / 24) * clock);
	while (ADPCM_PreCounter >= 10000000L)
	{
		/* Preventing excessive data transmission (A-JAX). I'll allow up to 200 samples... */
		ADPCM_DifBuf -= ((ADPCM_SampleRate * 400) / ADPCM_ClockRate);
		if (ADPCM_DifBuf <= 0)
		{
			ADPCM_DifBuf = 0;
			DMA_Exec(3);
		}
		ADPCM_PreCounter -= 10000000L;
	}
}

/* Write data to the buffer */
void FASTCALL ADPCM_Update(int16_t *buffer, int32_t length, int16_t *pbsp, int16_t *pbep)
{
	if (length <= 0)
		return;

	while (length)
	{
		int32_t outs;
		int32_t outl, outr;
		int32_t tmpl, tmpr;

		if (buffer >= pbep)
		{
			buffer = pbsp;
		}

		if ((ADPCM_WrPtr == ADPCM_RdPtr) && (!(DMA[3].CCR & 0x40)))
			DMA_Exec(3);
		if (ADPCM_WrPtr != ADPCM_RdPtr)
		{
			OldR = outr = ADPCM_BufL[ADPCM_RdPtr];
			OldL = outl = ADPCM_BufR[ADPCM_RdPtr];
			ADPCM_RdPtr++;
			if (ADPCM_RdPtr >= ADPCM_BufSize)
				ADPCM_RdPtr = 0;
		}
		else
		{
			outr = OldR;
			outl = OldL;
		}

		if (Config.Sound_LPF)
		{
			outr    = (int32_t)(outr * 40 * ADPCM_VolumeShift);
			outs    = (outr + Outs[3] * 2 + Outs[2] + Outs[1] * 157 - Outs[0] * 61) >> 8;
			Outs[2] = Outs[3];
			Outs[3] = outr;
			Outs[0] = Outs[1];
			Outs[1] = outs;
		}
		else
		{
			outs = (int32_t)(outr * ADPCM_VolumeShift);
		}

		OutsIpR[0] = OutsIpR[1];
		OutsIpR[1] = OutsIpR[2];
		OutsIpR[2] = OutsIpR[3];
		OutsIpR[3] = outs;

		if (Config.Sound_LPF)
		{
			outl    = (int32_t)(outl * 40 * ADPCM_VolumeShift);
			outs    = (outl + Outs[7] * 2 + Outs[6] + Outs[5] * 157 - Outs[4] * 61) >> 8;
			Outs[6] = Outs[7];
			Outs[7] = outl;
			Outs[4] = Outs[5];
			Outs[5] = outs;
		}
		else
		{
			outs = (int32_t)(outl * ADPCM_VolumeShift);
		}

		OutsIpL[0] = OutsIpL[1];
		OutsIpL[1] = OutsIpL[2];
		OutsIpL[2] = OutsIpL[3];
		OutsIpL[3] = outs;

#if 1
		tmpr = INTERPOLATE(OutsIpR, 0);
		if (tmpr > 32767)
			tmpr = 32767;
		else if (tmpr < (-32768))
			tmpr = -32768;
		*(buffer++) = (int16_t)tmpr;

		tmpl = INTERPOLATE(OutsIpL, 0);
		if (tmpl > 32767)
			tmpl = 32767;
		else if (tmpl < (-32768))
			tmpl = -32768;
		*(buffer++) = (int16_t)tmpl;
#else
		*(buffer++) = (int16_t)OutsIpR[3];
		*(buffer++) = (int16_t)OutsIpL[3];
#endif

		length--;
	}

	ADPCM_DifBuf = ADPCM_WrPtr - ADPCM_RdPtr;
	if (ADPCM_DifBuf < 0)
		ADPCM_DifBuf += ADPCM_BufSize;
}

/* Decode 1 nibble (4 bits) */
static INLINE void ADPCM_WriteOne(uint8_t val)
{
	ADPCM_Out += dif_table[(ADPCM_Step << 4) + val];

	if (ADPCM_Out > ADPCMMAX)
		ADPCM_Out = ADPCMMAX;
	else if (ADPCM_Out < ADPCMMIN)
		ADPCM_Out = ADPCMMIN;

	ADPCM_Step += index_shift[val & 0x07];
	ADPCM_Step = index_table[ADPCM_Step + 1];

	if (OutsIp[0] == -1)
	{
		OutsIp[0] = OutsIp[1] = OutsIp[2] = OutsIp[3] = ADPCM_Out;
	}
	else
	{
		OutsIp[0] = OutsIp[1];
		OutsIp[1] = OutsIp[2];
		OutsIp[2] = OutsIp[3];
		OutsIp[3] = ADPCM_Out;
	}

	while (ADPCM_SampleRate > ADPCM_Count)
	{
		if (ADPCM_Playing)
		{
			int32_t ratio = (((ADPCM_Count / 100) * FM_IPSCALE) / (ADPCM_SampleRate / 100));
			int32_t tmp   = INTERPOLATE(OutsIp, ratio);

			if (tmp > ADPCMMAX)
				tmp = ADPCMMAX;
			else if (tmp < ADPCMMIN)
				tmp = ADPCMMIN;

			if (!(ADPCM_Pan & 1))
				ADPCM_BufR[ADPCM_WrPtr] = (int16_t)tmp;
			else
				ADPCM_BufR[ADPCM_WrPtr] = 0;

			if (!(ADPCM_Pan & 2))
				ADPCM_BufL[ADPCM_WrPtr++] = (int16_t)tmp;
			else
				ADPCM_BufL[ADPCM_WrPtr++] = 0;
			if (ADPCM_WrPtr >= ADPCM_BufSize)
				ADPCM_WrPtr = 0;
		}
		ADPCM_Count += ADPCM_ClockRate;
	}
	ADPCM_Count -= ADPCM_SampleRate;
}

void FASTCALL ADPCM_Write(uint32_t adr, uint8_t data)
{
	if (adr & 1)
	{
		adr &= 3;

		if (adr == 1)
		{
			if (data & 1)
			{
				ADPCM_Playing = 0;
			}
			else if (data & 2)
			{
				if (!ADPCM_Playing)
				{
					ADPCM_Step = 0;
					ADPCM_Out = 0;
					OldL = OldR = -2;
					ADPCM_Playing = 1;
				}
				OutsIp[0] = OutsIp[1] = OutsIp[2] = OutsIp[3] = -1;
			}
		}
		else if (adr == 3)
		{
			if (ADPCM_Playing)
			{
				ADPCM_WriteOne((uint8_t)(data & 15));
				ADPCM_WriteOne((uint8_t)((data >> 4) & 15));
			}
		}
	}
}

uint8_t FASTCALL ADPCM_Read(uint32_t adr)
{
	/* adpcm status */
	if (adr & 1)
	{
		/* bit 7 : 0:playing 1:recording/standby */
		if (ADPCM_Playing) {
			return 0x7f;
		}
		return 0xff;
	}

	return 0xff;
}

void ADPCM_SetVolume(uint8_t vol)
{
	if (vol > 16)
		vol = 16;

	if (vol)
		ADPCM_VolumeShift = (int32_t)((double)16 / pow(1.189207115, (16 - vol)));
	else
		ADPCM_VolumeShift = 0;
}

static void ADPCM_CalcClockRate(void)
{
	int lut = (ADPCM_Clock & 4) | (ADPCM_Ratio & 3);
	ADPCM_Count     = 0;
	ADPCM_ClockRate = ADPCM_Clocks[lut];
}

void ADPCM_SetClock(uint8_t clock)
{
	ADPCM_Clock = clock;
	ADPCM_CalcClockRate();
}

void ADPCM_SetRatio(uint8_t ratio)
{
	if (ADPCM_Ratio != ratio)
	{
		ADPCM_Ratio = ratio;
		ADPCM_CalcClockRate();
	}
}

void ADPCM_SetPan(uint8_t pan)
{
	ADPCM_Pan = pan;
}

void ADPCM_Init(uint32_t samplerate)
{
	ADPCM_WrPtr      = 0;
	ADPCM_RdPtr      = 0;
	ADPCM_Out        = 0;
	ADPCM_Step       = 0;
	ADPCM_Playing    = 0;
	ADPCM_SampleRate = (samplerate * 12);
	ADPCM_PreCounter = 0;

	memset(Outs, 0, sizeof(Outs));

	OutsIp[0] = OutsIp[1] = OutsIp[2] = OutsIp[3] = -1;

	OutsIpR[0] = OutsIpR[1] = OutsIpR[2] = OutsIpR[3] = 0;
	OutsIpL[0] = OutsIpL[1] = OutsIpL[2] = OutsIpL[3] = 0;

	OldL = OldR = 0;

	ADPCM_Clock = 0;
	ADPCM_Pan = 3;
	ADPCM_Ratio = 2;

	ADPCM_CalcClockRate();

	ADPCM_InitTable();
}

int ADPCM_StateContext(void *f, int writing) {
	state_context_f(ADPCM_BufL, sizeof(ADPCM_BufL));
	state_context_f(ADPCM_BufR, sizeof(ADPCM_BufR));

	state_context_f(&ADPCM_VolumeShift, sizeof(ADPCM_VolumeShift));
	state_context_f(&ADPCM_WrPtr, sizeof(ADPCM_WrPtr));
	state_context_f(&ADPCM_RdPtr, sizeof(ADPCM_RdPtr));

	state_context_f(&ADPCM_ClockRate, sizeof(ADPCM_ClockRate));
	state_context_f(&ADPCM_Count, sizeof(ADPCM_Count));

	state_context_f(&ADPCM_Step, sizeof(ADPCM_Step));
	state_context_f(&ADPCM_Out, sizeof(ADPCM_Out));
	state_context_f(&ADPCM_Playing, sizeof(ADPCM_Playing));
	state_context_f(&ADPCM_Clock, sizeof(ADPCM_Clock));
	state_context_f(&ADPCM_PreCounter, sizeof(ADPCM_PreCounter));
	state_context_f(&ADPCM_DifBuf, sizeof(ADPCM_DifBuf));

	state_context_f(&ADPCM_Pan, sizeof(ADPCM_Pan));
	state_context_f(&ADPCM_Ratio, sizeof(ADPCM_Ratio));
	state_context_f(&OldR, sizeof(OldR));
	state_context_f(&OldL, sizeof(OldL));
	state_context_f(Outs, sizeof(Outs));
	state_context_f(OutsIp, sizeof(OutsIp));
	state_context_f(OutsIpR, sizeof(OutsIpR));
	state_context_f(OutsIpL, sizeof(OutsIpL));

	return 1;

}
