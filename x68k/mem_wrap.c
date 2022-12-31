/*	$Id: mem_wrap.c,v 1.2 2003/12/05 18:07:19 nonaka Exp $	*/

#include "../x11/common.h"

#include "../m68000/m68000.h"
#include "../x11/prop.h"

#include "adpcm.h"
#include "bg.h"
#include "crtc.h"
#include "dmac.h"
#include "fdc.h"
#include "gvram.h"
#include "ioc.h"
#include "mercury.h"
#include "mfp.h"
#include "midi.h"
#include "pia.h"
#include "rtc.h"
#include "sasi.h"
#include "scc.h"
#include "scsi.h"
#include "sram.h"
#include "sysport.h"
#include "tvram.h"
#include "x68kmemory.h"

#include "../fmgen/fmg_wrap.h"

static void wm_main(uint32_t addr, uint8_t val);
static void wm_cnt(uint32_t addr, uint8_t val);
static void wm_buserr(uint32_t addr, uint8_t val);
static void wm_nop(uint32_t addr, uint8_t val);

static uint8_t rm_main(uint32_t addr);
static uint8_t rm_nop(uint32_t addr);
static uint8_t rm_buserr(uint32_t addr);

static void AdrError(uint32_t, uint32_t);
static void BusError(uint32_t, uint32_t);

static uint8_t (*MemReadTable[])(uint32_t) = {
/*	$0000		$2000		$4000		$6000		$8000		$a000		$c000		$e000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e00000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e10000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e20000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e30000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e40000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e50000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e60000 */
	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	TVRAM_Read,	/* $e70000 */
	CRTC_Read,	VCtrl_Read,	DMA_Read,	rm_nop,		MFP_Read,	RTC_Read,	rm_nop,		SysPort_Read,	/* $e80000 */
	OPM_Read,	ADPCM_Read,	FDC_Read,	SASI_Read,	SCC_Read,	PIA_Read,	IOC_Read,	rm_nop,		/* $e90000 */
	SCSI_Read,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	MIDI_Read,	/* $ea0000 */
	BG_Read,	BG_Read,	BG_Read,	BG_Read,	BG_Read,	BG_Read,	BG_Read,	BG_Read,	/* $eb0000 */
#ifndef	NO_MERCURY
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	Mcry_Read,	rm_buserr,	/* $ec0000 */
#else
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	/* $ec0000 */
#endif
	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	/* $ed0000 */
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	/* $ee0000 */
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	/* $ef0000 */
};

static void (*MemWriteTable[])(uint32_t, uint8_t) = {
/*	$0000			$2000			$4000			$6000			$8000			$a000			$c000			$e000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e00000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e10000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e20000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e30000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e40000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e50000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e60000 */
	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	TVRAM_Write,	/* $e70000 */
	CRTC_Write,		VCtrl_Write,	DMA_Write,		wm_nop,			MFP_Write,		RTC_Write,		wm_nop,			SysPort_Write,	/* $e80000 */
	OPM_Write,		ADPCM_Write,	FDC_Write,		SASI_Write,		SCC_Write,		PIA_Write,		IOC_Write,		wm_nop,			/* $e90000 */
	SCSI_Write,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		MIDI_Write,		/* $ea0000 */
	BG_Write,		BG_Write,		BG_Write,		BG_Write,		BG_Write,		BG_Write,		BG_Write,		BG_Write,		/* $eb0000 */
#ifndef	NO_MERCURY
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		Mcry_Write,		wm_buserr,		/* $ec0000 */
#else
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $ec0000 */
#endif
	SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		/* $ed0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $ee0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $ef0000 */
};

static int RAMSize;

uint8_t *IPL;
uint8_t *MEM;
uint8_t *OP_ROM;
uint8_t *FONT;

uint32_t BusErrFlag     = 0;
uint32_t BusErrHandling = 0;
uint32_t BusErrAdr      = 0;

/*
 * write function
 */
void dma_writemem24(uint32_t addr, uint32_t val)
{
	wm_main(addr, val & 0xff);
}

void dma_writemem24_word(uint32_t addr, uint32_t val)
{
	if (addr & 1)
	{
		BusErrFlag |= 4;
		return;
	}

	wm_main(addr, (val >> 8) & 0xff);
	wm_main(addr + 1, val & 0xff);
}

void dma_writemem24_dword(uint32_t addr, uint32_t val)
{
	if (addr & 1)
	{
		BusErrFlag |= 4;
		return;
	}

	wm_main(addr, (val >> 24) & 0xff);
	wm_main(addr + 1, (val >> 16) & 0xff);
	wm_main(addr + 2, (val >> 8) & 0xff);
	wm_main(addr + 3, val & 0xff);
}

void cpu_writemem24(uint32_t addr, uint32_t val)
{
	BusErrFlag    = 0;

	wm_cnt(addr, val & 0xff);
	if (BusErrFlag & 2)
	{
		BusError(addr, val);
	}
}

void cpu_writemem24_word(uint32_t addr, uint32_t val)
{
	if (addr & 1)
	{
		AdrError(addr, val);
		return;
	}

	BusErrFlag = 0;

	wm_cnt(addr, (val >> 8) & 0xff);
	wm_main(addr + 1, val & 0xff);

	if (BusErrFlag & 2)
	{
		BusError(addr, val);
	}
}

void cpu_writemem24_dword(uint32_t addr, uint32_t val)
{
	if (addr & 1)
	{
		AdrError(addr, val);
		return;
	}

	BusErrFlag = 0;

	wm_cnt(addr, (val >> 24) & 0xff);
	wm_main(addr + 1, (val >> 16) & 0xff);
	wm_main(addr + 2, (val >> 8) & 0xff);
	wm_main(addr + 3, val & 0xff);

	if (BusErrFlag & 2)
	{
		BusError(addr, val);
	}
}

static void wm_main(uint32_t addr, uint8_t val)
{
	if ((BusErrFlag & 7) == 0)
		wm_cnt(addr, val);
}

static void wm_cnt(uint32_t addr, uint8_t val)
{
	addr &= 0xffffff;
	/* RAM */
	if (addr < RAMSize)
	{
		MEM[addr ^ 1] = val;
		return;
	}
	/* IPL, SCSI, FONT */
	if (addr >= 0xf00000)
	{
		return;
	}
	if (addr >= 0xe00000)
	{
		int index = addr >> 13;
		index &= 0xff;
		MemWriteTable[index](addr, val);
		return;
	}
	if (addr >= 0xc00000)
	{
		GVRAM_Write(addr, val);
		return;
	}

	wm_buserr(addr, val);
}

static void wm_buserr(uint32_t addr, uint8_t val)
{
	BusErrFlag = 2;
	BusErrAdr  = addr;
	(void)val;
}

static void wm_nop(uint32_t addr, uint8_t val)
{
	/* Nothing to do */
	(void)addr;
	(void)val;
}

/*
 * read function
 */
uint32_t dma_readmem24(uint32_t addr)
{
	return rm_main(addr);
}

uint32_t dma_readmem24_word(uint32_t addr)
{
	uint32_t v;

	if (addr & 1)
	{
		BusErrFlag = 3;
		return 0;
	}

	v = rm_main(addr) << 8;
	v |= rm_main(addr + 1);
	return v;
}

uint32_t dma_readmem24_dword(uint32_t addr)
{
	uint32_t v;

	if (addr & 1)
	{
		BusErrFlag = 3;
		return 0;
	}

	v = rm_main(addr) << 24;
	v |= rm_main(addr + 1) << 16;
	v |= rm_main(addr + 2) << 8;
	v |= rm_main(addr + 3);
	return v;
}

uint32_t cpu_readmem24(uint32_t addr)
{
	uint32_t v;

	v = rm_main(addr);
	if (BusErrFlag & 1)
	{
		p6logd("cpu_readmem24: addr = %x flag = %d\n", addr, BusErrFlag);
		BusError(addr, 0);
	}
	return v;
}

uint32_t cpu_readmem24_word(uint32_t addr)
{
	uint32_t v;

	if (addr & 1)
	{
		AdrError(addr, 0);
		return 0;
	}

	BusErrFlag = 0;

	v = rm_main(addr) << 8;
	v |= rm_main(addr + 1);
	if (BusErrFlag & 1)
	{
		p6logd("cpu_readmem24_word: addr = %x flag = %d\n", addr, BusErrFlag);
		BusError(addr, 0);
	}
	return v;
}

uint32_t cpu_readmem24_dword(uint32_t addr)
{
	uint32_t v;

	if (addr & 1)
	{
		BusErrFlag = 3;
		p6logd("cpu_readmem24_dword: addr = %x\n", addr);
		return 0;
	}

	BusErrFlag = 0;

	v = rm_main(addr) << 24;
	v |= rm_main(addr + 1) << 16;
	v |= rm_main(addr + 2) << 8;
	v |= rm_main(addr + 3);
	return v;
}

static uint8_t rm_main(uint32_t addr)
{
	addr &= 0xffffff;
	/* MEM */
	if (addr < RAMSize)
	{
		return MEM[addr ^ 1];
	}
	/* IPL/SCSI*/
	if (addr >= 0xfc0000)
	{
		addr &= 0x3ffff;
		addr ^= 1;
		return IPL[addr];
	}
	/* FONT */
	if (addr >= 0xf00000)
	{
		addr &= 0xfffff;
		addr ^= 1;
		return FONT[addr];
	}
	if (addr >= 0xe00000)
	{
		int index = addr >> 13;
		index &= 0xff;
		return MemReadTable[index](addr);
	}
	/* GVRAM */
	if (addr >= 0xc00000)
	{
		return GVRAM_Read(addr);
	}

	return rm_buserr(addr);
}

static uint8_t rm_nop(uint32_t addr)
{
	p6logd("rm_nop: addr = %x\n", addr);
	return 0;
}

static uint8_t rm_buserr(uint32_t addr)
{
	p6logd("rm_buserr: addr = %x flag = %d\n", addr, BusErrFlag);

	BusErrFlag = 1;
	BusErrAdr  = addr;

	return 0;
}

static void cpu_setOPbase24(uint32_t addr)
{
	switch ((addr >> 20) & 0xf) {
	case 0: case 1: case 2: case 3:
	case 4: case 5: case 6: case 7:
	case 8: case 9: case 0xa: case 0xb:
		OP_ROM = MEM;
		break;

	case 0xc:
	case 0xd:
		OP_ROM = GVRAM + (addr - 0x00c00000);
		break;

	case 0xe:
		if (addr < 0x00e80000)
			OP_ROM = TVRAM + (addr - 0x00e00000);
		else if ((addr >= 0x00ea0000) && (addr < 0x00ea2000))
			OP_ROM = SCSIIPL + (addr - 0x00ea0000);
		else if ((addr >= 0x00ed0000) && (addr < 0x00ed4000))
			OP_ROM = SRAM + (addr - 0x00ed0000);
		else
		{
			BusErrFlag = 3;
			BusErrAdr  = addr;
			BusError(addr, 0);
		}
		break;

	case 0xf:
		if ((addr >= 0x00fc0000) && (addr < 0x01000000))
			OP_ROM = IPL + (addr - 0x00fc0000);
		else
		{
			BusErrFlag = 3;
			BusErrAdr  = addr;
			BusError(addr, 0);
		}
		break;
	}
}

/*
 * Memory misc
 */
void Memory_Init(void)
{
#if defined(HAVE_CYCLONE)
	cpu_setOPbase24((uint32_t)m68000_get_reg(M68K_PC));
#elif defined(HAVE_M68000)
	cpu_setOPbase24((uint32_t)C68k_Get_Reg(&C68K, C68K_PC));
#elif defined(HAVE_C68K)
	cpu_setOPbase24((uint32_t)C68k_Get_PC(&C68K));
#elif defined(HAVE_MUSASHI)
	cpu_setOPbase24((uint32_t)m68k_get_reg(NULL, M68K_REG_PC));
#endif

	SRAM_SetRAMSize(Config.ramSize);
	RAMSize = Config.ramSize * 0x100000;
}

void Memory_SetSCSIMode(void)
{
	int i;

	for (i = 0xe0; i < 0xf0; i++)
	{
		MemReadTable[i] = rm_buserr;
	}
}

static void AdrError(uint32_t adr, uint32_t unknown)
{
	(void)adr;
	(void)unknown;
	p6logd("AdrError: %x\n", adr);
}

#if defined (HAVE_MUSASHI)
void m68k_pulse_bus_error(void);
#endif

static void BusError(uint32_t adr, uint32_t unknown)
{
	(void)adr;
	(void)unknown;
	p6logd("BusError: %x\n", adr);
#if defined (HAVE_MUSASHI)
	m68k_pulse_bus_error();
#else
	BusErrHandling = 1;
#endif
}
