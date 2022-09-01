#ifndef _WINX68K_IOC_H
#define _WINX68K_IOC_H

#include "common.h"

extern uint8_t IOC_IntStat;
extern uint8_t IOC_IntVect;

void IOC_Init(void);
uint8_t FASTCALL IOC_Read(uint32_t adr);
void FASTCALL IOC_Write(uint32_t adr, uint8_t data);

#endif /* _WINX68K_IOC_H */
