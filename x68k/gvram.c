/* GVRAM.C - Graphic VRAM */

#include "../x11/winx68k.h"

#include "gvram.h"
#include "crtc.h"
#include "palette.h"
#include "tvram.h"

uint8_t GVRAM[0x80000];
uint16_t Grp_LineBuf[1024];
uint16_t Grp_LineBufSP[1024];  /* �ü�ץ饤����ƥ���ȾƩ���ѥХåե� */
uint16_t Grp_LineBufSP2[1024]; /* ȾƩ���١����ץ졼���ѥХåե�����ȾƩ���ӥåȳ�Ǽ��*/
uint16_t Grp_LineBufSP_Tr[1024];
uint16_t Pal16Adr[256];        /* 16bit color �ѥ�åȥ��ɥ쥹�׻��� */

void GVRAM_Init(void)
{
	int i;

	memset(GVRAM, 0, 0x80000);
	for (i = 0; i < 128; i++) /* 16bit color �ѥ�åȥ��ɥ쥹�׻��� */
	{
		Pal16Adr[i * 2]     = i * 4;
		Pal16Adr[i * 2 + 1] = i * 4 + 1;
	}
}

void FASTCALL GVRAM_FastClear(void)
{
	uint16_t *p;
	uint32_t x, y;
	uint32_t v    = ((CRTC_Regs[0x29] & 4) ? 512 : 256);
	uint32_t h    = ((CRTC_Regs[0x29] & 3) ? 512 : 256);
	uint32_t offy = (GrphScrollY[0] & 0x1ff) << 10;

	/* ��äѤ������ϰϻ��ꤷ�ʤ����Ѥˤʤ��Τ⤢��ʥ����ʥޥ��ȥǥ塼���Ȥ��� */
	for (y = 0; y < v; ++y)
	{
		uint32_t offx = GrphScrollX[0] & 0x1ff;
		for (x = 0; x < h; ++x)
		{
			p = (uint16_t *)&GVRAM[offy + (offx * 2)];
			*p &= CRTC_FastClrMask;
			offx = (offx + 1) & 0x1ff;
		}
		offy = (offy + 0x400) & 0x7fc00;
	}
}

uint8_t FASTCALL GVRAM_Read(uint32_t adr)
{
	uint8_t page;
	uint16_t *ram = (uint16_t *)(&GVRAM[adr & 0x7fffe]);

	adr ^= 1;
	adr -= 0xc00000;

	if (CRTC_Regs[0x28] & 8)
	{
		/* �ɤ߹���¦��65536�⡼�ɤ�VRAM���֡ʶ��Ƭ��ʪĢ�� */
		if (adr < 0x80000)
			return GVRAM[adr];
	}
	else
	{
		switch (CRTC_Regs[0x28] & 3)
		{
		case 0: /* 16 colors */
			if (!(adr & 1))
			{
				if (CRTC_Regs[0x28] & 4) /* 1024dot */
				{
					ram  = (uint16_t *)(&GVRAM[((adr & 0xff800) >> 1) + (adr & 0x3fe)]);
					page = (uint8_t)((adr >> 17) & 0x08);
					page += (uint8_t)((adr >> 8) & 4);
					return (((*ram) >> page) & 15);
				}
				else
				{
					page = (uint8_t)((adr >> 17) & 0x0c);
					return (((*ram) >> page) & 15);
				}
			}
			break;
		case 1: /* 256 */
		case 2: /* Unknown */
			if (adr < 0x100000)
			{
				if (!(adr & 1))
				{
					page = (uint8_t)((adr >> 16) & 0x08);
					return (uint8_t)((*ram) >> page);
				}
			}
#if 0
			else
				BusErrFlag = 1;
#endif
			break;
		case 3: /* 65536 */
			if (adr < 0x80000)
				return GVRAM[adr];
#if 0
			else
				BusErrFlag = 1;
#endif
			break;
		}
	}
	return 0;
}

void FASTCALL GVRAM_Write(uint32_t adr, uint8_t data)
{
	uint8_t page;
	int line = 1023, scr = 0;
	uint16_t *ram = (uint16_t *)(&GVRAM[adr & 0x7fffe]);
	uint16_t temp;

	adr ^= 1;
	adr -= 0xc00000;

	if (CRTC_Regs[0x28] & 8) /* 65536�⡼�ɤ�VRAM���֡���Nemesis�� */
	{
		if (adr < 0x80000)
		{
			GVRAM[adr] = data;
			line       = (((adr & 0x7ffff) / 1024) - GrphScrollY[0]) & 511;
		}
	}
	else
	{
		switch (CRTC_Regs[0x28] & 3)
		{
		case 0: /* 16 colors */
			if (adr & 1)
				break;
			if (CRTC_Regs[0x28] & 4) /* 1024dot */
			{
				ram  = (uint16_t *)(&GVRAM[((adr & 0xff800) >> 1) + (adr & 0x3fe)]);
				page = (uint8_t)((adr >> 17) & 0x08);
				page += (uint8_t)((adr >> 8) & 4);
				temp = ((uint16_t)data & 15) << page;
				*ram = ((*ram) & (~(0xf << page))) | temp;
				line = ((adr / 2048) - GrphScrollY[0]) & 1023;
			}
			else
			{
				page = (uint8_t)((adr >> 17) & 0x0c);
				temp = ((uint16_t)data & 15) << page;
				*ram = ((*ram) & (~(0xf << page))) | temp;
				switch (adr / 0x80000)
				{
				case 0:
					scr = GrphScrollY[0];
					break;
				case 1:
					scr = GrphScrollY[1];
					break;
				case 2:
					scr = GrphScrollY[2];
					break;
				case 3:
					scr = GrphScrollY[3];
					break;
				}
				line = (((adr & 0x7ffff) / 1024) - scr) & 511;
			}
			break;
		case 1: /* 256 colors */
		case 2: /* Unknown */
			if (adr < 0x100000)
			{
				if (!(adr & 1))
				{
					scr  = GrphScrollY[(adr >> 18) & 2];
					line = (((adr & 0x7ffff) >> 10) - scr) & 511;

					TextDirtyLine[line] = 1; /* 32��4�̤ߤ����ʻ�����ˡ�� */

					scr  = GrphScrollY[((adr >> 18) & 2) + 1];
					line = (((adr & 0x7ffff) >> 10) - scr) & 511;

					if (adr & 0x80000)
						adr += 1;
					adr &= 0x7ffff;
					GVRAM[adr] = data;
				}
			}
#if 0
			else
			{
				BusErrFlag = 1;
				return;
			}
#endif
			break;
		case 3: /* 65536 colors */
			if (adr < 0x80000)
			{
				GVRAM[adr] = data;
				line       = (((adr & 0x7ffff) >> 10) - GrphScrollY[0]) & 511;
			}
#if 0
			else
			{
				BusErrFlag = 1;
				return;
			}
#endif
			break;
		}
		TextDirtyLine[line] = 1;
	}
}

void Grp_DrawLine16(void)
{
	uint16_t *srcp, *destp;
	uint32_t x, y;
	uint32_t i;
	uint16_t v, v0;

	y = GrphScrollY[0] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
		y += VLINE;
	y = (y & 0x1ff) << 10;

	x     = GrphScrollX[0] & 0x1ff;
	srcp  = (uint16_t *)(GVRAM + y + x * 2);
	destp = (uint16_t *)Grp_LineBuf;

	x = (x ^ 0x1ff) + 1;

	v = v0 = 0;
	i      = 0;
	if (x < TextDotX)
	{
		for (; i < x; ++i)
		{
			v = *srcp++;
			if (v != 0)
			{
				v0 = (v >> 8) & 0xff;
				v &= 0x00ff;

				v = Pal_Regs[Pal16Adr[v]];
				v |= Pal_Regs[Pal16Adr[v0] + 2] << 8;
				v = Pal16[v];
			}
			*destp++ = v;
		}
		srcp -= 0x200;
	}

	for (; i < TextDotX; ++i)
	{
		v = *srcp++;
		if (v != 0)
		{
			v0 = (v >> 8) & 0xff;
			v &= 0x00ff;

			v = Pal_Regs[Pal16Adr[v]];
			v |= Pal_Regs[Pal16Adr[v0] + 2] << 8;
			v = Pal16[v];
		}
		*destp++ = v;
	}
}

#define GET_WORD_W8(adr) (uint16_t)GVRAM[(adr + 1) & 0x7FFFF] << 8 | (uint16_t)GVRAM[adr & 0x7FFFF]

void FASTCALL Grp_DrawLine8(int page, int opaq)
{
	uint16_t *destp;
	uint32_t x, x0;
	uint32_t y, y0;
	uint32_t off;
	uint32_t i;
	uint16_t v;
	uint32_t adr;

	page &= 1;

	y  = GrphScrollY[page * 2] + VLINE;
	y0 = GrphScrollY[page * 2 + 1] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
	{
		y += VLINE;
		y0 += VLINE;
	}
	y  = ((y & 0x1ff) << 10) + page;
	y0 = ((y0 & 0x1ff) << 10) + page;

	x  = GrphScrollX[page * 2] & 0x1ff;
	x0 = GrphScrollX[page * 2 + 1] & 0x1ff;

	off   = y0 + x0 * 2;
	adr  = y + x * 2;
	destp = (uint16_t *)Grp_LineBuf;

	x = (x ^ 0x1ff) + 1;

	v = 0;
	i = 0;

	if (opaq)
	{
		if (x < TextDotX)
		{
			for (; i < x; ++i)
			{
				v = GET_WORD_W8(adr);
				adr += 2;
				v = GrphPal[(GVRAM[off] & 0xf0) | (v & 0x0f)];
				*destp++ = v;

				off += 2;
				if ((off & 0x3fe) == 0x000)
					off -= 0x400;
			}
			adr -= 0x400;
		}

		for (; i < TextDotX; ++i)
		{
			v = GET_WORD_W8(adr);
			adr += 2;
			v = GrphPal[(GVRAM[off] & 0xf0) | (v & 0x0f)];
			*destp++ = v;

			off += 2;
			if ((off & 0x3fe) == 0x000)
				off -= 0x400;
		}
	}
	else
	{
		if (x < TextDotX)
		{
			for (; i < x; ++i)
			{
				v = GET_WORD_W8(adr);
				adr += 2;
				v = (GVRAM[off] & 0xf0) | (v & 0x0f);
				if (v != 0x00)
					*destp = GrphPal[v];
				destp++;

				off += 2;
				if ((off & 0x3fe) == 0x000)
					off -= 0x400;
			}
			adr -= 0x400;
		}

		for (; i < TextDotX; ++i)
		{
			v = GET_WORD_W8(adr);
			adr += 2;
			v = (GVRAM[off] & 0xf0) | (v & 0x0f);
			if (v != 0x00)
				*destp = GrphPal[v];
			destp++;

			off += 2;
			if ((off & 0x3fe) == 0x000)
				off -= 0x400;
		}
	}
}

/* Manhattan Requiem Opening 7.0��7.5MHz */
void FASTCALL Grp_DrawLine4(uint32_t page, int opaq)
{
	uint16_t *destp; /* XXX: ALIGN */
	uint32_t x, y;
	uint32_t off;
	uint32_t i;
	uint16_t v;
	uint32_t adr;

	page &= 3;

	y = GrphScrollY[page] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
		y += VLINE;
	y = (y & 0x1ff) << 10;

	x   = GrphScrollX[page] & 0x1ff;
	off = y + x * 2;

	x ^= 0x1ff;

	adr  = off + (page >> 1);
	destp = (uint16_t *)Grp_LineBuf;

	v = 0;
	i = 0;

	if (page & 1)
	{
		if (opaq)
		{
			if (x < TextDotX)
			{
				for (; i < x; ++i)
				{
					v = GET_WORD_W8(adr);
					adr += 2;
					v = GrphPal[(v >> 4) & 0xf];
					*destp++ = v;
				}
				adr -= 0x400;
			}
			for (; i < TextDotX; ++i)
			{
				v = GET_WORD_W8(adr);
				adr += 2;
				v = GrphPal[(v >> 4) & 0xf];
				*destp++ = v;
			}
		}
		else
		{
			if (x < TextDotX)
			{
				for (; i < x; ++i)
				{
					v = GET_WORD_W8(adr);
					adr += 2;
					v = (v >> 4) & 0x0f;
					if (v != 0x00)
						*destp = GrphPal[v];
					destp++;
				}
				adr -= 0x400;
			}
			for (; i < TextDotX; ++i)
			{
				v = GET_WORD_W8(adr);
				adr += 2;
				v = (v >> 4) & 0x0f;
				if (v != 0x00)
					*destp = GrphPal[v];
				destp++;
			}
		}
	}
	else
	{
		if (opaq)
		{
			if (x < TextDotX)
			{
				for (; i < x; ++i)
				{
					v = GET_WORD_W8(adr);
					adr += 2;
					v = GrphPal[v & 0x0f];
					*destp++ = v;
				}
				adr -= 0x400;
			}
			for (; i < TextDotX; ++i)
			{
				v = GET_WORD_W8(adr);
				adr += 2;
				v = GrphPal[v & 0x0f];
				*destp++ = v;
			}
		}
		else
		{
			if (x < TextDotX)
			{
				for (; i < x; ++i)
				{
					v = GET_WORD_W8(adr);
					adr += 2;
					v &= 0x0f;
					if (v != 0x00)
						*destp = GrphPal[v];
					destp++;
				}
				adr -= 0x400;
			}
			for (; i < TextDotX; ++i)
			{
				v = GET_WORD_W8(adr);
				adr += 2;
				v &= 0x0f;
				if (v != 0x00)
					*destp = GrphPal[v];
				destp++;
			}
		}
	}
}

/* ���β��̥⡼�ɤϴ��ۤ��Ʋ������� */
void FASTCALL Grp_DrawLine4h(void)
{
	uint16_t *srcp, *destp;
	uint32_t x, y;
	uint32_t i;
	uint16_t v;
	int bits;

	y = GrphScrollY[0] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
		y += VLINE;
	y &= 0x3ff;

	if ((y & 0x200) == 0x000)
	{
		y <<= 10;
		bits = (GrphScrollX[0] & 0x200) ? 4 : 0;
	}
	else
	{
		y    = (y & 0x1ff) << 10;
		bits = (GrphScrollX[0] & 0x200) ? 12 : 8;
	}

	x     = GrphScrollX[0] & 0x1ff;
	srcp  = (uint16_t *)(GVRAM + y + x * 2);
	destp = (uint16_t *)Grp_LineBuf;

	x = ((x & 0x1ff) ^ 0x1ff) + 1;

	for (i = 0; i < TextDotX; ++i)
	{
		v        = *srcp++;
		*destp++ = GrphPal[(v >> bits) & 0x0f];

		if (--x == 0)
		{
			srcp -= 0x200;
			bits ^= 4;
			x = 512;
		}
	}
}

/* ȾƩ�����ü�Pri�Υ١����Ȥʤ�ڡ���������  */
void FASTCALL Grp_DrawLine16SP(void)
{
	uint32_t x, y;
	uint32_t off;
	uint32_t i;
	uint16_t v;

	y = GrphScrollY[0] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
		y += VLINE;
	y = (y & 0x1ff) << 10;

	x   = GrphScrollX[0] & 0x1ff;
	off = y + x * 2;
	x   = (x ^ 0x1ff) + 1;

	for (i = 0; i < TextDotX; ++i)
	{
		v = (Pal_Regs[GVRAM[off + 1] * 2] << 8) | Pal_Regs[GVRAM[off] * 2 + 1];
		if ((GVRAM[off] & 1) == 0)
		{
			Grp_LineBufSP[i]  = 0;
			Grp_LineBufSP2[i] = Pal16[v & 0xfffe];
		}
		else
		{
			Grp_LineBufSP[i]  = Pal16[v & 0xfffe];
			Grp_LineBufSP2[i] = 0;
		}

		off += 2;
		if (--x == 0)
			off -= 0x400;
	}
}

void FASTCALL Grp_DrawLine8SP(int page)
{
	uint32_t x, x0;
	uint32_t y, y0;
	uint32_t off, off0;
	uint32_t i;
	uint16_t v;

	page &= 1;

	y  = GrphScrollY[page * 2] + VLINE;
	y0 = GrphScrollY[page * 2 + 1] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
	{
		y += VLINE;
		y0 += VLINE;
	}
	y  = (y & 0x1ff) << 10;
	y0 = (y0 & 0x1ff) << 10;

	x  = GrphScrollX[page * 2] & 0x1ff;
	x0 = GrphScrollX[page * 2 + 1] & 0x1ff;

	off  = y + x * 2 + page;
	off0 = y0 + x0 * 2 + page;

	x = (x ^ 0x1ff) + 1;

	for (i = 0; i < TextDotX; ++i)
	{
		v                   = (GVRAM[off] & 0x0f) | (GVRAM[off0] & 0xf0);
		Grp_LineBufSP_Tr[i] = 0;

		if ((v & 1) == 0)
		{
			v &= 0xfe;
			if (v != 0x00)
			{
				v = GrphPal[v];
				if (!v)
					Grp_LineBufSP_Tr[i] = 0x1234;
			}

			Grp_LineBufSP[i]  = 0;
			Grp_LineBufSP2[i] = v;
		}
		else
		{
			v &= 0xfe;
			if (v != 0x00)
				v = GrphPal[v] | Ibit;
			Grp_LineBufSP[i]  = v;
			Grp_LineBufSP2[i] = 0;
		}

		off += 2;
		off0 += 2;
		if ((off0 & 0x3fe) == 0)
			off0 -= 0x400;
		if (--x == 0)
			off -= 0x400;
	}
}

void FASTCALL Grp_DrawLine4SP(uint32_t page /*, int opaq*/)
{
	uint32_t scrx, scry;
	uint32_t x, y;
	uint32_t off;
	uint32_t i;
	uint16_t v;

	page &= 3;

	scrx = GrphScrollX[page];
	scry = GrphScrollY[page];

	if (page & 1)
	{
		y = scry + VLINE;
		if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
			y += VLINE;
		y = (y & 0x1ff) << 10;

		x   = scrx & 0x1ff;
		off = y + x * 2;
		if (page & 2)
			off++;
		x = (x ^ 0x1ff) + 1;

		for (i = 0; i < TextDotX; ++i)
		{
			v = GVRAM[off] >> 4;
			if ((v & 1) == 0)
			{
				v &= 0x0e;
				Grp_LineBufSP[i]  = 0;
				Grp_LineBufSP2[i] = GrphPal[v];
			}
			else
			{
				v &= 0x0e;
				Grp_LineBufSP[i]  = GrphPal[v];
				Grp_LineBufSP2[i] = 0;
			}

			off += 2;
			if (--x == 0)
				off -= 0x400;
		}
	}
	else
	{
		y = scry + VLINE;
		if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
			y += VLINE;
		y = (y & 0x1ff) << 10;

		x   = scrx & 0x1ff;
		off = y + x * 2;
		if (page & 2)
			off++;
		x = (x ^ 0x1ff) + 1;

		for (i = 0; i < TextDotX; ++i)
		{
			v = GVRAM[off];
			if ((v & 1) == 0)
			{
				v &= 0x0e;
				Grp_LineBufSP[i]  = 0;
				Grp_LineBufSP2[i] = GrphPal[v];
			}
			else
			{
				v &= 0x0e;
				Grp_LineBufSP[i]  = GrphPal[v];
				Grp_LineBufSP2[i] = 0;
			}

			off += 2;
			if (--x == 0)
				off -= 0x400;
		}
	}
}

void FASTCALL Grp_DrawLine4hSP(void)
{
	uint16_t *srcp;
	uint32_t x, y;
	uint32_t i;
	int bits;
	uint16_t v;

	y = GrphScrollY[0] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
		y += VLINE;
	y &= 0x3ff;

	if ((y & 0x200) == 0x000)
	{
		y <<= 10;
		bits = (GrphScrollX[0] & 0x200) ? 4 : 0;
	}
	else
	{
		y    = (y & 0x1ff) << 10;
		bits = (GrphScrollX[0] & 0x200) ? 12 : 8;
	}

	x    = GrphScrollX[0] & 0x1ff;
	srcp = (uint16_t *)(GVRAM + y + x * 2);
	x    = ((x & 0x1ff) ^ 0x1ff) + 1;

	for (i = 0; i < TextDotX; ++i)
	{
		v = *srcp++ >> bits;
		if ((v & 1) == 0)
		{
			Grp_LineBufSP[i]  = 0;
			Grp_LineBufSP2[i] = GrphPal[v & 0x0e];
		}
		else
		{
			Grp_LineBufSP[i]  = GrphPal[v & 0x0e];
			Grp_LineBufSP2[i] = 0;
		}

		if (--x == 0)
			srcp -= 0x400;
	}
}

/*
 * --- ȾƩ�����оݤȤʤ�ڡ��������� --------------
 * 2�ڡ����ʾ夢�륰��ե��å��⡼�ɤΤߤʤΤǡ�
 * 256��2�� or 16��4�̤Υ⡼�ɤΤߡ�
 * 256�����ϡ�Opaque�Ǥʤ����Υ⡼�ɤϤ���ʤ������
 * ��ɬ��Opaque�⡼�ɤ�Ȧ��
 *
 * �����Ϥޤ�32��x4�̥⡼�ɤμ����򤷤Ƥʤ��줹��
 * �ʤ줸����­��ʤ��褥�ġ�
 *
 * �䤱�ˤ��ä���
 */
void FASTCALL Grp_DrawLine8TR(int page, int opaq)
{
	if (opaq)
	{
		uint32_t x, y;
		uint32_t v, v0;
		uint32_t i;

		page &= 1;

		y = GrphScrollY[page * 2] + VLINE;
		if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
			y += VLINE;
		y = ((y & 0x1ff) << 10) + page;
		x = GrphScrollX[page * 2] & 0x1ff;

		for (i = 0; i < TextDotX; ++i, x = (x + 1) & 0x1ff)
		{
			v0 = Grp_LineBufSP[i];
			v  = GVRAM[y + x * 2];

			if (v0 != 0)
			{
				if (v != 0)
				{
					v = GrphPal[v];
					if (v != 0)
					{
						v0 &= Pal_HalfMask;
						if (v & Ibit)
							v0 |= Pal_Ix2;
						v &= Pal_HalfMask;
						v += v0;
						v >>= 1;
					}
				}
			}
			else
				v = GrphPal[v];
			Grp_LineBuf[i] = (uint16_t)v;
		}
	}
}

void FASTCALL Grp_DrawLine8TR_GT(int page, int opaq)
{
	if (opaq)
	{
		uint32_t x, y;
		uint32_t i;

		page &= 1;

		y = GrphScrollY[page * 2] + VLINE;
		if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
			y += VLINE;
		y = ((y & 0x1ff) << 10) + page;
		x = GrphScrollX[page * 2] & 0x1ff;

		for (i = 0; i < TextDotX; ++i, x = (x + 1) & 0x1ff)
		{
			Grp_LineBuf[i]      = (Grp_LineBufSP[i] || Grp_LineBufSP_Tr[i]) ? 0 : GrphPal[GVRAM[y + x * 2]];
			Grp_LineBufSP_Tr[i] = 0;
		}
	}
}

void FASTCALL Grp_DrawLine4TR(uint32_t page, int opaq)
{
	uint32_t x, y;
	uint32_t v, v0;
	uint32_t i;

	page &= 3;

	y = GrphScrollY[page] + VLINE;
	if ((CRTC_Regs[0x29] & 0x1c) == 0x1c)
		y += VLINE;
	y = (y & 0x1ff) << 10;
	x = GrphScrollX[page] & 0x1ff;

	if (page & 1)
	{
		page >>= 1;
		y += page;

		if (opaq)
		{
			for (i = 0; i < TextDotX; ++i, x = (x + 1) & 0x1ff)
			{
				v0 = Grp_LineBufSP[i];
				v  = GVRAM[y + x * 2] >> 4;

				if (v0 != 0)
				{
					if (v != 0)
					{
						v = GrphPal[v];
						if (v != 0)
						{
							v0 &= Pal_HalfMask;
							if (v & Ibit)
								v0 |= Pal_Ix2;
							v &= Pal_HalfMask;
							v += v0;
							v >>= 1;
						}
					}
				}
				else
					v = GrphPal[v];
				Grp_LineBuf[i] = (uint16_t)v;
			}
		}
		else
		{
			for (i = 0; i < TextDotX; ++i, x = (x + 1) & 0x1ff)
			{
				v0 = Grp_LineBufSP[i];

				if (v0 == 0)
				{
					v = GVRAM[y + x * 2] >> 4;
					if (v != 0)
						Grp_LineBuf[i] = GrphPal[v];
				}
				else
				{
					v = GVRAM[y + x * 2] >> 4;
					if (v != 0)
					{
						v = GrphPal[v];
						if (v != 0)
						{
							v0 &= Pal_HalfMask;
							if (v & Ibit)
								v0 |= Pal_Ix2;
							v &= Pal_HalfMask;
							v += v0;
							v              = GrphPal[v >> 1];
							Grp_LineBuf[i] = (uint16_t)v;
						}
					}
					else
						Grp_LineBuf[i] = (uint16_t)v;
				}
			}
		}
	}
	else
	{
		page >>= 1;
		y += page;

		if (opaq)
		{
			for (i = 0; i < TextDotX; ++i, x = (x + 1) & 0x1ff)
			{
				v  = GVRAM[y + x * 2] & 0x0f;
				v0 = Grp_LineBufSP[i];

				if (v0 != 0)
				{
					if (v != 0)
					{
						v = GrphPal[v];
						if (v != 0)
						{
							v0 &= Pal_HalfMask;
							if (v & Ibit)
								v0 |= Pal_Ix2;
							v &= Pal_HalfMask;
							v += v0;
							v >>= 1;
						}
					}
				}
				else
					v = GrphPal[v];
				Grp_LineBuf[i] = (uint16_t)v;
			}
		}
		else
		{
			for (i = 0; i < TextDotX; ++i, x = (x + 1) & 0x1ff)
			{
				v  = GVRAM[y + x * 2] & 0x0f;
				v0 = Grp_LineBufSP[i];

				if (v0 != 0)
				{
					if (v != 0)
					{
						v = GrphPal[v];
						if (v != 0)
						{
							v0 &= Pal_HalfMask;
							if (v & Ibit)
								v0 |= Pal_Ix2;
							v &= Pal_HalfMask;
							v += v0;
							v >>= 1;
							Grp_LineBuf[i] = (uint16_t)v;
						}
					}
					else
						Grp_LineBuf[i] = (uint16_t)v;
				}
				else if (v != 0)
					Grp_LineBuf[i] = GrphPal[v];
			}
		}
	}
}
