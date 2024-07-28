#ifndef _WINX68K_CRTC_H
#define _WINX68K_CRTC_H

#include <stdint.h>
#include "common.h"

#define CRTC_R00_L     0x00
#define CRTC_R00_H     0x01
#define CRTC_R01_L     0x02
#define CRTC_R01_H     0x03
#define CRTC_R02_L     0x04
#define CRTC_R02_H     0x05
#define CRTC_R03_L     0x06
#define CRTC_R03_H     0x07
#define CRTC_R04_L     0x08
#define CRTC_R04_H     0x09
#define CRTC_R05_L     0x0a
#define CRTC_R05_H     0x0b
#define CRTC_R06_L     0x0c
#define CRTC_R06_H     0x0d
#define CRTC_R07_L     0x0e
#define CRTC_R07_H     0x0f

#define CRTC_R08_L     0x10
#define CRTC_R08_H     0x11
#define CRTC_R09_L     0x12
#define CRTC_R09_H     0x13
#define CRTC_R10_L     0x14
#define CRTC_R10_H     0x15
#define CRTC_R11_L     0x16
#define CRTC_R11_H     0x17
#define CRTC_R12_L     0x18
#define CRTC_R12_H     0x19
#define CRTC_R13_L     0x1a
#define CRTC_R13_H     0x1b
#define CRTC_R14_L     0x1c
#define CRTC_R14_H     0x1d
#define CRTC_R15_L     0x1e
#define CRTC_R15_H     0x1f

#define CRTC_R16_L     0x20
#define CRTC_R16_H     0x21
#define CRTC_R17_L     0x22
#define CRTC_R17_H     0x23
#define CRTC_R18_L     0x24
#define CRTC_R18_H     0x25
#define CRTC_R19_L     0x26
#define CRTC_R19_H     0x27
#define CRTC_R20_L     0x28
#define CRTC_R20_H     0x29
#define CRTC_R21_L     0x2a
#define CRTC_R21_H     0x2b
#define CRTC_R22_L     0x2c
#define CRTC_R22_H     0x2d
#define CRTC_R23_L     0x2e
#define CRTC_R23_H     0x2f

#define	VSYNC_HIGH	180310L
#define	VSYNC_NORM	162707L

extern	uint8_t	CRTC_Regs[48];
extern	uint8_t	CRTC_Mode;
extern	uint16_t CRTC_VSTART, CRTC_VEND;
extern	uint16_t CRTC_HSTART, CRTC_HEND;
extern	uint32_t TextDotX, TextDotY;
extern	uint32_t TextScrollX, TextScrollY;
extern	uint8_t	VCReg0[2];
extern	uint8_t	VCReg1[2];
extern	uint8_t	VCReg2[2];
extern	uint16_t CRTC_IntLine;
extern	uint8_t	CRTC_FastClr;
extern	uint8_t	CRTC_DispScan;
extern	uint32_t CRTC_FastClrLine;
extern	uint16_t CRTC_FastClrMask;
extern	uint8_t	CRTC_VStep;
extern  int	HSYNC_CLK;

extern	uint32_t GrphScrollX[4];
extern	uint32_t GrphScrollY[4];

void CRTC_Init(void);

void CRTC_RasterCopy(void);

uint8_t FASTCALL CRTC_Read(uint32_t adr);
void FASTCALL CRTC_Write(uint32_t adr, uint8_t data);

uint8_t FASTCALL VCtrl_Read(uint32_t adr);
void FASTCALL VCtrl_Write(uint32_t adr, uint8_t data);

#endif /* _WINX68K_CRTC_H */
