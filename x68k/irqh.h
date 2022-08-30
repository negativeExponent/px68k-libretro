#ifndef _WINX68K_IRQH_H
#define _WINX68K_IRQH_H

#include "common.h"

#define IRQ_DEFAULT_VECTOR 0xFFFFFFFF

void IRQH_Init(void);
int32_t FASTCALL IRQH_DefaultVector(int32_t irq);
void IRQH_IRQCallBack(uint8_t irq);
void IRQH_Int(uint8_t irq, int32_t (*handler)(int32_t));

#endif /* _WINX68K_IRQH_H */
