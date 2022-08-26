#ifndef _winx68k_pia
#define _winx68k_pia

#include "common.h"

extern	uint8_t	PIA_PortA;
extern	uint8_t	PIA_PortB;
extern	uint8_t	PIA_PortC;

void PIA_Init(void);
uint8_t FASTCALL PIA_Read(uint32_t adr);
void FASTCALL PIA_Write(uint32_t adr, uint8_t data);

#endif
