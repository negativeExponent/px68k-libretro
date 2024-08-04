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
#include "opm.h"
#include "pia.h"
#include "rtc.h"
#include "sasi.h"
#include "scc.h"
#include "scsi.h"
#include "sram.h"
#include "sysport.h"
#include "tvram.h"
#include "vc.h"
#include "x68kmemory.h"

static void wm_main_b(uint32_t adr, uint8_t data);
static void wm_main_w(uint32_t adr, uint16_t data);
static void wm_buserr(uint32_t adr, uint8_t data);
static void wm_nop(uint32_t adr, uint8_t data);

static uint8_t rm_main_b(uint32_t adr);
static uint16_t rm_main_w(uint32_t adr);
static uint8_t rm_font(uint32_t adr);
static uint8_t rm_ipl(uint32_t adr);
static uint8_t rm_nop(uint32_t adr);
static uint8_t rm_buserr(uint32_t adr);

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
#ifdef	HAVE_MERCURY
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	Mcry_Read,	rm_buserr,	/* $ec0000 */
#else
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	/* $ec0000 */
#endif
	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	SRAM_Read,	/* $ed0000 */
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	/* $ee0000 */
	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	rm_buserr,	/* $ef0000 */

	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f00000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f10000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f20000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f30000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f40000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f50000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f60000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f70000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f80000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $f90000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $fa0000 */
	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	rm_font,	/* $fb0000 */
	/* for SCSO will it be rm_buserr�� */
	rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		/* $fc0000 */
	rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		/* $fd0000 */
	rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		/* $fe0000 */
	rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		rm_ipl,		/* $ff0000 */
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
#ifdef	HAVE_MERCURY
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		Mcry_Write,		wm_buserr,		/* $ec0000 */
#else
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $ec0000 */
#endif
	SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		SRAM_Write,		/* $ed0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $ee0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $ef0000 */
	/* Any write to the ROM area is a bus error */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f00000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f10000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f20000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f30000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f40000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f50000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f60000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f70000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f80000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $f90000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $fa0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $fb0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $fc0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $fd0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $fe0000 */
	wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		wm_buserr,		/* $ff0000 */
};

uint8_t *OP_ROM;

uint8_t IPL[IPL_SIZE];
uint8_t MEM[MEM_SIZE];
uint8_t FONT[FONT_SIZE];

uint32_t BusErrFlag     = 0;
uint32_t BusErrHandling = 0;
uint32_t BusErrAdr      = 0;

/* Set an initial RAM size since most c68k cores use
memory reads to set initial PC and SR on Reset */
static uint32_t system_ram = 0x100000;

/*
 * write function
 */
void dma_writemem24(uint32_t adr, uint8_t data)
{
	if ((BusErrFlag & 7) == 0)
	{
		wm_main_b(adr, data);
	}
}

void dma_writemem24_word(uint32_t adr, uint16_t data)
{
	if (adr & 1)
	{
		BusErrFlag |= 4;
		return;
	}

	if ((BusErrFlag & 7) == 0)
	{
		wm_main_w(adr, data);
	}
}

void cpu_writemem24(uint32_t adr, uint32_t data)
{
	BusErrFlag = 0;

	wm_main_b(adr, (uint8_t)data);

	if (BusErrFlag & 2)
	{
		BusError(adr, data);
	}
}

void cpu_writemem24_word(uint32_t adr, uint32_t data)
{
	if (adr & 1)
	{
		AdrError(adr, data);
		return;
	}

	BusErrFlag = 0;

	wm_main_b(adr, (uint8_t)(data >> 8));
	if ((BusErrFlag & 7) == 0)
	{
		wm_main_b(adr + 1, (uint8_t)data);
	}

	if (BusErrFlag & 2)
	{
		BusError(adr, data);
	}
}

static void wm_main_b(uint32_t adr, uint8_t data)
{
	int index;

	adr &= 0x00ffffff;

	switch ((adr >> 20) & 0x0f)
	{
	case 0x00: case 0x01: case 0x02: case 0x03:
	case 0x04: case 0x05: case 0x06: case 0x07:
	case 0x08: case 0x09: case 0x0a: case 0x0b:
		if (adr < system_ram)
		{
			MEM[adr ^ 1] = data;
		} else {
			wm_buserr(adr, data);
		}
		break;

	case 0x0c:
	case 0x0d:
		GVRAM_Write(adr, data);
		break;

	case 0x0e:
		index = (adr >> 13) & 0x7f;
		MemWriteTable[index](adr, data);
		break;

	case 0x0f:
		break;
	}
}

static void wm_main_w(uint32_t adr, uint16_t data)
{
	int index;
	uint16_t *ptr;

	adr &= 0x00fffffe;

	switch ((adr >> 20) & 0x0f)
	{
	case 0x00: case 0x01: case 0x02: case 0x03:
	case 0x04: case 0x05: case 0x06: case 0x07:
	case 0x08: case 0x09: case 0x0a: case 0x0b:
		if (adr < system_ram)
		{
			ptr = (uint16_t *)&MEM[adr];
			*ptr = (uint16_t)data;
		} else {
			wm_buserr(adr, (uint8_t)(data >> 8));
			wm_buserr(adr + 1, (uint8_t)data);
		}
		break;

	case 0x0c:
	case 0x0d:
		GVRAM_Write(adr, (uint8_t)(data >> 8));
		GVRAM_Write(adr + 1, (uint8_t)data);
		break;

	case 0x0e:
		index = (adr >> 13) & 0x7f;
		MemWriteTable[index](adr, (uint8_t)(data >> 8));
		MemWriteTable[index](adr + 1, (uint8_t)data);
		break;

	case 0x0f:
		break;
	}
}

static void wm_buserr(uint32_t adr, uint8_t data)
{
	BusErrFlag = 2;
	BusErrAdr  = adr;
	(void)data;
}

static void wm_nop(uint32_t adr, uint8_t data)
{
	/* Nothing to do */
	(void)adr;
	(void)data;
}

/*
 * read function
 */
uint8_t dma_readmem24(uint32_t adr)
{
	return rm_main_b(adr);
}

uint16_t dma_readmem24_word(uint32_t adr)
{
	uint16_t v;

	if (adr & 1)
	{
		BusErrFlag = 3;
		return 0;
	}

	v = rm_main_w(adr);
	return v;
}

uint32_t cpu_readmem24(uint32_t adr)
{
	uint32_t v;

	v = (uint32_t)rm_main_b(adr);

	if (BusErrFlag & 1)
	{
		p6logd("cpu_readmem24 adr = %x flag = %d\n", adr, BusErrFlag);
		BusError(adr, 0);
	}

	return v;
}

uint32_t cpu_readmem24_word(uint32_t adr)
{
	uint32_t v;

	if (adr & 1)
	{
		AdrError(adr, 0);
		return 0;
	}

	BusErrFlag = 0;

	v = (uint32_t)rm_main_w(adr);

	if (BusErrFlag & 1)
	{
		p6logd("cpu_readmem24_word adr = %x flag = %d\n", adr, BusErrFlag);
		BusError(adr, 0);
	}

	return v;
}

static uint8_t rm_main_b(uint32_t adr)
{
	int index;

	adr &= 0x00ffffff;

	switch ((adr >> 20) & 0x0f)
	{
	case 0x00: case 0x01: case 0x02: case 0x03:
	case 0x04: case 0x05: case 0x06: case 0x07:
	case 0x08: case 0x09: case 0x0a: case 0x0b:
		if (adr < system_ram)
		{
			return MEM[adr ^ 1];
		}
		return rm_buserr(adr);

	case 0x0c:
	case 0x0d:
		return GVRAM_Read(adr);

	case 0x0e:
		if ((adr >= 0xea0020) && (adr <= 0xea1fff))
		{
			adr &= 0x1fff;
			adr ^= 1;
			return SCSIIPL[adr];
		}
		index = (adr >> 13) & 0x7f;
		return MemReadTable[index](adr);

	case 0x0f:
		if (adr >= 0xfc0000)
		{
			adr &= 0x3ffff;
			adr ^= 1;
			return IPL[adr];
		}
		adr &= 0xfffff;
		adr ^= 1;
		return FONT[adr];
	}

	return rm_buserr(adr);
}

static uint16_t rm_main_w(uint32_t adr)
{
	int index;
	uint16_t v;
	uint16_t *ptr;

	adr &= 0x00fffffe;

	switch ((adr >> 20) & 0x0f)
	{
	case 0x00: case 0x01: case 0x02: case 0x03:
	case 0x04: case 0x05: case 0x06: case 0x07:
	case 0x08: case 0x09: case 0x0a: case 0x0b:
		if (adr < system_ram)
		{
			ptr = (uint16_t *)&MEM[adr];
			return (uint16_t)*ptr;
		}
		return rm_buserr(adr);

	case 0x0c:
	case 0x0d:
		v = GVRAM_Read(adr) << 8;
		v |= GVRAM_Read(adr + 1);
		return v;

	case 0x0e:
		if ((adr >= 0xea0020) && (adr <= 0xea1fff))
		{
			adr &= 0x1fff;
			ptr = (uint16_t *)&SCSIIPL[adr];
			return (uint16_t)*ptr;
		}
		index = (adr >> 13) & 0x7f;
		v = MemReadTable[index](adr) << 8;
		v |= MemReadTable[index](adr + 1);
		return v;

	case 0x0f:
		if (adr >= 0xfc0000)
		{
			adr &= 0x3ffff;
			ptr = (uint16_t *)&IPL[adr];
			return (uint16_t)*ptr;
		}
		adr &= 0xfffff;
		ptr = (uint16_t *)&FONT[adr];
		return (uint16_t)*ptr;
	}

	return (0xff | rm_buserr(adr));
}

static uint8_t rm_font(uint32_t adr)
{
	return FONT[(adr & 0xfffff) ^ 1];
}

static uint8_t rm_ipl(uint32_t adr)
{
	return IPL[(adr & 0x3ffff) ^ 1];
}

static uint8_t rm_nop(uint32_t adr)
{
	(void)adr;
	return 0;
}

static uint8_t rm_buserr(uint32_t adr)
{
	p6logd("func = %s adr = %x flag = %d\n", "rm_buserr", adr, BusErrFlag);

	BusErrFlag = 1;
	BusErrAdr  = adr;

	return 0xff;
}

static void cpu_setOPbase24(uint32_t adr)
{
	switch ((adr >> 20) & 0xf)
	{
	case 0: case 1: case 2: case 3:
	case 4: case 5: case 6: case 7:
	case 8: case 9: case 0xa: case 0xb:
		OP_ROM = MEM;
		break;

	case 0xc:
	case 0xd:
		OP_ROM = GVRAM + (adr - 0x00c00000);
		break;

	case 0xe:
		if (adr < 0x00e80000)
			OP_ROM = TVRAM + (adr - 0x00e00000);
		else if ((adr >= 0x00ea0000) && (adr < 0x00ea2000))
			OP_ROM = SCSIIPL + (adr - 0x00ea0000);
		else if ((adr >= 0x00ed0000) && (adr < 0x00ed4000))
			OP_ROM = SRAM + (adr - 0x00ed0000);
		else
		{
			BusErrFlag = 3;
			BusErrAdr  = adr;
			BusError(adr, 0);
		}
		break;

	case 0xf:
		if ((adr >= 0x00fc0000) && (adr < 0x01000000))
			OP_ROM = IPL + (adr - 0x00fc0000);
		else
		{
			BusErrFlag = 3;
			BusErrAdr  = adr;
			BusError(adr, 0);
		}
		break;
	}
}

/*
 * Memory misc
 */
void Memory_Init(void)
{
	cpu_setOPbase24(M68K->GetPC());
	SRAM_SetRAMSize(Config.ramSize);
	system_ram = Config.ramSize * 0x100000;
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

#if defined(HAVE_MUSASHI)
void m68k_pulse_bus_error(void);
#endif

static void BusError(uint32_t adr, uint32_t unknown)
{
	(void)adr;
	(void)unknown;
	p6logd("BusError: %x\n", adr);
#if defined(HAVE_MUSASHI)
	m68k_pulse_bus_error();
#else
	BusErrHandling = 1;
#endif
}
