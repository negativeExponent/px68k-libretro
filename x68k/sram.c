// ---------------------------------------------------------------------------------------
//  SRAM.C - SRAM (16kb) �ΰ�
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
//   ���Ω���ʤ������뤹�����å�
// -----------------------------------------------------------------------
void SRAM_VirusCheck(void)
{
	if (!Config.SRAMWarning)
		return; // Warningȯ���⡼�ɤǤʤ���е���

	if ((cpu_readmem24_dword(0xed3f60) == 0x60000002) &&
	    (cpu_readmem24_dword(0xed0010) == 0x00ed3f60)) // ���ꤦ���뤹�ˤ��������ʤ��菢�
	{
		SRAM_Cleanup();
		SRAM_Init(); // Virus���꡼�󥢥å׸�Υǡ�����񤭹���Ǥ���
	}
}

// -----------------------------------------------------------------------
//   �����
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
//   ű�����
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
//   �꡼��
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
//   �餤��
// -----------------------------------------------------------------------
void FASTCALL SRAM_Write(uint32_t adr, uint8_t data)
{
	if ((SysPort[5] == 0x31) && (adr < 0xed4000))
	{
		if ((adr == 0xed0018) && (data == 0xb0)) // SRAM��ư�ؤ��ڤ��ؤ��ʴ�ñ�ʥ����륹�к���
		{
			if (Config.SRAMWarning) // Warningȯ���⡼�ɡʥǥե���ȡ�
			{
			}
		}
		adr &= 0xffff;
		adr ^= 1;
		SRAM[adr] = data;
	}
}
