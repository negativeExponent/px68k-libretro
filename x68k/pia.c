/* PIA.C - uPD8255 (only the bare minimum) */

#include "../x11/common.h"
#include "../x11/state.h"

#include "../x11/joystick.h"
#include "../m68000/m68000.h"

#include "pia.h"
#include "adpcm.h"

typedef struct {
	uint8_t PortA;
	uint8_t PortB;
	uint8_t PortC;
	uint8_t Ctrl;
} PIA;

static PIA pia;

void PIA_Init(void)
{
	pia.PortA = 0xff;
	pia.PortB = 0xff;
	pia.PortC = 0x0b;
	pia.Ctrl  = 0;
}

static void PIA_SetPortC(uint32_t data)
{
	uint8_t portc;

	portc = pia.PortC;
	pia.PortC = data;

	ADPCM_SetPan(data & 3);

	ADPCM_SetRatio((data >> 2) & 3);

	if ((portc & 0x10) != (pia.PortC & 0x10))
		Joystick_Write(0, (uint8_t)((data & 0x10) ? 0xff : 0x00));

	if ((portc & 0x20) != (pia.PortC & 0x20))
		Joystick_Write(1, (uint8_t)((data & 0x20) ? 0xff : 0x00));

}

uint8_t FASTCALL PIA_Read(uint32_t adr)
{
	if ((adr & 1) == 0)
		return 0xff;

	adr &= 7;

	switch (adr)
	{
	case 1:
		return Joystick_Read(0);

	case 3:
		return Joystick_Read(1);

	case 5:
		return pia.PortC;
	}
	
	p6logd(" PIA: Read unimplemented register $%06x\n", adr);
	return 0xff;
}

void FASTCALL PIA_Write(uint32_t adr, uint8_t data)
{
	if ((adr & 1) == 0)
		return;
	
	adr &= 7;

	switch (adr)
	{
	case 5:
		PIA_SetPortC(data);
		return;
	
	case 7:
		if (data < 0x80)
		{
			uint8_t bit = (data >> 1) & 7;
			uint8_t mask = 1 << bit;

			if (data & 1)
				PIA_SetPortC(pia.PortC | mask);
			else
				PIA_SetPortC(pia.PortC & ~mask);
		}
		return;
	}

	p6logd(" PIA: Write unimplemented register $%06x <- $%02x\n", adr, data);
}

int PIA_StateContext(void *f, int writing) {
	state_context_f(&pia, sizeof(pia));

	return 1;
}
