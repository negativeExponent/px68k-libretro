/*
 *  SYSPORT.C - X68k System Port
 */

#include "../x11/common.h"

#include "../x11/prop.h"

#include "sysport.h"
#include "palette.h"

uint8_t SysPort[7];

void SysPort_Init(void)
{
	int i;

	for (i = 0; i < 7; i++)
		SysPort[i] = 0;
}

void FASTCALL SysPort_Write(uint32_t adr, uint8_t data)
{
	switch (adr)
	{
	case 0xe8e001:
		if (SysPort[1] != (data & 15))
		{
			SysPort[1] = data & 15;
			Pal_ChangeContrast(SysPort[1]);
		}
		break;
	case 0xe8e003:
		SysPort[2] = data & 0x0b;
		break;
	case 0xe8e005:
		SysPort[3] = data & 0x1f;
		break;
	case 0xe8e007:
		SysPort[4] = data & 0x0e;
		break;
	case 0xe8e00d:
		SysPort[5] = data;
		break;
	case 0xe8e00f:
		SysPort[6] = data & 15;
		break;
	}
}

uint8_t FASTCALL SysPort_Read(uint32_t adr)
{
	switch (adr)
	{
	case 0xe8e001:
		return SysPort[1];
	case 0xe8e003:
		return SysPort[2];
	case 0xe8e005:
		return SysPort[3];
	case 0xe8e007:
		return SysPort[4];
	case 0xe8e00b:
		/* 10MHz:0xff、16MHz:0xfe、030(25MHz):0xdcをそれぞれ返すらしい */
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
	case 0xe8e00d:
		return SysPort[5];
	case 0xe8e00f:
		return SysPort[6];
	}

	return 0xff;
}
