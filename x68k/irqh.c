/* IRQH.C - IRQ Handler (fictitious device) */

#include "../x11/common.h"
#include "../x11/state.h"

#include "../m68000/m68000.h"

#include "irqh.h"

static uint8_t IRQH_IRQ[8];
static int32_t (*IRQH_CallBack[8])(int32_t);

void IRQH_Init(void)
{
	memset(IRQH_IRQ, 0, 8);
}

static int32_t FASTCALL IRQH_DefaultVector(int32_t irq)
{
	IRQH_IRQCallBack(irq);
	return IRQ_DEFAULT_VECTOR;
}

void IRQH_IRQCallBack(uint8_t irq)
{
	int i;

	IRQH_IRQ[irq & 7] = 0;
	m68000_set_irq_line(0);

	for (i = 7; i > 0; i--)
	{
		if (IRQH_IRQ[i])
		{
			m68000_set_irq_line(i);
			return;
		}
	}
}

void IRQH_Int(uint8_t irq, int32_t (*handler)(int32_t))
{
	int i;

	IRQH_IRQ[irq & 7] = 1;
	if (handler == NULL) IRQH_CallBack[irq & 7] = &IRQH_DefaultVector;
	else IRQH_CallBack[irq & 7] = handler;

	for (i = 7; i > 0; i--)
	{
		if (IRQH_IRQ[i])
		{
			m68000_set_irq_line(i);
			return;
		}
	}
}

int32_t my_irqh_callback(int32_t level)
{
	int32_t (*func)(int32_t) = IRQH_CallBack[level & 7] ? IRQH_CallBack[level & 7] : &IRQH_DefaultVector;
	int32_t vect = (*func)(level & 7);
	int i;

	for (i = 7; i > 0; i--)
	{
		if (IRQH_IRQ[i])
		{
			m68000_set_irq_line(i);
			break;
		}
	}

	return (int32_t)vect;
}

int IRQH_StateContext(void *f, int writing) {
	state_context_f(IRQH_IRQ, sizeof(IRQH_IRQ));

	return 1;
}
