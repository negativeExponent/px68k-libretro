/* PALETTE.C - Text/BG/Graphic Palette */

#include "../x11/common.h"
#include "../x11/windraw.h"

#include "palette.h"
#include "bg.h"
#include "crtc.h"
#include "tvram.h"
#include "x68kmemory.h"
#include "../x11/state.h"

uint8_t Pal_Regs[1024];
uint16_t TextPal[256];
uint16_t GrphPal[256];
uint16_t Pal16[65536];
uint16_t Ibit; /* Might be used for semi-transparent processing */

uint16_t Pal_HalfMask, Pal_Ix2;
static uint16_t Pal_R, Pal_G, Pal_B; /* For changing screen brightness */

/* ----- Create a conversion table from X68k to Win using the 16-bit mode color mask of DDraw -----
* X68k has a "GGGGGRRRRRBBBBBI" structure. Win often has a "RRRRRGGGGGGBBBBB" structure. However,
* it seems that there are cases where this is different, so let's do some calculations.
*/
static void Pal_SetColor(void)
{
	uint16_t TempMask, bit;
	uint16_t R[5] = { 0, 0, 0, 0, 0 };
	uint16_t G[5] = { 0, 0, 0, 0, 0 };
	uint16_t B[5] = { 0, 0, 0, 0, 0 };
	int r, g, b, i;

	r = g = b = 5;
	Pal_R = Pal_G = Pal_B = 0;
	TempMask              = 0; /* Check which bits are used (for I bits) */
	for (bit = 0x8000; bit; bit >>= 1)
	{
		/* Pick up 5 bits from the left (highest order) for each color */
		if ((WinDraw_Pal16R & bit) && (r))
		{
			R[--r] = bit;
			TempMask |= bit;
			Pal_R |= bit;
		}
		if ((WinDraw_Pal16G & bit) && (g))
		{
			G[--g] = bit;
			TempMask |= bit;
			Pal_G |= bit;
		}
		if ((WinDraw_Pal16B & bit) && (b))
		{
			B[--b] = bit;
			TempMask |= bit;
			Pal_B |= bit;
		}
	}

	Ibit = 1;
	for (bit = 1; bit; bit <<= 1)
	{
		/* Unused bits (usually for colors with 6 or more bits */
		if (!(TempMask & bit)) /* The least significant bit) is treated as the I bit */
		{
			/* I did not set Ibit=~TempMask; in case there are multiple 0 bits */
			Ibit = bit;
			break;
		}
	}

	/* Kitty kitty
	 * What if Pal_Ix2 = 0? Then it'll be 32-bit expansion... */
	/* �� It looks great on Riva128 (lol) but it might not be a problem... */

	Pal_HalfMask = ~(B[0] | R[0] | G[0] | Ibit);
	Pal_Ix2      = Ibit << 1;

	/*
		// If it seems strange, I'll put this in... 32bit expansion is a pain (sweat)
		if (Ibit==0x8000)			// If Ibit is the most significant bit, swap it with the least significant bit of blue
		{
			Ibit = B[0];
			B[0] = 0;			// The blue will be 4 bit but bear with me ^^;
			Pal_HalfMask = ~(B[1] | R[0] | G[0] | Ibit | 0x8000);
			Pal_Ix2 = Ibit << 1;
		}
	*/

	/* Creating a table based on the bit arrangement of the X68k */
	for (i = 0; i < 65536; i++)
	{
		bit = 0;
		if (i & 0x8000)
			bit |= G[4];
		if (i & 0x4000)
			bit |= G[3];
		if (i & 0x2000)
			bit |= G[2];
		if (i & 0x1000)
			bit |= G[1];
		if (i & 0x0800)
			bit |= G[0];
		if (i & 0x0400)
			bit |= R[4];
		if (i & 0x0200)
			bit |= R[3];
		if (i & 0x0100)
			bit |= R[2];
		if (i & 0x0080)
			bit |= R[1];
		if (i & 0x0040)
			bit |= R[0];
		if (i & 0x0020)
			bit |= B[4];
		if (i & 0x0010)
			bit |= B[3];
		if (i & 0x0008)
			bit |= B[2];
		if (i & 0x0004)
			bit |= B[1];
		if (i & 0x0002)
			bit |= B[0];
		if (i & 0x0001)
			bit |= Ibit;
		Pal16[i] = bit;
	}
}

void Pal_Init(void)
{
	memset(Pal_Regs, 0, 1024);
	memset(TextPal, 0, 512);
	memset(GrphPal, 0, 512);
	Pal_SetColor();
}

/* Changed the color of the palette */
void Pal_ChangeContrast(int num)
{
	int r, g, b, i;
	int palr, palg, palb;
	uint16_t bit;
	uint16_t R[5] = { 0, 0, 0, 0, 0 };
	uint16_t G[5] = { 0, 0, 0, 0, 0 };
	uint16_t B[5] = { 0, 0, 0, 0, 0 };
	uint16_t pal;

	r = g = b = 5;
	TVRAM_SetAllDirty();
	for (bit = 0x8000; bit; bit >>= 1)
	{
		/* Pick up 5 bits from the left (highest order) for each color */
		if ((WinDraw_Pal16R & bit) && (r))
			R[--r] = bit;
		if ((WinDraw_Pal16G & bit) && (g))
			G[--g] = bit;
		if ((WinDraw_Pal16B & bit) && (b))
			B[--b] = bit;
	}

	for (i = 0; i < 65536; i++)
	{
		palr = palg = palb = 0;
		if (i & 0x8000)
			palg |= G[4];
		if (i & 0x4000)
			palg |= G[3];
		if (i & 0x2000)
			palg |= G[2];
		if (i & 0x1000)
			palg |= G[1];
		if (i & 0x0800)
			palg |= G[0];
		if (i & 0x0400)
			palr |= R[4];
		if (i & 0x0200)
			palr |= R[3];
		if (i & 0x0100)
			palr |= R[2];
		if (i & 0x0080)
			palr |= R[1];
		if (i & 0x0040)
			palr |= R[0];
		if (i & 0x0020)
			palb |= B[4];
		if (i & 0x0010)
			palb |= B[3];
		if (i & 0x0008)
			palb |= B[2];
		if (i & 0x0004)
			palb |= B[1];
		if (i & 0x0002)
			palb |= B[0];

		pal  = palr | palb | palg;
		palg = (uint16_t)((palg * num) / 15) & Pal_G;
		palr = (uint16_t)((palr * num) / 15) & Pal_R;
		palb = (uint16_t)((palb * num) / 15) & Pal_B;

		Pal16[i] = palr | palb | palg;
		if ((pal) && (!Pal16[i]))
			Pal16[i] = B[0];
		if (i & 0x0001)
			Pal16[i] |= Ibit;
	}

	for (i = 0; i < 256; i++)
	{
		pal = Pal_Regs[i * 2];
		pal = (pal << 8) + Pal_Regs[i * 2 + 1];

		GrphPal[i] = Pal16[pal];

		pal = Pal_Regs[i * 2 + 512];
		pal = (pal << 8) + Pal_Regs[i * 2 + 513];

		TextPal[i] = Pal16[pal];
	}
}

int Pal_StateContext(void *f, int writing) {
	state_context_f(Pal_Regs, sizeof(Pal_Regs));
	state_context_f(TextPal, sizeof(Pal_Regs));
	state_context_f(GrphPal, sizeof(Pal_Regs));
	state_context_f(Pal16, sizeof(Pal_Regs));

	return 1;
}
