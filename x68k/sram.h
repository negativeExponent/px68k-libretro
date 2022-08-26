#ifndef _winx68k_sram
#define _winx68k_sram

#include "common.h"

extern	uint8_t	SRAM[0x4000];

void SRAM_Init(void);
void SRAM_Cleanup(void);
void SRAM_VirusCheck(void);

uint8_t FASTCALL SRAM_Read(uint32_t adr);
void FASTCALL SRAM_Write(uint32_t adr, uint8_t data);

#endif

