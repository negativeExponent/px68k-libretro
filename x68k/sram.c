/*
 *  SRAM.C - SRAM (16kb)
 */

#include "../x11/common.h"

#include "../x11/prop.h"
#include "dosio.h"

#include "sram.h"
#include "sysport.h"
#include "x68kmemory.h"

uint8_t SRAM[0x4000];
static char SRAMFILE[] = "sram.dat";

void SRAM_SetMem(uint16_t adr, uint8_t val)
{
	if (SRAM[adr ^ 1] != val)
	{
		SRAM[adr ^ 1] = val;
	}
}

/**
 * Set RAM size (in MB)
 */
void SRAM_SetRAMSize(int size)
{
	if ((SRAM[0x09 ^ 1] >> 4) == size)
		return;

	SRAM_SetMem(0x08, 0x00);
	SRAM_SetMem(0x09, (size << 4) & 0xf0);
	SRAM_SetMem(0x0a, 0x00);
	SRAM_SetMem(0x0b, 0x00);
}

void SRAM_Clear(void)
{
	memset(SRAM, 0xff, 0x4000);
}

void SRAM_UpdateBoot(void)
{
	uint16_t *tmp;

	/* Estimated operation time(min.) */
	tmp = (uint16_t *)&SRAM[0x40];
	if (tmp[1] != 0xffff)
	{
		tmp[1] = tmp[1] + 1;
	}
	else
	{
		tmp[1] = 0x0000;
		tmp[0] = tmp[0] + 1;
	}

	/* Estimated booting times */
	tmp = (uint16_t *)&SRAM[0x44];
	if (tmp[1] != 0xffff)
	{
		tmp[1] = tmp[1] + 1;
	}
	else
	{
		tmp[1] = 0x0000;
		tmp[0] = tmp[0] + 1;
	}
}

void SRAM_Init(void)
{
	int i;
	uint8_t tmp;
	void *fp;

	SRAM_Clear();

	fp = file_open_rb_c(SRAMFILE);
	if (fp)
	{
		file_read(fp, SRAM, 0x4000);
		file_close(fp);
		for (i = 0; i < 0x4000; i += 2)
		{
			tmp         = SRAM[i];
			SRAM[i]     = SRAM[i + 1];
			SRAM[i + 1] = tmp;
		}
	}
}

void SRAM_Cleanup(void)
{
	int i;
	uint8_t tmp;
	void *fp;

	for (i = 0; i < 0x4000; i += 2)
	{
		tmp         = SRAM[i];
		SRAM[i]     = SRAM[i + 1];
		SRAM[i + 1] = tmp;
	}

	fp = file_open_c(SRAMFILE);
	if (!fp)
		fp = file_create_c(SRAMFILE);
	if (fp)
	{
		file_write(fp, SRAM, 0x4000);
		file_close(fp);
	}
}

uint8_t FASTCALL SRAM_Read(uint32_t adr)
{
	adr &= 0xffff;
	adr ^= 1;
	if (adr < 0x4000)
		return SRAM[adr];
	return 0xff;
}

void FASTCALL SRAM_Write(uint32_t adr, uint8_t data)
{
	if (SysPort[5] != 0x31) /* write enabled? */
		return;

	if (adr < 0xed4000)
	{
		adr &= 0xffff;
		adr ^= 1;
		SRAM[adr] = data;
	}
}
