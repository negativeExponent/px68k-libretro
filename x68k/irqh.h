#ifndef _WINX68K_IRQH_H
#define _WINX68K_IRQH_H

#define IRQ_DEFAULT_VECTOR 0xFFFFFFFF

void IRQH_Init(void);
void IRQH_IRQCallBack(uint8_t irq);
void IRQH_Int(uint8_t irq, int32_t (*handler)(int32_t));

int32_t my_irqh_callback(int32_t level);

#endif /* _WINX68K_IRQH_H */
