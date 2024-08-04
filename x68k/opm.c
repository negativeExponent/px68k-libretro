/*
 * OPM.C OPM Interface for FMGEN OPM Generator
 */

#include "../x11/common.h"
#include "adpcm.h"
#include "fdc.h"

#include "../fmgen/fmg_wrap.h"

#include "../x68k/opm.h"

#include "../x11/state.h"

static int32_t CurReg;
static uint32_t CurCount;

static void *opm = NULL;

int OPM_Init(int32_t clock, int32_t rate)
{
	if (!(opm = opm_new(clock, rate)))
	{
		return FALSE;
	}

	return TRUE;
}

void OPM_SetRate(int32_t clock, int32_t rate)
{
	opm_setrate(opm, clock, rate);
}

void OPM_Cleanup(void)
{
	opm_delete(opm);
	opm = NULL;
}

void OPM_Reset(void)
{
	if (!opm)
	{
		return;
	}

	opm_reset(opm);
}

uint8_t FASTCALL OPM_Read(uint32_t adr)
{
	if (!opm)
	{
		return 0xff;
	}

	if ((adr & 3) == 3)
	{
		return opm_readstatus(opm);
	}

	return 0xff;
}

void FASTCALL OPM_Write(uint32_t adr, uint8_t data)
{
	if (!opm) {
		return;
	}

	if (adr & 1)
	{
		if ((adr & 3) == 3)
		{
			if (CurReg == 0x1b)
			{
				ADPCM_SetClock((data >> 5) & 4);
				FDC_SetForceReady((data >> 6) & 1);
			}
			opm_setreg(opm, (int32_t)CurReg, (int32_t)data);
		}
		else
		{
			CurReg = (int32_t)data;
		}
	}
}

void OPM_Update(int16_t *buffer, int32_t length, int16_t *pbsp, int16_t *pbep)
{
	if (!opm)
	{
		return;
	}

	opm_mix(opm, buffer, length, pbsp, pbep);
}

void FASTCALL OPM_Timer(uint32_t step)
{
	if (!opm)
	{
		return;
	}

	CurCount += step;
	opm_count(opm, CurCount / 10);
	CurCount %= 10;
}

void OPM_SetVolume(uint8_t vol)
{
	int32_t v = (vol) ? ((16 - vol) * 4) : 192; /* このくらいかなぁ */

	if (!opm)
	{
		return;
	}

	opm_setvolume(opm, -v);
}

void OPM_SetChannelMask(uint32_t mask)
{
	opm_setchannelmask(opm, mask);
}

void OPM_RomeoOut(uint32_t delay) { }

int OPM_StateContext(void *f, int writing)
{
	state_context_f(&CurReg, 4);
	state_context_f(&CurCount, 4);

	if (opm) {
		opm_statecontext(opm, f, writing);
	}

	return 1;
}
