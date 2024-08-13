/*
 *  SYSPORT.C - X68k System Port
 */

#include "../x11/common.h"

#include "../x11/prop.h"

#include "sysport.h"
#include "palette.h"
#include "sram.h"

#include "../x11/state.h"

uint8_t SysPort[8];

void SysPort_Init(void)
{
	int i;

	for (i = 0; i < 7; i++)
		SysPort[i] = 0;
}

uint8_t FASTCALL SysPort_Read(uint32_t adr)
{
	if ((adr & 1) == 0)
	{
		return 0xff;
	}

	adr &= 0x0f;
	
	switch (adr)
	{
	case 0x01:
		return SysPort[1];

	case 0x03:
		return SysPort[2];

	case 0x05:
		return SysPort[3];

	case 0x07:
		return SysPort[4];

	case 0x0b:
		/* 10MHz: 0xff, 16MHz: 0xfe, 030(25MHz): 0xdc are returned
		 * respectively */
		switch (Config.XVIMode)
		{
		case 1: /* x68030 */
			return 0xdc;

		case 2: /* XVI or Compact */
		case 3:
			return 0xfe;

		default: /* 10MHz */
			break;
		}

		return 0xff;

	case 0x0d:
		return 0xff;

	case 0x0f:
		return 0xff;
	}

	/* should not reach here. */
	return 0xff;
}

void FASTCALL SysPort_Write(uint32_t adr, uint8_t data)
{
	if ((adr & 1) == 0)
	{
		return;
	}

	adr &= 0x0f;

	switch (adr)
	{
	case 0x01:
		if (SysPort[1] != (data & 15))
		{
			SysPort[1] = data & 15;
			Pal_ChangeContrast(SysPort[1]);
		}
		break;

	case 0x03:
		SysPort[2] = data & 0x0b;
		break;

	case 0x05:
		SysPort[3] = data & 0x1f;
		break;

	case 0x07:
		SysPort[4] = data & 0x0e;
		break;

	case 0x0d:
		SysPort[5] = data;
		if (data == 0x31)
			SRAM_WriteEnable(TRUE);
		else
			SRAM_WriteEnable(FALSE);
		break;

	case 0x0f:
		SysPort[6] = data & 15;
		break;
	}
}

int SysPort_StateContext(void *f, int writing) {
	state_context_f(SysPort, sizeof(SysPort));

	return 1;
}
