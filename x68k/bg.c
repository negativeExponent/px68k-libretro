/*
 *  BG.C - BG and sprites
 *  TODO: Check transparent color processing (especially with Text)
 */

#include "../x11/common.h"
#include "../x11/windraw.h"
#include "../x11/state.h"

#include "bg.h"
#include "crtc.h"
#include "palette.h"
#include "tvram.h"

static uint8_t Sprite[0x10000];
static uint16_t BG_CHREND  = 0;
static uint16_t BG_BG0TOP  = 0;
static uint16_t BG_BG0END  = 0;
static uint16_t BG_BG1TOP  = 0;
static uint16_t BG_BG1END  = 0;
static uint8_t  BG_CHRSIZE  = 16;
static uint32_t BG_AdrMask = 511;
static uint32_t BG0ScrollX = 0, BG0ScrollY = 0;
static uint32_t BG1ScrollX = 0, BG1ScrollY = 0;

static uint8_t  BGCHR8[8 * 8 * 256];
static uint8_t  BGCHR16[16 * 16 * 256];
static uint16_t BG_PriBuf[1600];

static uint8_t *Sprite_Regs;	/* 0xeb0000 - 0xeb0400 */
uint8_t *BG_Regs;				/* 0xeb0800 - 0xeb0812 */				
static uint8_t *BG;				/* 0xeb8000 - 0xebffff */

uint16_t BG_LineBuf[1600];

/* NOTE: changed from long to int32_t */
int32_t BG_HAdjust = 0;
int32_t BG_VLINE   = 0;

uint32_t VLINEBG = 0;

void BG_Init(void)
{
	/* EB0400 - EB07FF, EB0812 - EB7FFF - Reserved(FF) */
	memset(Sprite, 0, 0x10000);
	memset(&Sprite[0x400], 0xff, 0x400);
	memset(&Sprite[0x812], 0xff, 0x77ee);
	memset(BGCHR8, 0, 8 * 8 * 256);
	memset(BGCHR16, 0, 16 * 16 * 256);
	memset(BG_LineBuf, 0, 1600 * 2);
	BG_CHREND = 0x8000;

	Sprite_Regs = &Sprite[0];
	BG_Regs = &Sprite[0x800];
	BG = &Sprite[0x8000];
}

uint8_t FASTCALL BG_Read(uint32_t adr)
{
	adr &= 0xffff;

	if (adr < 0x400)
	{
		adr &= 0x3ff;
		adr ^= 1;
		return Sprite[adr];
	}

	return Sprite[adr];
}

#define UPDATE_TDL(t)                               \
	{                                               \
		int i;                                      \
		for (i = 0; i < 16; i++)                    \
		{                                           \
			TextDirtyLine[(t)] = 1;                 \
			(t) = ((t) + 1) & 0x3ff;                \
		}                                           \
	}

void FASTCALL BG_Write(uint32_t adr, uint8_t data)
{
	uint32_t bg16chr;
	int s1, s2, v = 0;

	s1 = (((BG_Regs[0x11] & 4) ? 2 : 1) - ((BG_Regs[0x11] & 16) ? 1 : 0));
	s2 = (((CRTC_Regs[0x29] & 4) ? 2 : 1) - ((CRTC_Regs[0x29] & 16) ? 1 : 0));

	if (!(BG_Regs[0x11] & 16))
	{
		v = ((BG_Regs[0x0f] >> s1) - (CRTC_Regs[0x0d] >> s2));
	}

	adr &= 0xffff;

	if (adr < 0x400) /* sprite mem */
	{	
		adr &= 0x3ff;
		adr ^= 1;

		if (Sprite[adr] != data)
		{
			uint16_t t0, t, *pw;

			v = BG_VLINE - 16 - v;
			/* get YPOS pointer (Sprite_Regs[] is little endian) */
			pw = (uint16_t *)(Sprite + (adr & 0x3f8) + 2);

			t = t0 = (*pw + v) & 0x3ff;
			UPDATE_TDL(t);

			Sprite[adr] = data;

			t = (*pw + v) & 0x3ff;
			if (t != t0)
			{
				UPDATE_TDL(t);
			}
		}
	}
	else if ((adr >= 0x800) && (adr < 0x812)) /* BG regs */
	{
		if (Sprite[adr] == data)
			return; /* return if no data is changed */

		Sprite[adr] = data;
		adr -= 0x800;
		switch (adr)
		{
		case 0x00:
		case 0x01:
			BG0ScrollX = (((uint32_t)BG_Regs[0x00] << 8) + BG_Regs[0x01]) & BG_AdrMask;
			TVRAM_SetAllDirty();
			break;
		case 0x02:
		case 0x03:
			BG0ScrollY = (((uint32_t)BG_Regs[0x02] << 8) + BG_Regs[0x03]) & BG_AdrMask;
			TVRAM_SetAllDirty();
			break;
		case 0x04:
		case 0x05:
			BG1ScrollX = (((uint32_t)BG_Regs[0x04] << 8) + BG_Regs[0x05]) & BG_AdrMask;
			TVRAM_SetAllDirty();
			break;
		case 0x06:
		case 0x07:
			BG1ScrollY = (((uint32_t)BG_Regs[0x06] << 8) + BG_Regs[0x07]) & BG_AdrMask;
			TVRAM_SetAllDirty();
			break;

		case 0x08: /* BG On/Off Changed */
			TVRAM_SetAllDirty();
			break;

		case 0x0d:
			BG_HAdjust = ((int32_t)BG_Regs[0x0d] - (CRTC_HSTART + 4)) * 8; /* Isn't it necessary to divide the horizontal resolution by 1/2? (Tetris) */
			TVRAM_SetAllDirty();
			break;
		case 0x0f:
			BG_VLINE = ((int32_t)BG_Regs[0x0f] - CRTC_VSTART) / ((BG_Regs[0x11] & 4) ? 1 : 2); /* Difference when BG and other elements are misaligned */
			TVRAM_SetAllDirty();
			break;

		case 0x11: /* BG ScreenRes Changed */
			if (data & 3)
			{
				if ((BG_BG0TOP == 0x4000) || (BG_BG1TOP == 0x4000))
					BG_CHREND = 0x4000;
				else if ((BG_BG0TOP == 0x6000) || (BG_BG1TOP == 0x6000))
					BG_CHREND = 0x6000;
				else
					BG_CHREND = 0x8000;
			}
			else
				BG_CHREND = 0x2000;
			BG_CHRSIZE = ((data & 3) ? 16 : 8);
			BG_AdrMask = ((data & 3) ? 1023 : 511);
			BG_HAdjust = ((int32_t)BG_Regs[0x0d] - (CRTC_HSTART + 4)) * 8; /*Isn't it necessary to divide the horizontal resolution by 1/2? (Tetris) */
			BG_VLINE = ((int32_t)BG_Regs[0x0f] - CRTC_VSTART) / ((BG_Regs[0x11] & 4) ? 1 : 2); /* Difference when BG and other elements are misaligned */
			break;
		case 0x09: /* BG Plane Cfg Changed */
			TVRAM_SetAllDirty();
			if (data & 0x08)
			{
				if (data & 0x30)
				{
					BG_BG1TOP = 0x6000;
					BG_BG1END = 0x8000;
				}
				else
				{
					BG_BG1TOP = 0x4000;
					BG_BG1END = 0x6000;
				}
			}
			else
				BG_BG1TOP = BG_BG1END = 0;
			if (data & 0x01)
			{
				if (data & 0x06)
				{
					BG_BG0TOP = 0x6000;
					BG_BG0END = 0x8000;
				}
				else
				{
					BG_BG0TOP = 0x4000;
					BG_BG0END = 0x6000;
				}
			}
			else
				BG_BG0TOP = BG_BG0END = 0;
			if (BG_Regs[0x11] & 3)
			{
				if ((BG_BG0TOP == 0x4000) || (BG_BG1TOP == 0x4000))
					BG_CHREND = 0x4000;
				else if ((BG_BG0TOP == 0x6000) || (BG_BG1TOP == 0x6000))
					BG_CHREND = 0x6000;
				else
					BG_CHREND = 0x8000;
			}
			break;
		case 0x0b:
			break;
		}
	}
	else if (adr >= 0x8000) /* BG*/
	{
		if (Sprite[adr] == data)
			return; /* return if no data is changed */

		Sprite[adr] = data;
		adr -= 0x8000;
		if (adr < 0x2000)
		{
			BGCHR8[adr * 2]     = data >> 4;
			BGCHR8[adr * 2 + 1] = data & 15;
		}
		bg16chr              = ((adr & 3) * 2) + ((adr & 0x3c) * 4) + ((adr & 0x40) >> 3) + ((adr & 0x7f80) * 2);
		BGCHR16[bg16chr]     = data >> 4;
		BGCHR16[bg16chr + 1] = data & 15;

		if ((adr < BG_CHREND) ||							/* pattern area */
			((adr >= BG_BG1TOP) && (adr < BG_BG1END)) ||	/* BG1 MAP Area */
			((adr >= BG_BG0TOP) && (adr < BG_BG0END)))		/* BG0 MAP Area */
		{
			TVRAM_SetAllDirty();
		}
	}
}

struct SPRITECTRLTBL {
	uint16_t sprite_posx;
	uint16_t sprite_posy;
	uint16_t sprite_ctrl;
	uint8_t sprite_ply;
	uint8_t dummy;
} __attribute__((packed));
typedef struct SPRITECTRLTBL SPRITECTRLTBL_T;

/* Drawing 1 line */
static INLINE void Sprite_DrawLineMcr(int pri)
{
	SPRITECTRLTBL_T *sct = (SPRITECTRLTBL_T *)Sprite_Regs;
	uint32_t y;
	uint32_t t;
	int n;

	for (n = 127; n >= 0; --n)
	{
		if ((sct[n].sprite_ply & 3) == pri)
		{
			SPRITECTRLTBL_T *sctp = &sct[n];

			t = (sctp->sprite_posx + BG_HAdjust) & 0x3ff;
			if (t >= TextDotX + 16)
				continue;

			y = sctp->sprite_posy & 0x3ff;
			y -= VLINEBG;
			y += BG_VLINE;
			y = -y;
			y += 16;

			/* add y, 16; jnc .spline_lpcnt */
			if (y <= 15)
			{
				uint8_t *p;
				uint32_t pal;
				int i, d;

				if (sctp->sprite_ctrl < 0x4000)
				{
					p = &BGCHR16[((sctp->sprite_ctrl * 256) & 0xffff) + (y * 16)];
					d = 1;
				}
				else if ((sctp->sprite_ctrl - 0x4000) & 0x8000)
				{
					p = &BGCHR16[((sctp->sprite_ctrl * 256) & 0xffff) + (((y * 16) & 0xff) ^ 0xf0) + 15];
					d = -1;
				}
				else if ((int16_t)(sctp->sprite_ctrl) >= 0x4000)
				{
					p = &BGCHR16[((sctp->sprite_ctrl * 256) & 0xffff) + (y * 16) + 15];
					d = -1;
				}
				else
				{
					p = &BGCHR16[((sctp->sprite_ctrl << 8) & 0xffff) + (((y * 16) & 0xff) ^ 0xf0)];
					d = 1;
				}

				for (i = 0; i < 16; i++, t++, p += d)
				{
					pal = *p & 0xf;
					if (pal)
					{
						pal |= (sctp->sprite_ctrl >> 4) & 0xf0;
						if (BG_PriBuf[t] >= n * 8)
						{
							BG_LineBuf[t] = TextPal[pal];
							Text_TrFlag[t] |= 2;
							BG_PriBuf[t] = n * 8;
						}
					}
				}
			}
		}
	}
}

#define BG_DRAWLINE_LOOPY(cnt)                              \
	{                                                       \
		bl = bl << 4;                                       \
		for (j = 0; j < cnt; j++, esi += d, edi++)          \
		{                                                   \
			dat = *esi | bl;                                \
			if (dat == 0)                                   \
				continue;                                   \
			if ((dat & 0xf) || !(Text_TrFlag[edi + 1] & 2)) \
			{                                               \
				BG_LineBuf[1 + edi] = TextPal[dat];         \
				Text_TrFlag[edi + 1] |= 2;                  \
			}                                               \
		}                                                   \
	}

#define BG_DRAWLINE_LOOPY_NG(cnt)                   \
	{                                               \
		bl = bl << 4;                               \
		for (j = 0; j < cnt; j++, esi += d, edi++)  \
		{                                           \
			dat = *esi & 0xf;                       \
			if (dat)                                \
			{                                       \
				dat |= bl;                          \
				BG_LineBuf[1 + edi] = TextPal[dat]; \
				Text_TrFlag[edi + 1] |= 2;          \
			}                                       \
		}                                           \
	}

static void bg_drawline_loopx8(uint16_t BGTOP, uint32_t BGScrollX, uint32_t BGScrollY, int32_t adjust, int ng)
{
	uint8_t dat, bl;
	int i, j, d;
	uint32_t ebp, edx, edi, ecx;
	uint16_t si;
	uint8_t *esi;

	ebp = ((BGScrollY + VLINEBG - BG_VLINE) & 7) << 3;
	edx = BGTOP + (((BGScrollY + VLINEBG - BG_VLINE) & 0x1f8) << 4);
	edi = ((BGScrollX - adjust) & 7) ^ 15;
	ecx = ((BGScrollX - adjust) & 0x1f8) >> 2;

	for (i = TextDotX >> 3; i >= 0; i--)
	{
		bl = BG[ecx + edx];
		si = (uint16_t)BG[ecx + edx + 1] << 6;

		if (bl < 0x40)
		{
			esi = &BGCHR8[si + ebp];
			d   = +1;
		}
		else if ((bl - 0x40) & 0x80)
		{
			esi = &BGCHR8[si + 0x3f - ebp];
			d   = -1;
		}
		else if ((int8_t)bl >= 0x40)
		{
			esi = &BGCHR8[si + ebp + 7];
			d   = -1;
		}
		else
		{
			esi = &BGCHR8[si + 0x38 - ebp];
			d   = +1;
		}
		if (ng)
		{
			BG_DRAWLINE_LOOPY_NG(8);
		}
		else
		{
			BG_DRAWLINE_LOOPY(8);
		}
		ecx += 2;
		ecx &= 0x7f;
	}
}

static void bg_drawline_loopx16(uint16_t BGTOP, uint32_t BGScrollX, uint32_t BGScrollY, int32_t adjust, int ng)
{
	uint8_t dat, bl;
	int i, j, d;
	uint32_t ebp, edx, edi, ecx;
	uint16_t si;
	uint8_t *esi;

	ebp = ((BGScrollY + VLINEBG - BG_VLINE) & 15) << 4;
	edx = BGTOP + (((BGScrollY + VLINEBG - BG_VLINE) & 0x3f0) << 3);
	edi = ((BGScrollX - adjust) & 15) ^ 15;
	ecx = ((BGScrollX - adjust) & 0x3f0) >> 3;

	for (i = TextDotX >> 4; i >= 0; i--)
	{
		bl = BG[ecx + edx];
		si = BG[ecx + edx + 1] << 8;

		if (bl < 0x40)
		{
			esi = &BGCHR16[si + ebp];
			d   = +1;
		}
		else if ((bl - 0x40) & 0x80)
		{
			esi = &BGCHR16[si + 0xff - ebp];
			d   = -1;
		}
		else if ((int8_t)bl >= 0x40)
		{
			esi = &BGCHR16[si + ebp + 15];
			d   = -1;
		}
		else
		{
			esi = &BGCHR16[si + 0xf0 - ebp];
			d   = +1;
		}
		if (ng)
		{
			BG_DRAWLINE_LOOPY_NG(16);
		}
		else
		{
			BG_DRAWLINE_LOOPY(16);
		}
		ecx += 2;
		ecx &= 0x7f;
	}
}

static INLINE void BG_DrawLineMcr8(uint16_t BGTOP, uint32_t BGScrollX, uint32_t BGScrollY)
{
	bg_drawline_loopx8(BGTOP, BGScrollX, BGScrollY, BG_HAdjust, 0);
}

static INLINE void BG_DrawLineMcr16(uint16_t BGTOP, uint32_t BGScrollX, uint32_t BGScrollY)
{
	bg_drawline_loopx16(BGTOP, BGScrollX, BGScrollY, BG_HAdjust, 0);
}

static INLINE void BG_DrawLineMcr8_ng(uint16_t BGTOP, uint32_t BGScrollX, uint32_t BGScrollY)
{
	bg_drawline_loopx8(BGTOP, BGScrollX, BGScrollY, BG_HAdjust, 1);
}

static INLINE void BG_DrawLineMcr16_ng(uint16_t BGTOP, uint32_t BGScrollX, uint32_t BGScrollY)
{
	bg_drawline_loopx16(BGTOP, BGScrollX, BGScrollY, 0, 1);
}

void FASTCALL BG_DrawLine(int opaq, int gd)
{
	unsigned i;
	void (*func8)(uint16_t, uint32_t, uint32_t), (*func16)(uint16_t, uint32_t, uint32_t);

	if (opaq)
	{
		for (i = 16; i < TextDotX + 16; ++i)
		{
			BG_LineBuf[i] = TextPal[0];
			BG_PriBuf[i]  = 0xffff;
		}
	}
	else
	{
		for (i = 16; i < TextDotX + 16; ++i)
		{
			BG_PriBuf[i] = 0xffff;
		}
	}

	func8  = (gd) ? BG_DrawLineMcr8 : BG_DrawLineMcr8_ng;
	func16 = (gd) ? BG_DrawLineMcr16 : BG_DrawLineMcr16_ng;

	Sprite_DrawLineMcr(1);
	if ((BG_Regs[0x09] & 8) && (BG_CHRSIZE == 8))
	{
		/* BG1 on */
		(*func8)(BG_BG1TOP, BG1ScrollX, BG1ScrollY);
	}
	Sprite_DrawLineMcr(2);
	if (BG_Regs[0x09] & 1)
	{
		/* BG0 on */
		if (BG_CHRSIZE == 8)
		{
			(*func8)(BG_BG0TOP, BG0ScrollX, BG0ScrollY);
		}
		else
		{
			(*func16)(BG_BG0TOP, BG0ScrollX, BG0ScrollY);
		}
	}
	Sprite_DrawLineMcr(3);
}

int BG_StateContext(void *f, int writing) {
	state_context_f(Sprite, sizeof(Sprite));

	state_context_f(&BG_CHREND, sizeof(BG_CHREND));
	state_context_f(&BG_BG0TOP, sizeof(BG_BG0TOP));
	state_context_f(&BG_BG0END, sizeof(BG_BG0END));
	state_context_f(&BG_BG1TOP, sizeof(BG_BG1TOP));
	state_context_f(&BG_BG1END, sizeof(BG_BG1END));
	state_context_f(&BG_CHRSIZE, sizeof(BG_CHRSIZE));
	state_context_f(&BG_AdrMask, sizeof(BG_AdrMask));
	state_context_f(&BG0ScrollX, sizeof(BG0ScrollX));
	state_context_f(&BG0ScrollY, sizeof(BG0ScrollY));
	state_context_f(&BG1ScrollX, sizeof(BG1ScrollX));
	state_context_f(&BG1ScrollY, sizeof(BG1ScrollY));

	state_context_f(BGCHR8, sizeof(BGCHR8));
	state_context_f(BGCHR16, sizeof(BGCHR16));
	state_context_f(BG_PriBuf, sizeof(BG_PriBuf));

	state_context_f(BG_LineBuf, sizeof(BG_LineBuf));

	state_context_f(&BG_HAdjust, sizeof(BG_HAdjust));
	state_context_f(&BG_VLINE, sizeof(BG_VLINE));
	state_context_f(&VLINEBG, sizeof(VLINEBG));

	return 1;
}
