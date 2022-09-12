/*
 *  SRAM.C - SRAM (16kb) 領域
 */

#include "common.h"
#include "sram.h"
#include "dosio.h"
#include "prop.h"
#include "sysport.h"
#include "x68kmemory.h"

uint8_t SRAM[0x4000];
static char SRAMFILE[] = "sram.dat";

void SRAM_SetRAMSize(int size)
{
	if ((cpu_readmem24(0xed0009) >> 4) == size)
		return;

	cpu_writemem24(0xe8e00d, 0x31); /* SRAM Write permission */
	cpu_writemem24(0xed0008, 0x00);
	cpu_writemem24(0xed0009, ((size << 4) & 0xf0));
	cpu_writemem24(0xed000a, 0x00);
	cpu_writemem24(0xed000b, 0x00);
	cpu_writemem24(0xe8e00d, 0x00);
}

void SRAM_Clear(void)
{
	int i;

	cpu_writemem24(0xe8e00d, 0x31); /* SRAM Write permission */
	for (i = 0; i < 0x4000; i++)
		cpu_writemem24(0xed0000 + i, 0xff);
	cpu_writemem24(0xe8e00d, 0x00);
}

void SRAM_VirusCheck(void)
{
	if (!Config.SRAMWarning)
		return;

	if ((cpu_readmem24_dword(0xed3f60) == 0x60000002) &&
	    (cpu_readmem24_dword(0xed0010) == 0x00ed3f60)) /* Only works for specific viruses */
	{
		SRAM_Cleanup();
		SRAM_Init(); /* Write data after virus cleanup */
	}
}

void SRAM_Init(void)
{
	int i;
	uint8_t tmp;
	void *fp;

	for (i = 0; i < 0x4000; i++)
		SRAM[i] = 0xFF;

	fp = file_open_c(SRAMFILE);
	if (fp)
	{
		file_lread(fp, SRAM, 0x4000);
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
		fp = file_create_c(SRAMFILE, FTYPE_SRAM);
	if (fp)
	{
		file_lwrite(fp, SRAM, 0x4000);
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
	if ((SysPort[5] == 0x31) && (adr < 0xed4000))
	{
		if ((adr == 0xed0018) && (data == 0xb0)) /* SRAM起動への切り替え（簡単なウィルス対策） */
		{
			if (Config.SRAMWarning) /* Warning発生モード（デフォルト） */
			{
			}
		}
		adr &= 0xffff;
		adr ^= 1;
		SRAM[adr] = data;
	}
}

void FASTCALL SRAM_UpdateBoot(void)
{
	cpu_writemem24(0xe8e00d, 0x31);                                    /* SRAM write permission */
	cpu_writemem24_dword(0xed0040, cpu_readmem24_dword(0xed0040) + 1); /* Estimated operation time(min.) */
	cpu_writemem24_dword(0xed0044, cpu_readmem24_dword(0xed0044) + 1); /* Estimated booting times */
	cpu_writemem24(0xe8e00d, 0x00);
}
