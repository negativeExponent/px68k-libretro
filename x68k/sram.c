// ---------------------------------------------------------------------------------------
//  SRAM.C - SRAM (16kb) 領域
// ---------------------------------------------------------------------------------------

#include "sram.h"
#include "common.h"
#include "fileio.h"
#include "prop.h"
#include "sysport.h"
#include "winx68k.h"
#include "x68kmemory.h"

uint8_t SRAM[0x4000];
static char SRAMFILE[] = "sram.dat";

void SRAM_SetRAMSize(int size)
{
	if ((Memory_ReadB(0xed0009) >> 4) == size)
		return;

	Memory_WriteB(0xe8e00d, 0x31); /* SRAM Write permission */
	Memory_WriteB(0xed0008, 0x00);
	Memory_WriteB(0xed0009, ((size << 4) & 0xf0));
	Memory_WriteB(0xed000a, 0x00);
	Memory_WriteB(0xed000b, 0x00);
	Memory_WriteB(0xe8e00d, 0x00);
}

void SRAM_Clear(void)
{
	int i;

	Memory_WriteB(0xe8e00d, 0x31); /* SRAM Write permission */
	for (i = 0; i < 0x4000; i++)
		Memory_WriteB(0xed0000 + i, 0xff);
	Memory_WriteB(0xe8e00d, 0x00);
}

// -----------------------------------------------------------------------
//   役に立たないうぃるすチェック
// -----------------------------------------------------------------------
void SRAM_VirusCheck(void)
{
	if (!Config.SRAMWarning)
		return; // Warning発生モードでなければ帰る

	if ((cpu_readmem24_dword(0xed3f60) == 0x60000002) &&
	    (cpu_readmem24_dword(0xed0010) == 0x00ed3f60)) // 特定うぃるすにしか効かないよ~
	{
		SRAM_Cleanup();
		SRAM_Init(); // Virusクリーンアップ後のデータを書き込んでおく
	}
}

// -----------------------------------------------------------------------
//   初期化
// -----------------------------------------------------------------------
void SRAM_Init(void)
{
	int i;
	uint8_t tmp;
	void *fp;

	for (i = 0; i < 0x4000; i++)
		SRAM[i] = 0xFF;

	fp = File_OpenCurDir(SRAMFILE);
	if (fp)
	{
		File_Read(fp, SRAM, 0x4000);
		File_Close(fp);
		for (i = 0; i < 0x4000; i += 2)
		{
			tmp         = SRAM[i];
			SRAM[i]     = SRAM[i + 1];
			SRAM[i + 1] = tmp;
		}
	}
}

// -----------------------------------------------------------------------
//   撤収~
// -----------------------------------------------------------------------
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

	fp = File_OpenCurDir(SRAMFILE);
	if (!fp)
		fp = File_CreateCurDir(SRAMFILE, FTYPE_SRAM);
	if (fp)
	{
		File_Write(fp, SRAM, 0x4000);
		File_Close(fp);
	}
}

// -----------------------------------------------------------------------
//   りーど
// -----------------------------------------------------------------------
uint8_t FASTCALL SRAM_Read(uint32_t adr)
{
	adr &= 0xffff;
	adr ^= 1;
	if (adr < 0x4000)
		return SRAM[adr];
	else
		return 0xff;
}

// -----------------------------------------------------------------------
//   らいと
// -----------------------------------------------------------------------
void FASTCALL SRAM_Write(uint32_t adr, uint8_t data)
{
	if ((SysPort[5] == 0x31) && (adr < 0xed4000))
	{
		if ((adr == 0xed0018) && (data == 0xb0)) // SRAM起動への切り替え（簡単なウィルス対策）
		{
			if (Config.SRAMWarning) // Warning発生モード（デフォルト）
			{
			}
		}
		adr &= 0xffff;
		adr ^= 1;
		SRAM[adr] = data;
	}
}
