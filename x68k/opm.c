/*
 * OPM.C OPM Interface for FMGEN OPM Generator
 */

#include "../x11/common.h"
#include "adpcm.h"
#include "fdc.h"

#include "../fmgen/fmg_wrap.h"

#include "../x68k/opm.h"

#include "../x11/state.h"

typedef struct 
{
	uint32_t adr;
	uint32_t count;
	uint8_t reg1b;
	uint8_t busy;
	uint16_t reserve16;
	uint32_t reserve32;
} opmif_t;

static opmif_t opm;
static void *myOPM;

static void Reset(void)
{
	int i;

	memset(&opm, 0, sizeof(opm));

	if (myOPM)
	{
		for (i = 0; i < 0x100; i++)
		{
			if (i == 8)
			{
				continue;
			}
			if ((i >= 0x60) && (i <= 0x7f))
			{
				opm_setreg(myOPM, i, 0x7f);
				continue;
			}
			if ((i >= 0xe0) && (i <= 0xff))
			{
				opm_setreg(myOPM, i, 0xff);
				continue;
			}
			opm_setreg(myOPM, i, 0);
		}
		opm_setreg(myOPM, 0x19, 0x80);
		for (i = 0; i < 8; i++)
		{
			opm_setreg(myOPM, 8, i);
		}
	}
}

int OPM_Init(int32_t clock, int32_t rate)
{
	myOPM = opm_new(clock, rate);

	if (!myOPM)
	{
		return 0;
	}

	Reset();
	return 1;
}

void OPM_SetRate(int32_t clock, int32_t rate)
{
	if (myOPM)
	{
		opm_setrate(myOPM, clock, rate);
	}
}

void OPM_Cleanup(void)
{
	if (myOPM)
	{
		opm_delete(myOPM);
		myOPM = NULL;
	}
}

void OPM_Reset(void)
{
	if (myOPM)
	{
		opm_reset(myOPM);
		Reset();
	}
}

uint8_t FASTCALL OPM_Read(uint32_t adr)
{
	if ((adr & 1) != 0)
	{
		adr &= 3;

		if (adr != 1)
		{
			uint8_t ret = 0;

			if (opm.busy)
			{
				ret |= 0x80;
				opm.busy = 0;
			}
			
			if (myOPM)
			{
				ret = opm_readstatus(myOPM) & 3;
			}

			return ret;
		}

		return 0xff;
	}

	return 0xff;
}

void FASTCALL OPM_Write(uint32_t adr, uint8_t data)
{
	if ((adr & 1) != 0)
	{
		adr &= 3;

		if (adr == 1)
		{
			opm.adr = data;
			opm.busy = 0;
		}
		else
		{
			if (opm.adr == 0x1b)
			{
				if ((data & 0xc0) != (opm.reg1b & 0xc0))
				{
					uint32_t ct = opm.reg1b & 0xc0;

					if ((data & 0x80) != (ct & 0x80))
					{
						ADPCM_SetClock((data >> 5) & 4);
					}
				
					if ((data & 0x40) != (ct & 0x40))
					{
						FDC_SetForceReady((data >> 6) & 1);
					}
				}

				opm.reg1b = data; /* cache addr 0x1b data */
			}

			if (myOPM)
			{
				opm_setreg(myOPM, opm.adr, data);
			}
			
			opm.busy = 1;
		}
	}
}

void OPM_Update(int16_t *buffer, int32_t length, int16_t *pbsp, int16_t *pbep)
{
	if (myOPM)
	{
		opm_mix(myOPM, buffer, length, pbsp, pbep);
	}
}

void FASTCALL OPM_Timer(uint32_t step)
{
	opm.count += step;

	if (myOPM)
	{
		opm_count(myOPM, opm.count / 10);
	}

	opm.count %= 10;
}

void OPM_SetVolume(uint8_t vol)
{
	if (myOPM)
	{
		int32_t v = (vol) ? ((16 - vol) * 4) : 192;
		opm_setvolume(myOPM, -v);
	}
}

void OPM_SetChannelMask(uint32_t mask)
{
	if (myOPM)
	{
		opm_setchannelmask(myOPM, mask);
	}
}

void OPM_RomeoOut(uint32_t delay) { }

int OPM_StateContext(void *f, int writing)
{
	state_context_f(&opm.adr, sizeof(opm.adr));
	state_context_f(&opm.count, sizeof(opm.count));
	state_context_f(&opm.reg1b, sizeof(opm.reg1b));
	state_context_f(&opm.busy, sizeof(opm.busy));
	state_context_f(&opm.reserve16, sizeof(opm.reserve16));
	state_context_f(&opm.reserve32, sizeof(opm.reserve32));

	if (myOPM) {
		opm_statecontext(myOPM, f, writing);
	}

	return 1;
}
