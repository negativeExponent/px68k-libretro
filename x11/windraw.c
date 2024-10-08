/*
 * Copyright (c) 2003 NONAKA Kimihiro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>

#include "common.h"

#include "../x68k/bg.h"
#include "../x68k/crtc.h"
#include "../x68k/vc.h"
#include "../x68k/gvram.h"
#include "../x68k/palette.h"
#include "../x68k/tvram.h"
#include "../x68k/x68kmemory.h"

#include "winui.h"
#include "winx68k.h"
#include "mouse.h"
#include "prop.h"
#include "status.h"
#include "windraw.h"

extern uint8_t Debug_Text, Debug_Grp, Debug_Sp;
extern uint16_t *videoBuffer;
extern uint32_t retrow, retroh;
extern int CHANGEAV, VID_MODE;

static uint16_t *ScrBuf = 0;
static uint16_t menu_buffer[800 * 600];

uint16_t WinDraw_Pal16B, WinDraw_Pal16R, WinDraw_Pal16G;

void WinDraw_ChangeSize(void)
{
	/* function is called from crtc */
	/* StatBar_Show(Config.WindowFDDStat); */
}

int WinDraw_Init(void)
{
	WinDraw_Pal16R = 0xf800;
	WinDraw_Pal16G = 0x07e0;
	WinDraw_Pal16B = 0x001f;

	ScrBuf = (uint16_t *)malloc(800 * 600 * 2);

	if (!ScrBuf)
		return FALSE;

	return TRUE;
}

void WinDraw_Cleanup(void)
{
	if (ScrBuf)
		free(ScrBuf);
	ScrBuf = NULL;
}

void FASTCALL WinDraw_Draw(void)
{
	static int oldvidmode = 1;

	if (retrow != TextDotX || retroh != TextDotY)
	{
		if (TextDotX <= FULLSCREEN_WIDTH && TextDotY <= FULLSCREEN_HEIGHT)
		{
			retrow = TextDotX;
			retroh = TextDotY;
			CHANGEAV = 1;
		}
	}

	if (oldvidmode != VID_MODE)
	{
		oldvidmode = VID_MODE;
		CHANGEAV   = 2;
	}

	videoBuffer = (uint16_t *)ScrBuf;
}

#define WD_MEMCPY(src) memcpy(&ScrBuf[adr], (src), TextDotX * 2)

#define WD_LOOP(start, end, sub)                 \
	{                                            \
		for (i = (start); i < (end); i++, adr++) \
		{                                        \
			sub();                               \
		}                                        \
	}

#define WD_SUB(src)                  \
	{                                \
		w = (src);                   \
		if (w != 0)                  \
			ScrBuf[adr] = w;         \
	}

static INLINE void WinDraw_DrawGrpLine(int opaq)
{
#define _DGL_SUB() WD_SUB(Grp_LineBuf[i])

	uint32_t adr = VLINE * FULLSCREEN_WIDTH;
	uint16_t w;
	uint32_t i;

	if (opaq)
	{
		WD_MEMCPY(Grp_LineBuf);
	}
	else
	{
		WD_LOOP(0, TextDotX, _DGL_SUB);
	}
}

static INLINE void WinDraw_DrawGrpLineNonSP(int opaq)
{
#define _DGL_NSP_SUB() WD_SUB(Grp_LineBufSP2[i])

	uint32_t adr = VLINE * FULLSCREEN_WIDTH;
	uint16_t w;
	uint32_t i;

	if (opaq)
	{
		WD_MEMCPY(Grp_LineBufSP2);
	}
	else
	{
		WD_LOOP(0, TextDotX, _DGL_NSP_SUB);
	}
}

static INLINE void WinDraw_DrawTextLine(int opaq, int td)
{
#define _DTL_SUB2() WD_SUB(BG_LineBuf[i])
#define _DTL_SUB()              \
	{                           \
		if (Text_TrFlag[i] & 1) \
		{                       \
			_DTL_SUB2();        \
		}                       \
	}

	uint32_t adr = VLINE * FULLSCREEN_WIDTH;
	uint16_t w;
	uint32_t i;

	if (opaq)
	{
		WD_MEMCPY(&BG_LineBuf[16]);
	}
	else
	{
		if (td)
		{
			WD_LOOP(16, TextDotX + 16, _DTL_SUB);
		}
		else
		{
			WD_LOOP(16, TextDotX + 16, _DTL_SUB2);
		}
	}
}

static INLINE void WinDraw_DrawTextLineTR(int opaq)
{
#define _DTL_TR_SUB()                      \
	{                                      \
		w = Grp_LineBufSP[i - 16];         \
		if (w != 0)                        \
		{                                  \
			w &= Pal_HalfMask;             \
			v = BG_LineBuf[i];             \
			if (v & Ibit)                  \
				w += Pal_Ix2;              \
			v &= Pal_HalfMask;             \
			v += w;                        \
			v >>= 1;                       \
		}                                  \
		else                               \
		{                                  \
			if (Text_TrFlag[i] & 1)        \
				v = BG_LineBuf[i];         \
			else                           \
				v = 0;                     \
		}                                  \
		ScrBuf[adr] = (uint16_t)v;         \
	}

#define _DTL_TR_SUB2()                             \
	{                                              \
		if (Text_TrFlag[i] & 1)                    \
		{                                          \
			w = Grp_LineBufSP[i - 16];             \
			v = BG_LineBuf[i];                     \
                                                   \
			if (v != 0)                            \
			{                                      \
				if (w != 0)                        \
				{                                  \
					w &= Pal_HalfMask;             \
					if (v & Ibit)                  \
						w += Pal_Ix2;              \
					v &= Pal_HalfMask;             \
					v += w;                        \
					v >>= 1;                       \
				}                                  \
				ScrBuf[adr] = (uint16_t)v;         \
			}                                      \
		}                                          \
	}

	uint32_t adr = VLINE * FULLSCREEN_WIDTH;
	uint32_t v;
	uint16_t w;
	uint32_t i;

	if (opaq)
	{
		WD_LOOP(16, TextDotX + 16, _DTL_TR_SUB);
	}
	else
	{
		WD_LOOP(16, TextDotX + 16, _DTL_TR_SUB2);
	}
}

static INLINE void WinDraw_DrawBGLine(int opaq, int td)
{
#define _DBL_SUB2() WD_SUB(BG_LineBuf[i])
#define _DBL_SUB()              \
	{                           \
		if (Text_TrFlag[i] & 2) \
		{                       \
			_DBL_SUB2();        \
		}                       \
	}

	uint32_t adr = VLINE * FULLSCREEN_WIDTH;
	uint16_t w;
	uint32_t i;

	if (opaq)
	{
		WD_MEMCPY(&BG_LineBuf[16]);
	}
	else
	{
		if (td)
		{
			WD_LOOP(16, TextDotX + 16, _DBL_SUB);
		}
		else
		{
			WD_LOOP(16, TextDotX + 16, _DBL_SUB2);
		}
	}
}

static INLINE void WinDraw_DrawBGLineTR(int opaq)
{
#define _DBL_TR_SUB3()         \
	{                          \
		if (w != 0)            \
		{                      \
			w &= Pal_HalfMask; \
			if (v & Ibit)      \
				w += Pal_Ix2;  \
			v &= Pal_HalfMask; \
			v += w;            \
			v >>= 1;           \
		}                      \
	}

#define _DBL_TR_SUB()                      \
	{                                      \
		w = Grp_LineBufSP[i - 16];         \
		v = BG_LineBuf[i];                 \
                                           \
		_DBL_TR_SUB3()                     \
		ScrBuf[adr] = (uint16_t)v;         \
	}

#define _DBL_TR_SUB2()                             \
	{                                              \
		if (Text_TrFlag[i] & 2)                    \
		{                                          \
			w = Grp_LineBufSP[i - 16];             \
			v = BG_LineBuf[i];                     \
                                                   \
			if (v != 0)                            \
			{                                      \
				_DBL_TR_SUB3()                     \
				ScrBuf[adr] = (uint16_t)v;         \
			}                                      \
		}                                          \
	}

	uint32_t adr = VLINE * FULLSCREEN_WIDTH;
	uint32_t v;
	uint16_t w;
	uint32_t i;

	if (opaq)
	{
		WD_LOOP(16, TextDotX + 16, _DBL_TR_SUB);
	}
	else
	{
		WD_LOOP(16, TextDotX + 16, _DBL_TR_SUB2);
	}
}

static INLINE void WinDraw_DrawPriLine(void)
{
#define _DPL_SUB() WD_SUB(Grp_LineBufSP[i])

	uint32_t adr = VLINE * FULLSCREEN_WIDTH;
	uint16_t w;
	uint32_t i;

	WD_LOOP(0, TextDotX, _DPL_SUB);
}

void WinDraw_DrawLine(void)
{
	int opaq, ton = 0, gon = 0, bgon = 0, tron = 0, pron = 0, tdrawed = 0;

	if (VLINE == (uint32_t)-1)
		return;

	if (!TextDirtyLine[VLINE])
		return;

	TextDirtyLine[VLINE] = 0;

	if (Debug_Grp)
	{
		switch (VCReg0[1] & 3)
		{
		case 0:                /* 16 colors */
			if (VCReg0[1] & 4) /* 1024dot */
			{
				if (VCReg2[1] & 0x10)
				{
					if ((VCReg2[0] & 0x14) == 0x14)
					{
						Grp_DrawLine4hSP();
						pron = tron = 1;
					}
					else
					{
						Grp_DrawLine4h();
						gon = 1;
					}
				}
			}
			else /* 512dot */
			{
				if ((VCReg2[0] & 0x10) && (VCReg2[1] & 1))
				{
					Grp_DrawLine4SP((VCReg1[1]) & 3 /*, 1*/); /* Semi-transparent preparation */
					pron = tron = 1;
				}
				opaq = 1;
				if (VCReg2[1] & 8)
				{
					Grp_DrawLine4((VCReg1[1] >> 6) & 3, 1);
					opaq = 0;
					gon  = 1;
				}
				if (VCReg2[1] & 4)
				{
					Grp_DrawLine4((VCReg1[1] >> 4) & 3, opaq);
					opaq = 0;
					gon  = 1;
				}
				if (VCReg2[1] & 2)
				{
					if (((VCReg2[0] & 0x1e) == 0x1e) && (tron))
						Grp_DrawLine4TR((VCReg1[1] >> 2) & 3, opaq);
					else
						Grp_DrawLine4((VCReg1[1] >> 2) & 3, opaq);
					opaq = 0;
					gon  = 1;
				}

				if (VCReg2[1] & 1)
				{
#if 0
					// if ( (VCReg2[0]&0x1e)==0x1e )
					//{
					//	Grp_DrawLine4SP((VCReg1[1]   )&3, opaq);
					//	tron = pron = 1;
					//	}
					// else
#endif
					if ((VCReg2[0] & 0x14) != 0x14)
					{
						Grp_DrawLine4((VCReg1[1]) & 3, opaq);
						gon = 1;
					}
				}
			}
			break;
		case 1:
		case 2:
			opaq = 1;                                      /* 256 colors */
			if ((VCReg1[1] & 3) <= ((VCReg1[1] >> 4) & 3)) /* When the values ??are the same, GRP0 takes priority (Dragon Spirit) */
			{
				if ((VCReg2[0] & 0x10) && (VCReg2[1] & 1))
				{
					Grp_DrawLine8SP(0); /* Semi-transparent preparation */
					tron = pron = 1;
				}
				if (VCReg2[1] & 4)
				{
					if (((VCReg2[0] & 0x1e) == 0x1e) && (tron))
						Grp_DrawLine8TR(1, 1);
					else if (((VCReg2[0] & 0x1d) == 0x1d) && (tron))
						Grp_DrawLine8TR_GT(1, 1);
					else
						Grp_DrawLine8(1, 1);
					opaq = 0;
					gon  = 1;
				}
				if (VCReg2[1] & 1)
				{
					if ((VCReg2[0] & 0x14) != 0x14)
					{
						Grp_DrawLine8(0, opaq);
						gon = 1;
					}
				}
			}
			else
			{
				if ((VCReg2[0] & 0x10) && (VCReg2[1] & 1))
				{
					Grp_DrawLine8SP(1); /* Semi-transparent preparation */
					tron = pron = 1;
				}
				if (VCReg2[1] & 4)
				{
					if (((VCReg2[0] & 0x1e) == 0x1e) && (tron))
						Grp_DrawLine8TR(0, 1);
					else if (((VCReg2[0] & 0x1d) == 0x1d) && (tron))
						Grp_DrawLine8TR_GT(0, 1);
					else
						Grp_DrawLine8(0, 1);
					opaq = 0;
					gon  = 1;
				}
				if (VCReg2[1] & 1)
				{
					if ((VCReg2[0] & 0x14) != 0x14)
					{
						Grp_DrawLine8(1, opaq);
						gon = 1;
					}
				}
			}
			break;
		case 3: /* 65536 colors */
			if (VCReg2[1] & 15)
			{
				if ((VCReg2[0] & 0x14) == 0x14)
				{
					Grp_DrawLine16SP();
					tron = pron = 1;
				}
				else
				{
					Grp_DrawLine16();
					gon = 1;
				}
			}
			break;
		}
	}

#if 0
	// if ( ( ((VCReg1[0]&0x30)>>4) < (VCReg1[0]&0x03) ) && (gon) )
	// gdrawed = 1; // BG is above Grp
#endif

	if (((VCReg1[0] & 0x30) >> 2) < (VCReg1[0] & 0x0c))
	{
		/* BG is higher */
		if ((VCReg2[1] & 0x20) && (Debug_Text))
		{
			Text_DrawLine(1);
			ton = 1;
		}
		else
			memset(Text_TrFlag, 0, TextDotX + 16);

		if ((VCReg2[1] & 0x40) && (BG_Regs[0x08] & 2) && (!(BG_Regs[0x11] & 2)) && (Debug_Sp))
		{
			int s1 = (((BG_Regs[0x11] & 4) ? 2 : 1) - ((BG_Regs[0x11] & 16) ? 1 : 0));
			int s2 = (((CRTC_Regs[0x29] & 4) ? 2 : 1) - ((CRTC_Regs[0x29] & 16) ? 1 : 0));

			VLINEBG = VLINE;
			VLINEBG <<= s1;
			VLINEBG >>= s2;
			if (!(BG_Regs[0x11] & 16))
				VLINEBG -= ((BG_Regs[0x0f] >> s1) - (CRTC_Regs[0x0d] >> s2));
			BG_DrawLine(!ton, 0);
			bgon = 1;
		}
	}
	else
	{
		/* Text is on top */
		if ((VCReg2[1] & 0x40) && (BG_Regs[0x08] & 2) && (!(BG_Regs[0x11] & 2)) && (Debug_Sp))
		{
			int s1 = (((BG_Regs[0x11] & 4) ? 2 : 1) - ((BG_Regs[0x11] & 16) ? 1 : 0));
			int s2 = (((CRTC_Regs[0x29] & 4) ? 2 : 1) - ((CRTC_Regs[0x29] & 16) ? 1 : 0));

			VLINEBG = VLINE;
			VLINEBG <<= s1;
			VLINEBG >>= s2;
			if (!(BG_Regs[0x11] & 16))
				VLINEBG -= ((BG_Regs[0x0f] >> s1) - (CRTC_Regs[0x0d] >> s2));
			memset(Text_TrFlag, 0, TextDotX + 16);
			BG_DrawLine(1, 1);
			bgon = 1;
		}
		else
		{
			if ((VCReg2[1] & 0x20) && (Debug_Text))
			{
				uint32_t i;
				for (i = 16; i < TextDotX + 16; ++i)
					BG_LineBuf[i] = TextPal[0];
			}
			else
			{
				memset(&BG_LineBuf[16], 0, TextDotX * 2);
			}
			memset(Text_TrFlag, 0, TextDotX + 16);
			bgon = 1;
		}

		if ((VCReg2[1] & 0x20) && (Debug_Text))
		{
			Text_DrawLine(!bgon);
			ton = 1;
		}
	}

	opaq = 1;

#if 0
					// Show screen where Pri = 3 (violation) is set
		if ( ((VCReg1[0]&0x30)==0x30)&&(bgon) )
		{
			if ( ((VCReg2[0]&0x5d)==0x1d)&&((VCReg1[0]&0x03)!=0x03)&&(tron) )
			{
				if ( (VCReg1[0]&3)<((VCReg1[0]>>2)&3) )
				{
					WinDraw_DrawBGLineTR(opaq);
					tdrawed = 1;
					opaq = 0;
				}
			}
			else
			{
				WinDraw_DrawBGLine(opaq, /*tdrawed*/0);
				tdrawed = 1;
				opaq = 0;
			}
		}
		if ( ((VCReg1[0]&0x0c)==0x0c)&&(ton) )
		{
			if ( ((VCReg2[0]&0x5d)==0x1d)&&((VCReg1[0]&0x03)!=0x0c)&&(tron) )
				WinDraw_DrawTextLineTR(opaq);
			else
				WinDraw_DrawTextLine(opaq, /*tdrawed*/((VCReg1[0]&0x30)==0x30));
			opaq = 0;
			tdrawed = 1;
		}
#endif
	/* Display screens with Pri = 2 or 3 (lowest)
	 * If the priorities are the same, is GRP<SP<TEXT? (Dragon Spiral, Momoden, YsIII, etc.)

	 * If Text is above Grp and you make it semi-transparent with Text, will the SP priority also
	 * be dragged along by Text? (In other words, will SP be displayed even if it's below Grp?)

	 * When looking at KnightArms, it seems like the semi-transparent base plane is at the top...
	*/

	if ((VCReg1[0] & 0x02))
	{
		if (gon)
		{
			WinDraw_DrawGrpLine(opaq);
			opaq = 0;
		}
		if (tron)
		{
			WinDraw_DrawGrpLineNonSP(opaq);
			opaq = 0;
		}
	}
	if ((VCReg1[0] & 0x20) && (bgon))
	{
		if (((VCReg2[0] & 0x5d) == 0x1d) && ((VCReg1[0] & 0x03) != 0x02) && (tron))
		{
			if ((VCReg1[0] & 3) < ((VCReg1[0] >> 2) & 3))
			{
				WinDraw_DrawBGLineTR(opaq);
				tdrawed = 1;
				opaq    = 0;
			}
		}
		else
		{
			WinDraw_DrawBGLine(opaq, /*0*/ tdrawed);
			tdrawed = 1;
			opaq    = 0;
		}
	}
	if ((VCReg1[0] & 0x08) && (ton))
	{
		if (((VCReg2[0] & 0x5d) == 0x1d) && ((VCReg1[0] & 0x03) != 0x02) && (tron))
			WinDraw_DrawTextLineTR(opaq);
		else
			WinDraw_DrawTextLine(opaq, tdrawed /*((VCReg1[0]&0x30)>=0x20)*/);
		opaq    = 0;
		tdrawed = 1;
	}

	/* Display the screen with Pri = 1 (second) */
	if (((VCReg1[0] & 0x03) == 0x01) && (gon))
	{
		WinDraw_DrawGrpLine(opaq);
		opaq = 0;
	}
	if (((VCReg1[0] & 0x30) == 0x10) && (bgon))
	{
		if (((VCReg2[0] & 0x5d) == 0x1d) && (!(VCReg1[0] & 0x03)) && (tron))
		{
			if ((VCReg1[0] & 3) < ((VCReg1[0] >> 2) & 3))
			{
				WinDraw_DrawBGLineTR(opaq);
				tdrawed = 1;
				opaq    = 0;
			}
		}
		else
		{
			WinDraw_DrawBGLine(opaq, ((VCReg1[0] & 0xc) == 0x8));
			tdrawed = 1;
			opaq    = 0;
		}
	}
	if (((VCReg1[0] & 0x0c) == 0x04) && ((VCReg2[0] & 0x5d) == 0x1d) && (VCReg1[0] & 0x03) &&
	    (((VCReg1[0] >> 4) & 3) > (VCReg1[0] & 3)) && (bgon) && (tron))
	{
		WinDraw_DrawBGLineTR(opaq);
		tdrawed = 1;
		opaq    = 0;
		if (tron)
		{
			WinDraw_DrawGrpLineNonSP(opaq);
		}
	}
	else if (((VCReg1[0] & 0x03) == 0x01) && (tron) && (gon) && (VCReg2[0] & 0x10))
	{
		WinDraw_DrawGrpLineNonSP(opaq);
		opaq = 0;
	}
	if (((VCReg1[0] & 0x0c) == 0x04) && (ton))
	{
		if (((VCReg2[0] & 0x5d) == 0x1d) && (!(VCReg1[0] & 0x03)) && (tron))
			WinDraw_DrawTextLineTR(opaq);
		else
			WinDraw_DrawTextLine(opaq, ((VCReg1[0] & 0x30) >= 0x10));
		opaq    = 0;
		tdrawed = 1;
	}

	/* Display the screen with Pri = 0 (highest priority) */
	if ((!(VCReg1[0] & 0x03)) && (gon))
	{
		WinDraw_DrawGrpLine(opaq);
		opaq = 0;
	}
	if ((!(VCReg1[0] & 0x30)) && (bgon))
	{
		WinDraw_DrawBGLine(opaq, /*tdrawed*/ ((VCReg1[0] & 0xc) >= 0x4));
		tdrawed = 1;
		opaq    = 0;
	}
	if ((!(VCReg1[0] & 0x0c)) && ((VCReg2[0] & 0x5d) == 0x1d) && (((VCReg1[0] >> 4) & 3) > (VCReg1[0] & 3)) && (bgon) &&
	    (tron))
	{
		WinDraw_DrawBGLineTR(opaq);
		tdrawed = 1;
		opaq    = 0;
		if (tron)
		{
			WinDraw_DrawGrpLineNonSP(opaq);
		}
	}
	else if ((!(VCReg1[0] & 0x03)) && (tron) && (VCReg2[0] & 0x10))
	{
		WinDraw_DrawGrpLineNonSP(opaq);
		opaq = 0;
	}
	if ((!(VCReg1[0] & 0x0c)) && (ton))
	{
		WinDraw_DrawTextLine(opaq, 1);
		tdrawed = 1;
		opaq    = 0;
	}

	/* Graphics at special priority */
	if (((VCReg2[0] & 0x5c) == 0x14) && (pron)) /* When using special Pri, the target plane bit seems to have no meaning (twin bit) */
	{
		WinDraw_DrawPriLine();
	}
	else if (((VCReg2[0] & 0x5d) == 0x1c) && (tron)) /* When semi-transparent, fill all transparent dots with half color */
	{                                                /* AQUALES */

#define _DL_SUB()                                          \
	{                                                      \
		w = Grp_LineBufSP[i];                              \
		if (w != 0 && (ScrBuf[adr] & 0xffff) == 0)         \
			ScrBuf[adr] = (w & Pal_HalfMask) >> 1;         \
	}

		uint32_t adr = VLINE * FULLSCREEN_WIDTH;
		uint16_t w;
		uint32_t i;

		WD_LOOP(0, TextDotX, _DL_SUB);
	}

	if (opaq)
	{
		uint32_t adr = VLINE * FULLSCREEN_WIDTH;
		memset(&ScrBuf[adr], 0, TextDotX * 2);
	}
}

/* menu-related routines */

struct _px68k_menu
{
	uint16_t *sbp;    /* surface buffer ptr */
	uint16_t *mlp;    /* menu locate ptr */
	uint16_t mcolor;  /* color of chars to write */
	uint16_t mbcolor; /* back ground color of chars to write */
	int ml_x;
	int ml_y;
	int mfs; /* menu font size; */
} p6m;

/* sjis to jis code conversion */
static uint16_t sjis2jis(uint16_t w)
{
	uint8_t wh, wl;

	wh = w / 256, wl = w % 256;

	wh <<= 1;
	if (wl < 0x9f)
	{
		wh += (wh < 0x3f) ? 0x1f : -0x61;
		wl -= (wl > 0x7e) ? 0x20 : 0x1f;
	}
	else
	{
		wh += (wh < 0x3f) ? 0x20 : -0x60;
		wl -= 0x7e;
	}

	return (wh * 256 + wl);
}

/* Convert from JIS code to index of 0 origin */
/* However, 0x2921-0x2f7e is not in the X68K ROM, so it is skipped */
static uint16_t jis2idx(uint16_t jc)
{
	if (jc >= 0x3000)
	{
		jc -= 0x3021;
	}
	else
	{
		jc -= 0x2121;
	}
	jc = jc % 256 + (jc / 256) * 0x5e;

	return jc;
}

#define isHankaku(s) (((s) >= 0x20 && (s) <= 0x7e) || ((s) >= 0xa0 && (s) <= 0xdf))
#define MENU_WIDTH   800

/* fs : font size : 16 or 24
* For half-width characters, put the data in the top 8 bits of the 16 bits
* (so that it can be determined whether it is half-width or full-width)
*/
static int32_t get_font_addr(uint16_t sjis, int fs)
{
	uint16_t jis, j_idx;
	uint8_t jhi;
	int fsb; /* file size in bytes */

	/* Half-width character */
	if (isHankaku(sjis >> 8))
	{
		switch (fs)
		{
		case 8:
			return (0x3a000 + (sjis >> 8) * (1 * 8));
		case 16:
			return (0x3a800 + (sjis >> 8) * (1 * 16));
		case 24:
			return (0x3d000 + (sjis >> 8) * (2 * 24));
		default:
			return -1;
		}
	}

	/* Double-byte character */
	if (fs == 16)
	{
		fsb = 2 * 16;
	}
	else if (fs == 24)
	{
		fsb = 3 * 24;
	}
	else
	{
		return -1;
	}

	jis   = sjis2jis(sjis);
	j_idx = (uint32_t)jis2idx(jis);
	jhi   = (uint8_t)(jis >> 8);

	if (jhi >= 0x21 && jhi <= 0x28)
	{
		/* Non-Chinese characters */
		return ((fs == 16) ? 0x0 : 0x40000) + j_idx * fsb;
	}
	else if (jhi >= 0x30 && jhi <= 0x74)
	{
		/* First level/Second level */
		return ((fs == 16) ? 0x5e00 : 0x4d380) + j_idx * fsb;
	}
	else
	{
		return -1;
	}
}

/* RGB565 */
static void set_mcolor(uint16_t c)
{
	p6m.mcolor = c;
}

/* If mbcolor = 0, the color is transparent */
static void set_mbcolor(uint16_t c)
{
	p6m.mbcolor = c;
}

#if 0 /* unused for now, so just silence this */
/* Graphic coordinates */
static void set_mlocate(int x, int y)
{
	p6m.ml_x = x, p6m.ml_y = y;
}
#endif

/* Character coordinates (one coordinate on the horizontal axis is half-width
 * character width) */
static void set_mlocateC(int x, int y)
{
	p6m.ml_x = x * p6m.mfs / 2, p6m.ml_y = y * p6m.mfs;
}

static void set_sbp(uint16_t *p) {
	p6m.sbp = p;
}

/* menu font size (16 or 24) */
static void set_mfs(int fs) {
	p6m.mfs = fs;
}

static uint16_t *get_ml_ptr(void)
{
	p6m.mlp = p6m.sbp + MENU_WIDTH * p6m.ml_y + p6m.ml_x;
	return p6m.mlp;
}

/* For half-width characters, put the data in the top 8 bits of the 16 bits
* (so that it can be determined whether it is half-width or full-width)
* The cursor moves forward by the displayed amount
*/
static void draw_char(uint16_t sjis)
{
	int32_t f;
	uint16_t *p;
	int i, j, k, wc, w;
	uint8_t c;
	uint16_t bc;

	int h = p6m.mfs;

	p = get_ml_ptr();

	f = get_font_addr(sjis, h);

	if (f < 0)
		return;

	/* h=8 is only half-width */
	w = (h == 8) ? 8 : (isHankaku(sjis >> 8) ? h / 2 : h);

	for (i = 0; i < h; i++)
	{
		wc = w;
		for (j = 0; j < ((w % 8 == 0) ? w / 8 : w / 8 + 1); j++)
		{
			c = FONT[f ^ 1]; /* read from CGROM address */
			f++;
			for (k = 0; k < 8; k++)
			{
				bc = p6m.mbcolor ? p6m.mbcolor : *p;
				*p = (c & 0x80) ? p6m.mcolor : bc;
				p++;
				c = c << 1;
				wc--;
				if (wc == 0)
					break;
			}
		}
		p = p + MENU_WIDTH - w;
	}

	p6m.ml_x += w;
}

static void draw_str(char *cp)
{
	int i, len;
	uint8_t *s;
	uint16_t wc;

	len = strlen(cp);
	s   = (uint8_t *)cp;

	for (i = 0; i < len; i++)
	{
		if (isHankaku(*s))
		{
			/* The first 8 bits are used to determine half-full-width, so if it
			 * is half-width, shift left 8 bits in advance
			 */
			draw_char((uint16_t)*s << 8);
			s++;
		}
		else
		{
			wc = (uint16_t)(*s << 8) + *(s + 1);
			draw_char(wc);
			s += 2;
			i++;
		}
		/* 8x8 drawing (the FUNC key on the soft keyboard reduces the character
		 * width) */
		if (p6m.mfs == 8)
		{
			p6m.ml_x -= 3;
		}
	}
}

int WinDraw_MenuInit(void)
{
	set_sbp(menu_buffer);
	set_mfs(16);

	set_mcolor(0xffff);
	set_mbcolor(0);

	return TRUE;
}

#include "menu_str_sjis.txt"
char menu_item_desc[][60] = {
	"Reset / NMI reset / Quit",
	"Change / Eject floppy 0",
	"Change / Eject floppy 1",
	"Change / Eject HDD 0",
	"Change / Eject HDD 1"
};

void WinDraw_DrawMenu(MenuState menu_state, int mkey_pos, int mkey_y, int *mval_y)
{
	int i, drv;
	char tmp[256];

	/* Set_sbp(kbd_buffer) is used when drawing the software keyboard, so it is restored. */

	set_sbp(menu_buffer);
	set_mfs(Config.menuSize ? 24 : 16);

	set_mcolor(0x07ff); /* cyan */
	set_mlocateC(0, 0);
	draw_str(twaku_str);
	set_mlocateC(0, 1);
	draw_str(twaku2_str);
	set_mlocateC(0, 2);
	draw_str(twaku3_str);

	set_mcolor(0xffff);
	set_mlocateC(2, 1);
	sprintf(tmp, "%s%s", title_str, PX68K_VERSION);
	draw_str(tmp);

	/* middle */
	set_mcolor(0xffff);
#if 0
	// set_mlocate(3 * p6m.mfs / 2, 3.5 * p6m.mfs);
	// draw_str(waku_val_str[0]);
	// set_mlocate(17 * p6m.mfs / 2, 3.5 * p6m.mfs);
	// draw_str(waku_val_str[1]);
#endif

	/* Center frame */
	set_mcolor(0xffe0); /* yellow */
	set_mlocateC(1, 4);
	draw_str(waku_str);
	for (i = 5; i < 10; i++)
	{
		set_mlocateC(1, i);
		draw_str(waku2_str);
	}
	set_mlocateC(1, 10);
	draw_str(waku3_str);

	/* item/keyword */
	set_mcolor(0xffff);
	for (i = 0; i < 5; i++)
	{
		set_mlocateC(3, 5 + i);
		if (menu_state == ms_key && i == (mkey_y - mkey_pos))
		{
			set_mcolor(0x0);
			set_mbcolor(0xffe0); /* yellow); */
		}
		else
		{
			set_mcolor(0xffff);
			set_mbcolor(0x0);
		}
		draw_str(menu_item_key[i + mkey_pos]);
	}

	/* item/current value */
	set_mcolor(0xffff);
	set_mbcolor(0x0);
	for (i = 0; i < 5; i++)
	{
		if ((menu_state == ms_value || menu_state == ms_hwjoy_set) && i == (mkey_y - mkey_pos))
		{
			set_mcolor(0x0);
			set_mbcolor(0xffe0); /* yellow); */
		}
		else
		{
			set_mcolor(0xffff);
			set_mbcolor(0x0);
		}

		set_mlocateC(17, 5 + i);
		drv = WinUI_get_drv_num(i + mkey_pos);
		if (drv >= 0 && mval_y[i + mkey_pos] == 0)
		{
			char *p;
			if (drv < 2)
			{
				p = Config.FDDImage[drv];
			}
			else
			{
				p = Config.HDImage[drv - 2];
			}

			if (p[0] == '\0')
			{
				draw_str(" -- no disk --");
			}
			else
			{
				/* Do not display the first current directory name */
				char ptr[PATH_MAX];
				if (!strncmp(cur_dir_str, p, cur_dir_slen))
					strncpy(ptr, p + cur_dir_slen, sizeof(ptr));
				else
					strncpy(ptr, p, sizeof(ptr));
				ptr[40] = '\0';
				draw_str(ptr);
			}
		}
		else
		{
			draw_str(menu_items[i + mkey_pos][mval_y[i + mkey_pos]]);
		}
	}

	/* Bottom border */
	set_mcolor(0x07ff); /* cyan */
	set_mbcolor(0x0);
	set_mlocateC(0, 11);
	draw_str(swaku_str);
	set_mlocateC(0, 12);
	draw_str(swaku2_str);
#if 0
	// set_mlocateC(0, 15);
	// draw_str(swaku2_str);
#endif
	set_mlocateC(0, 13);
	draw_str(swaku3_str);

	/* Caption */
	set_mcolor(0xffff);
	set_mbcolor(0x0);
	set_mlocateC(2, 12);
	draw_str(menu_item_desc[mkey_y]);
#if 0
	// if (menu_state == ms_value) {
	// set_mlocateC(2, 15);
	// draw_str(item_cap2[mkey_y]);
	//}
#endif

	videoBuffer = (uint16_t *)menu_buffer;
}

void WinDraw_DrawMenufile(struct menu_flist *mfl)
{
	int i;
	char ptr[PATH_MAX];

	/* 0xf800 - red */
	/* 0xf81f - magenta */

	/* bottom frame */
	set_mcolor(0xffff);
	set_mbcolor(0x1); /* 0 means transparent */
	set_mlocateC(1, 1);
	draw_str(swaku_str);
	for (i = 2; i < 16; i++)
	{
		set_mlocateC(1, i);
		draw_str(swaku2_str);
	}
	set_mlocateC(1, 16);
	draw_str(swaku3_str);

	for (i = 0; i < 14; i++)
	{
		if (i + 1 > mfl->num)
		{
			break;
		}
		if (i == mfl->y)
		{
			set_mcolor(0x0);
			set_mbcolor(0xffff);
		}
		else
		{
			set_mcolor(0xffff);
			set_mbcolor(0x1);
		}
		/* enclose directory in '[ ]' */
		set_mlocateC(3, i + 2);
		if (mfl->type[i + mfl->ptr])
			draw_str("[");
		strncpy(ptr, mfl->name[i + mfl->ptr], sizeof(ptr));
		ptr[56] = '\0';
		draw_str(ptr);
		if (mfl->type[i + mfl->ptr])
			draw_str("]");
	}

	set_mbcolor(0x0); /* switch back to transparent mode */

	videoBuffer = (uint16_t *)menu_buffer;
}

void WinDraw_ClearMenuBuffer(void) {
	memset(menu_buffer, 0, 800 * 600 * 2);
}
