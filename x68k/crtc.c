/* CRTC.C - CRT Controller */

#include "../x11/common.h"
#include "../x11/windraw.h"
#include "../x11/winx68k.h"

#include "crtc.h"
#include "bg.h"
#include "palette.h"
#include "tvram.h"

#include "../x11/state.h"

static uint16_t FastClearMask[16] = {
	0xffff, 0xfff0, 0xff0f, 0xff00, 0xf0ff, 0xf0f0, 0xf00f, 0xf000,
	0x0fff, 0x0ff0, 0x0f0f, 0x0f00, 0x00ff, 0x00f0, 0x000f, 0x0000
};

uint8_t  CRTC_Regs[24 * 2];
uint8_t  CRTC_Mode = 0;
uint32_t TextDotX = 768;
uint32_t TextDotY = 512;
uint16_t CRTC_VSTART = 0, CRTC_VEND = 0;
uint16_t CRTC_HSTART = 0, CRTC_HEND = 0;
uint32_t TextScrollX = 0, TextScrollY = 0;
uint32_t GrphScrollX[4] = { 0, 0, 0, 0 };
uint32_t GrphScrollY[4] = { 0, 0, 0, 0 };

uint8_t  CRTC_FastClr     = 0;
uint16_t CRTC_FastClrMask = 0;
uint16_t CRTC_IntLine     = 0;
uint8_t  CRTC_VStep       = 2;

static uint8_t CRTC_RCFlag[2] = { 0, 0 };

int HSYNC_CLK = 324;
extern int VID_MODE;

static void CRTC_RasterCopy(void)
{
	static const uint32_t off[4] = { 0, 0x20000, 0x40000, 0x60000 };
	uint32_t src, dst, line;
	int i, bit;

	line = (((uint32_t)CRTC_Regs[0x2d]) << 2);
	src  = (((uint32_t)CRTC_Regs[0x2c]) << 9);
	dst  = (((uint32_t)CRTC_Regs[0x2d]) << 9);

	for (bit = 0; bit < 4; bit++)
	{
		if (CRTC_Regs[0x2b] & (1 << bit))
		{
			memmove(&TVRAM[dst + off[bit]], &TVRAM[src + off[bit]], sizeof(uint32_t) * 128);
		}
	}

	line = (line - TextScrollY) & 0x3ff;

	for (i = 0; i < 4; i++)
	{
		TextDirtyLine[line] = 1;
		line                = (line + 1) & 0x3ff;
	}

	TVRAM_RCUpdate();
}

void CRTC_Init(void)
{
	const uint8_t ResetTable[] = {
		0x00, 0x89, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x7c,
		0x02, 0x37, 0x00, 0x05, 0x00, 0x28, 0x02, 0x28,
		0x00, 0x1b,
		0x0b, 0x16, 0x00, 0x33, 0x7a, 0x7b, 0x00, 0x00
	};
	int i;

	memset(GrphScrollX, 0, sizeof(GrphScrollX));
	memset(GrphScrollY, 0, sizeof(GrphScrollY));
	memset(CRTC_Regs, 0, sizeof(CRTC_Regs));
	for (i = 0; i < 18; i++)
	{
		CRTC_Regs[i] = ResetTable[i];
	}
	for (i = 0; i < 8; i++)
	{
		CRTC_Regs[i + 0x28] = ResetTable[i + 18];
	}

	CRTC_HSTART = 28;
	CRTC_HEND   = 124;
	CRTC_VSTART = 40;
	CRTC_VEND   = 552;

	TextScrollX = 0;
	TextScrollY = 0;

	TextDotX    = 768;
	TextDotY    = 512;
}

static void CRTC_ScreenChanged(void)
{
	if ((CRTC_Regs[0x29] & 0x14) == 0x10)
	{
		TextDotY /= 2;
		CRTC_VStep = 1;
	}
	else if ((CRTC_Regs[0x29] & 0x14) == 0x04)
	{
		TextDotY *= 2;
		CRTC_VStep = 4;
	}
	else
		CRTC_VStep = 2;
}

uint8_t FASTCALL CRTC_Read(uint32_t adr)
{	
	adr &= 0x7ff;

	if (adr < 0x400)
	{
		adr &= 0x3f;

		if (adr >= 0x30)
		{
			return 0xff;
		}

		if ((adr >= 0x28) && (adr <= 0x2b))
		{
			return CRTC_Regs[adr];
		}

		return 0;
	}

	if ((adr >= 0x480) && (adr <= 0x4ff))
	{
		if ((adr & 1) == 0)
		{
			return 0;
		}
		/* Notes on FastClear:
		 * When you write a 1 to the FastClr bit, the 1 will not be visible
		 * even if you read it back at that point. The bit will become 1
		 * during the first vertical blanking period after writing the 1,
		 * and erasure will begin. The erasure will end during one vertical
		 * sync period, and the bit will return to 0... PITAPAT.
		 */
		if (CRTC_FastClr)
			return CRTC_Mode | 0x02;

		return CRTC_Mode & 0xfd;
	}

	return 0xff;
}

void FASTCALL CRTC_Write(uint32_t adr, uint8_t data)
{
	adr &= 0x7ff;

	if (adr < 0x400)
	{
		adr &= 0x3f;

		if (adr >= 0x30)
		{
			return;
		}

		if (CRTC_Regs[adr] == data)
		{
			return;
		}

		CRTC_Regs[adr] = data;
		TVRAM_SetAllDirty();

		switch (adr)
		{
		case 0x00:
		case 0x01:
			/* HTOTAL */
			break;
		case 0x02:
		case 0x03:
			/* HSYNC End */
			break;
		case 0x04:
		case 0x05:
			CRTC_HSTART = (((uint16_t)CRTC_Regs[0x04] << 8) + CRTC_Regs[0x05]) & 255;
			TextDotX    = (CRTC_HEND - CRTC_HSTART) * 8;
			BG_HAdjust  = ((int32_t)BG_Regs[0x0d] - (CRTC_HSTART + 4)) * 8; /*Isn't it necessary to divide the horizontal resolution by 1/2? (Tetris) */
			WinDraw_ChangeSize();
			break;
		case 0x06:
		case 0x07:
			CRTC_HEND = (((uint16_t)CRTC_Regs[0x06] << 8) + CRTC_Regs[0x07]) & 255;
			TextDotX  = (CRTC_HEND - CRTC_HSTART) * 8;
			WinDraw_ChangeSize();
			break;
		case 0x08:
		case 0x09:
			VLINE_TOTAL = (((uint16_t)CRTC_Regs[0x08] << 8) + CRTC_Regs[0x09]) & 1023;
			HSYNC_CLK   = ((CRTC_Regs[0x29] & 0x10) ? VSYNC_HIGH : VSYNC_NORM) / VLINE_TOTAL;
			break;
		case 0x0a:
		case 0x0b:
			/* VSYNC end */
			break;
		case 0x0c:
		case 0x0d:
			CRTC_VSTART = (((uint16_t)CRTC_Regs[0x0c] << 8) + CRTC_Regs[0x0d]) & 1023;
			BG_VLINE    = ((int32_t)BG_Regs[0x0f] - CRTC_VSTART) / ((BG_Regs[0x11] & 4) ? 1 : 2); /* Difference when BG and other elements are misaligned */
			TextDotY    = CRTC_VEND - CRTC_VSTART;
			CRTC_ScreenChanged();
			WinDraw_ChangeSize();
			break;
		case 0x0e:
		case 0x0f:
			CRTC_VEND = (((uint16_t)CRTC_Regs[0x0e] << 8) + CRTC_Regs[0x0f]) & 1023;
			TextDotY  = CRTC_VEND - CRTC_VSTART;
			CRTC_ScreenChanged();
			WinDraw_ChangeSize();
			break;
		case 0x28:
			TVRAM_SetAllDirty();
			break;
		case 0x29:
			HSYNC_CLK = ((CRTC_Regs[0x29] & 0x10) ? VSYNC_HIGH : VSYNC_NORM) / VLINE_TOTAL;
			VID_MODE  = !!(CRTC_Regs[0x29] & 0x10);
			TextDotY  = CRTC_VEND - CRTC_VSTART;
			CRTC_ScreenChanged();
			WinDraw_ChangeSize();
			break;
		case 0x10:
		case 0x11:
			/* EXT sync horizontal adjust */
			break;
		case 0x12:
		case 0x13:
			CRTC_IntLine = (((uint16_t)CRTC_Regs[0x12] << 8) + CRTC_Regs[0x13]) & 1023;
			break;
		case 0x14:
		case 0x15:
			TextScrollX = (((uint32_t)CRTC_Regs[0x14] << 8) + CRTC_Regs[0x15]) & 1023;
			break;
		case 0x16:
		case 0x17:
			TextScrollY = (((uint32_t)CRTC_Regs[0x16] << 8) + CRTC_Regs[0x17]) & 1023;
			break;
		case 0x18:
		case 0x19:
			GrphScrollX[0] = (((uint32_t)CRTC_Regs[0x18] << 8) + CRTC_Regs[0x19]) & 1023;
			break;
		case 0x1a:
		case 0x1b:
			GrphScrollY[0] = (((uint32_t)CRTC_Regs[0x1a] << 8) + CRTC_Regs[0x1b]) & 1023;
			break;
		case 0x1c:
		case 0x1d:
			GrphScrollX[1] = (((uint32_t)CRTC_Regs[0x1c] << 8) + CRTC_Regs[0x1d]) & 511;
			break;
		case 0x1e:
		case 0x1f:
			GrphScrollY[1] = (((uint32_t)CRTC_Regs[0x1e] << 8) + CRTC_Regs[0x1f]) & 511;
			break;
		case 0x20:
		case 0x21:
			GrphScrollX[2] = (((uint32_t)CRTC_Regs[0x20] << 8) + CRTC_Regs[0x21]) & 511;
			break;
		case 0x22:
		case 0x23:
			GrphScrollY[2] = (((uint32_t)CRTC_Regs[0x22] << 8) + CRTC_Regs[0x23]) & 511;
			break;
		case 0x24:
		case 0x25:
			GrphScrollX[3] = (((uint32_t)CRTC_Regs[0x24] << 8) + CRTC_Regs[0x25]) & 511;
			break;
		case 0x26:
		case 0x27:
			GrphScrollY[3] = (((uint32_t)CRTC_Regs[0x26] << 8) + CRTC_Regs[0x27]) & 511;
			break;
		case 0x2a:
		case 0x2b:
			break;
		case 0x2c: /* Turn on the raster copy of the CRTC operation port (and leave it on), */
		case 0x2d: /* Apparently it's also permissible to change only the Src/Dst (like Dracula) */
			CRTC_RCFlag[adr & 1] = 1; /* Is it executed after changing Dst? */

			if ((CRTC_Mode & 8) && /*(CRTC_RCFlag[0])&&*/ (CRTC_RCFlag[1]))
			{
				CRTC_RasterCopy();
				CRTC_RCFlag[0] = 0;
				CRTC_RCFlag[1] = 0;
			}

			break;
		}
	}
	else if ((adr >= 0x480) && (adr <= 0x4ff))
	{
		if ((adr & 1) == 0)
		{
			return;
		}

		CRTC_Mode = (data | (CRTC_Mode & 2));

		/* Raster Copy */
		if (CRTC_Mode & 8)
		{
			CRTC_RasterCopy();
			CRTC_RCFlag[0] = 0;
			CRTC_RCFlag[1] = 0;
		}

		if (CRTC_Mode & 2) /* FastClear */
		{
			/* The mask at this point seems to be valid (Quoth) */
			CRTC_FastClrMask = FastClearMask[CRTC_Regs[0x2b] & 15];
		}
	}
}

int CRTC_StateContext(void *f, int writing) {
	state_context_f(CRTC_Regs, sizeof(CRTC_Regs));
	state_context_f(&CRTC_Mode, sizeof(CRTC_Mode));
	state_context_f(&TextDotX, sizeof(TextDotX));
	state_context_f(&TextDotY, sizeof(TextDotY));
	state_context_f(&CRTC_VSTART, sizeof(CRTC_VSTART));
	state_context_f(&CRTC_VEND, sizeof(CRTC_VEND));
	state_context_f(&CRTC_HSTART, sizeof(CRTC_HSTART));
	state_context_f(&CRTC_HEND, sizeof(CRTC_HEND));
	state_context_f(&TextScrollX, sizeof(TextScrollX));
	state_context_f(&TextScrollY, sizeof(TextScrollY));
	state_context_f(GrphScrollX, sizeof(GrphScrollX));
	state_context_f(GrphScrollY, sizeof(GrphScrollY));

	state_context_f(&CRTC_FastClr, sizeof(CRTC_FastClr));
	state_context_f(&CRTC_FastClrMask, sizeof(CRTC_FastClrMask));
	state_context_f(&CRTC_IntLine, sizeof(CRTC_IntLine));
	state_context_f(&CRTC_VStep, sizeof(CRTC_VStep));

	state_context_f(CRTC_RCFlag, sizeof(CRTC_RCFlag));

	state_context_f(&HSYNC_CLK, sizeof(HSYNC_CLK));

	return 1;
}
