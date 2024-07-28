/*
 *  CRTC.C - CRT Controller / Video Controller
 *  TurtleBazooka - Code correction suggestions
 */

#include	"common.h"
#include	"windraw.h"
#include	"winx68k.h"
#include	"tvram.h"
#include	"gvram.h"
#include "palette.h"
#include	"bg.h"
#include	"m68000.h"
#include	"crtc.h"

uint8_t	CRTC_Regs[24*2];
uint8_t	CRTC_Mode = 0;
uint32_t TextDotX = 768, TextDotY = 512;
uint16_t CRTC_VSTART, CRTC_VEND;
uint16_t CRTC_HSTART, CRTC_HEND;
uint32_t TextScrollX = 0, TextScrollY = 0;
uint32_t GrphScrollX[4] = {0, 0, 0, 0};
uint32_t GrphScrollY[4] = {0, 0, 0, 0};

uint8_t	CRTC_FastClr = 0;
uint8_t	CRTC_SispScan = 0;
uint32_t CRTC_FastClrLine = 0;
uint16_t CRTC_FastClrMask = 0;
uint16_t CRTC_IntLine = 0;
uint8_t	CRTC_VStep = 2;

uint8_t	VCReg0[2] = {0, 0};
uint8_t	VCReg1[2] = {0, 0};
uint8_t	VCReg2[2] = {0, 0};

uint8_t	CRTC_RCFlag[2] = {0, 0};
int HSYNC_CLK = 324;
extern int VID_MODE, CHANGEAV_TIMING;

void CRTC_RasterCopy(void)
{
	uint32_t line = (((uint32_t)CRTC_Regs[CRTC_R22_L])<<2);
	uint32_t src  = (((uint32_t)CRTC_Regs[CRTC_R22_H])<<9);
	uint32_t dst  = (((uint32_t)CRTC_Regs[CRTC_R22_L])<<9);

	static const uint32_t off[4] = { 0, 0x20000, 0x40000, 0x60000 };
	int i, bit;

	for (bit = 0; bit < 4; bit++)
   {
		if (CRTC_Regs[CRTC_R21_L] & (1 << bit))
			memmove(&TVRAM[dst + off[bit]], &TVRAM[src + off[bit]],
			    sizeof(uint32_t) * 128);
	}

	line = (line - TextScrollY) & 0x3ff;
	for (i = 0; i < 4; i++) {
		TextDirtyLine[line] = 1;
		line = (line + 1) & 0x3ff;
	}

	TVRAM_RCUpdate();
}

/*
 * $e82000 256.w -- Graphics Palette
 * $e82200 256.w -- Text Palette, Sprite + BG Palette
 * $e82400 1.w R0 screen mode
 * $e82500 1.w R1 priority control
 * $e82600 1.w R2 ON/OFF control/special priority
 */

uint8_t FASTCALL VCtrl_Read(uint32_t adr)
{
   if (adr < 0x00e82400)
      return Pal_Read(adr);
   if (adr < 0x00e82500)
      return VCReg0[adr&1];
   if (adr < 0x00e82600)
      return VCReg1[adr&1];
   if (adr < 0x00e82700)
      return VCReg2[adr&1];
   return 0xff;
}

void FASTCALL VCtrl_Write(uint32_t adr, uint8_t data)
{
   if (adr < 0x00e82400)
      Pal_Write(adr, data);
   else if (adr < 0x00e82500)
   {
      if (VCReg0[adr&1] != data)
      {
         VCReg0[adr&1] = data;
         TVRAM_SetAllDirty();
      }
   }
   else if (adr < 0x00e82600)
   {
      if (VCReg1[adr&1] != data)
      {
         VCReg1[adr&1] = data;
         TVRAM_SetAllDirty();
      }
   }
   else if (adr < 0x00e82700)
   {
      if (VCReg2[adr&1] != data)
      {
         VCReg2[adr&1] = data;
         TVRAM_SetAllDirty();
      }
   }
}

void CRTC_Init(void)
{
	memset(CRTC_Regs, 0, 48);
	memset(GrphScrollX, 0, sizeof(GrphScrollX));
	memset(GrphScrollY, 0, sizeof(GrphScrollY));

	CRTC_HSTART = 28;
	CRTC_HEND   = 124;
	CRTC_VSTART = 40;
	CRTC_HEND   = 552;

	TextScrollX = 0;
	TextScrollY = 0;
}

uint8_t FASTCALL CRTC_Read(uint32_t adr)
{
   if (adr<0xe803ff)
   {
      int reg;
#ifndef MSB_FIRST
	   adr ^= 1;
#endif
      reg = adr & 0x3f;
      if ( (reg >= 0x28) && (reg <= 0x2b) )
      {
         return CRTC_Regs[reg];
      }

   }
   else if ( adr==0xe80481 )
   {
      if (CRTC_FastClr)
         return (CRTC_Mode | 0x02);
      return (CRTC_Mode & 0xfd);
   }
   return 0x00;
}

void FASTCALL CRTC_Write(uint32_t adr, uint8_t data)
{
   static uint16_t FastClearMask[16] = {
      0xffff, 0xfff0, 0xff0f, 0xff00, 0xf0ff, 0xf0f0, 0xf00f, 0xf000,
      0x0fff, 0x0ff0, 0x0f0f, 0x0f00, 0x00ff, 0x00f0, 0x000f, 0x0000
   };

   int old_vidmode = VID_MODE;
   if (adr<0xe80400)
   {
      int reg;
#ifndef MSB_FIRST
	   adr ^= 1;
#endif
      reg = adr & 0x3f;
      if ( reg>=0x30 ) return;
      if (CRTC_Regs[reg]==data) return;
      CRTC_Regs[reg] = data;
      TVRAM_SetAllDirty();
      switch(reg)
      {
         case 0x04:
         case 0x05:
            CRTC_HSTART = (((uint16_t)CRTC_Regs[CRTC_R02_H] << 8) + CRTC_Regs[CRTC_R02_L]) & 1023;
            if (CRTC_HEND > CRTC_HSTART)
               TextDotX = (CRTC_HEND-CRTC_HSTART)*8;
            BG_HAdjust = ((long)BG_Regs[0x0d]-(CRTC_HSTART+4))*8;				/* ��ʿ�����ϲ����٤ˤ��1/2�Ϥ���ʤ�����Tetris�� */
            break;
         case 0x06:
         case 0x07:
            CRTC_HEND = (((uint16_t)CRTC_Regs[CRTC_R03_H] << 8) + CRTC_Regs[CRTC_R03_L]) & 1023;
            if (CRTC_HEND > CRTC_HSTART)
               TextDotX = (CRTC_HEND-CRTC_HSTART)*8;
            break;
         case 0x08:
         case 0x09:
            VLINE_TOTAL = (((uint16_t)CRTC_Regs[CRTC_R04_H]<<8)+CRTC_Regs[CRTC_R04_L]) & 1023;
            HSYNC_CLK = ((CRTC_Regs[CRTC_R20_L]&0x10)?VSYNC_HIGH:VSYNC_NORM)/VLINE_TOTAL;
            break;
         case 0x0c:
         case 0x0d:
            CRTC_VSTART = (((uint16_t)CRTC_Regs[CRTC_R06_H] << 8) + CRTC_Regs[CRTC_R06_L]) & 1023;
            BG_VLINE = ((long)BG_Regs[0x0f]-CRTC_VSTART)/((BG_Regs[0x11]&4)?1:2);	/* BG�Ȥ���¾������Ƥ���κ�ʬ */
            TextDotY = CRTC_VEND-CRTC_VSTART;
            if ((CRTC_Regs[CRTC_R20_L]&0x14)==0x10)
            {
               TextDotY/=2;
               CRTC_VStep = 1;
            }
            else if ((CRTC_Regs[CRTC_R20_L]&0x14)==0x04)
            {
               TextDotY*=2;
               CRTC_VStep = 4;
            }
            else
               CRTC_VStep = 2;
            break;
         case 0x0e:
         case 0x0f:
            CRTC_VEND = (((uint16_t)CRTC_Regs[CRTC_R07_H] << 8) + CRTC_Regs[CRTC_R07_L]) & 1023;
            TextDotY = CRTC_VEND-CRTC_VSTART;
            if ((CRTC_Regs[CRTC_R20_L]&0x14)==0x10)
            {
               TextDotY/=2;
               CRTC_VStep = 1;
            }
            else if ((CRTC_Regs[CRTC_R20_L]&0x14)==0x04)
            {
               TextDotY*=2;
               CRTC_VStep = 4;
            }
            else
               CRTC_VStep = 2;
            break;
         case 0x28:
            HSYNC_CLK = ((CRTC_Regs[CRTC_R20_L]&0x10)?VSYNC_HIGH:VSYNC_NORM)/VLINE_TOTAL;
            VID_MODE = !!(CRTC_Regs[CRTC_R20_L]&0x10);
            TextDotY = CRTC_VEND-CRTC_VSTART;
            if ((CRTC_Regs[CRTC_R20_L]&0x14)==0x10)
            {
               TextDotY/=2;
               CRTC_VStep = 1;
            }
            else if ((CRTC_Regs[CRTC_R20_L]&0x14)==0x04)
            {
               TextDotY*=2;
               CRTC_VStep = 4;
            }
            else
               CRTC_VStep = 2;
            if (VID_MODE != old_vidmode)
            {
               old_vidmode = VID_MODE;
               CHANGEAV_TIMING=1;
            }
            break;
         case 0x29:
            TVRAM_Cleanup();
            break;
         case 0x12:
         case 0x13:
            CRTC_IntLine = (((uint16_t)CRTC_Regs[CRTC_R09_H]<<8)+CRTC_Regs[CRTC_R09_L])&1023;
            break;
         case 0x14:
         case 0x15:
            TextScrollX = (((uint32_t)CRTC_Regs[CRTC_R10_H]<<8)+CRTC_Regs[CRTC_R10_L])&1023;
            break;
         case 0x16:
         case 0x17:
            TextScrollY = (((uint32_t)CRTC_Regs[CRTC_R11_H]<<8)+CRTC_Regs[CRTC_R11_L])&1023;
            break;
         case 0x18:
         case 0x19:
            GrphScrollX[0] = (((uint32_t)CRTC_Regs[CRTC_R12_H]<<8)+CRTC_Regs[CRTC_R12_L])&1023;
            break;
         case 0x1a:
         case 0x1b:
            GrphScrollY[0] = (((uint32_t)CRTC_Regs[CRTC_R13_H]<<8)+CRTC_Regs[CRTC_R13_L])&1023;
            break;
         case 0x1c:
         case 0x1d:
            GrphScrollX[1] = (((uint32_t)CRTC_Regs[CRTC_R14_H]<<8)+CRTC_Regs[CRTC_R14_L])&511;
            break;
         case 0x1e:
         case 0x1f:
            GrphScrollY[1] = (((uint32_t)CRTC_Regs[CRTC_R15_H]<<8)+CRTC_Regs[CRTC_R15_L])&511;
            break;
         case 0x20:
         case 0x21:
            GrphScrollX[2] = (((uint32_t)CRTC_Regs[CRTC_R16_H]<<8)+CRTC_Regs[CRTC_R16_L])&511;
            break;
         case 0x22:
         case 0x23:
            GrphScrollY[2] = (((uint32_t)CRTC_Regs[CRTC_R17_H]<<8)+CRTC_Regs[CRTC_R17_L])&511;
            break;
         case 0x24:
         case 0x25:
            GrphScrollX[3] = (((uint32_t)CRTC_Regs[CRTC_R18_H]<<8)+CRTC_Regs[CRTC_R18_L])&511;
            break;
         case 0x26:
         case 0x27:
            GrphScrollY[3] = (((uint32_t)CRTC_Regs[CRTC_R19_H]<<8)+CRTC_Regs[CRTC_R19_L])&511;
            break;
         case 0x2a:
         case 0x2b:
            break;
         case 0x2c:				/* CRTCư��ݡ��ȤΥ饹�����ԡ���ON�ˤ��Ƥ����ơʤ��Ƥ������ޤޡˡ� */
         case 0x2d:				/* Src/Dst���������Ѥ��Ƥ����Τ�������餷���ʥɥ饭���Ȥ��� */
            CRTC_RCFlag[reg-0x2c] = 1;	/* Dst�ѹ���˼¹Ԥ���롩 */
            if ((CRTC_Mode&8)&&(CRTC_RCFlag[0])/*&&(CRTC_RCFlag[1])*/)
            {
               CRTC_RasterCopy();
               CRTC_RCFlag[0] = 0;
               CRTC_RCFlag[1] = 0;
            }
            break;
      }
   }
   else if (adr==0xe80481)
   {					/* CRTCư��ݡ��� */
      CRTC_Mode = (data|(CRTC_Mode&2));
      if (CRTC_Mode&8)
      {				/* Raster Copy */
         CRTC_RasterCopy();
         CRTC_RCFlag[0] = 0;
         CRTC_RCFlag[1] = 0;
      }
      if (CRTC_Mode&2)
      {
         CRTC_FastClrLine = vline;
         /* ���λ����Υޥ�����ͭ���餷���ʥ��������� */
         CRTC_FastClrMask = FastClearMask[CRTC_Regs[CRTC_R21_L]&15];
      }
   }
}
