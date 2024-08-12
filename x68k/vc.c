/*
 *  VC.C - Video Contoller
 */

#include "../x11/common.h"
#include "../x11/state.h"

#include "crtc.h"
#include "palette.h"
#include "tvram.h"
#include "vc.h"

/* Video control register */

/* The color mode of Reg0 looks the same as CRTC at first glance, but note that
 * it has a different role. CRTC changes the way GVRAM is accessed (how it
 * appears on the memory map), while VCtrl controls how GVRAM is expanded on the
 * screen. In other words, it is permissible to use it in such a way that the
 * access method (CRTC) is 16-bit mode and the display is 256-color mode. It is
 * used when Cotton starts up and in the opening of Ys (radio version).
 */

/*
 * $e82000 256.w -- Graphics Palette
 * $e82200 256.w -- Text Palette, Sprite + BG Palette
 * $e82400 1.w R0 screen mode
 * $e82500 1.w R1 priority control
 * $e82600 1.w R2 ON/OFF control/special priority
 */

uint8_t VCReg0[2] = { 0, 0 };
uint8_t VCReg1[2] = { 0, 0 };
uint8_t VCReg2[2] = { 0, 0 };

uint8_t FASTCALL VCtrl_Read(uint32_t adr)
{
	adr &= 0xfff;

	if (adr < 0x400)
	{
		return Pal_Regs[adr];
	}

	if (adr < 0x500)
	{
		return VCReg0[adr & 1];
	}

	if (adr < 0x600)
	{
		return VCReg1[adr & 1];
	}

	if (adr < 0x700)
	{
		return VCReg2[adr & 1];
	}

	return 0xff;
}

void FASTCALL VCtrl_Write(uint32_t adr, uint8_t data)
{
	adr &= 0xfff;

	if (adr < 0x400)
	{
		uint16_t pal;

		if (Pal_Regs[adr] == data)
			return;

		Pal_Regs[adr] = data;
		TVRAM_SetAllDirty();

		pal = Pal_Regs[adr & 0x3fe];
		pal = (pal << 8) + Pal_Regs[(adr & 0x3fe) + 1];

		if (adr < 0x200)
		{
			GrphPal[adr / 2] = Pal16[pal];
		}
		else if (adr < 0x400)
		{
			/* TODO: verify:
			 * It seems that TextPal does not allow byte access (Kobe Love
			 * Story)> */
			TextPal[(adr - 0x200) / 2] = Pal16[pal];
		}
	}
	else if (adr < 0x500)
	{
		if (VCReg0[adr & 1] != data)
		{
			VCReg0[adr & 1] = data;
			TVRAM_SetAllDirty();
		}
	}
	else if (adr < 0x600)
	{
		if (VCReg1[adr & 1] != data)
		{
			VCReg1[adr & 1] = data;
			TVRAM_SetAllDirty();
		}
	}
	else if (adr < 0x700)
	{
		if (VCReg2[adr & 1] != data)
		{
			VCReg2[adr & 1] = data;
			TVRAM_SetAllDirty();
		}
	}
}

int VCtrl_StateContext(void *f, int writing)
{
	state_context_f(VCReg0, sizeof(VCReg0));
	state_context_f(VCReg1, sizeof(VCReg1));
	state_context_f(VCReg2, sizeof(VCReg2));

	return 1;
}
