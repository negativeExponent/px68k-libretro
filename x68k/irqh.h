#ifndef _winx68k_irqh
#define _winx68k_irqh

#include "common.h"

void IRQH_Init(void);
uint32_t FASTCALL IRQH_DefaultVector(uint8_t irq);
void IRQH_IRQCallBack(uint8_t irq);
void IRQH_Int(uint8_t irq, void* handler);

#endif
