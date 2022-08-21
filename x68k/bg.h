#ifndef _winx68k_bg
#define _winx68k_bg

#include <stdint.h>
#include "common.h"

extern	uint8_t	BG_DrawWork0[1024*1024];
extern	uint8_t	BG_DrawWork1[1024*1024];
extern	uint32_t	BG0ScrollX, BG0ScrollY;
extern	uint32_t	BG1ScrollX, BG1ScrollY;
extern	uint32_t	BG_AdrMask;
extern	uint8_t	BG_CHRSIZE;
extern	uint8_t	BG_Regs[0x12];
extern	uint16_t	BG_BG0TOP;
extern	uint16_t	BG_BG1TOP;
extern	long	BG_HAdjust;
extern	long	BG_VLINE;
extern	uint32_t	VLINEBG;

extern	uint8_t	Sprite_DrawWork[1024*1024];
extern	uint16_t	BG_LineBuf[1600];

void BG_Init(void);

uint8_t FASTCALL BG_Read(uint32_t adr);
void FASTCALL BG_Write(uint32_t adr, uint8_t data);

void FASTCALL BG_DrawLine(int32_t opaq, int32_t gd);

#endif
