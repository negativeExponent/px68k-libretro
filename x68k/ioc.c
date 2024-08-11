/* IOC.C - I/O Controller */

#include "../x11/common.h"
#include "../x11/state.h"

#include "ioc.h"

uint8_t IOC_IntStat = 0;
uint8_t IOC_IntVect = 0;

void IOC_Init(void)
{
	IOC_IntStat = 0;
	IOC_IntVect = 0;
}

uint8_t FASTCALL IOC_Read(uint32_t adr)
{
	adr &= 0x0f;

	if (adr & 1)
	{
		if (adr == 1)
		{
			return IOC_IntStat;
		}
		
		/* $e9c003: interrupt vector, write only */
		if (adr == 3)
		{
			return 0xff;
		}

		p6logd(" Read unimplemented register $%06x\n", 0xe9c000 + adr);
		return 0xff;
	}

	return 0xff;
}

void FASTCALL IOC_Write(uint32_t adr, uint8_t data)
{
	adr &= 0x0f;

	if (adr & 1)
	{	
		if (adr == 1)
		{
			IOC_IntStat &= 0xf0;
			IOC_IntStat |= data & 0x0f;
		}
		else if (adr == 3)
		{
			IOC_IntVect = (data & 0xfc);
		}
		else
			p6logd(" Write unimplemented register $%06x <- $%02x\n", 0xe9c000 + adr, data);
	}
}

int IOC_StateContext(void *f, int writing) {
	state_context_f(&IOC_IntStat, 1);
	state_context_f(&IOC_IntVect, 1);

	return 1;
}
