#ifndef _winx68k_sysport
#define _winx68k_sysport

#include <stdint.h>
#include "common.h"

extern	uint8_t	SysPort[7];

void SysPort_Init(void);
uint8_t FASTCALL SysPort_Read(uint32_t adr);
void FASTCALL SysPort_Write(uint32_t adr, uint8_t data);

#endif
