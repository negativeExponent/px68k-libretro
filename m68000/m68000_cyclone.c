#include "../x11/common.h"
#include "../x11/state.h"
#include "../x68k/x68kmemory.h"

#include "m68000_cyclone.h"
#include "cyclone.h"

/* cyclone implementation untested. just moved it here for safe-keeping */

/* cylone read/write functions */

unsigned int read8(unsigned int a) {
	return (unsigned int) cpu_readmem24(a);
}

unsigned int read16(unsigned int a) {
	return (unsigned int) cpu_readmem24_word(a);
}

unsigned int read32(unsigned int a) {
	return (unsigned int) (
		((unsigned short)cpu_readmem24_word(a) << 16) |
		((unsigned short)cpu_readmem24_word(a + 2)));
}

void write8(unsigned int a, unsigned char d) {
	cpu_write24(a, d);
}

void write8(unsigned int a, unsigned short d) {
	cpu_write24_word(a, d);
}

void write8(unsigned int a, unsigned int d) {
	cpu_write24(a, (d >> 16) & 0xffff);
	cpu_write24(a + 2, d & 0xffff);
	
}

unsigned int MyCheckPc(unsigned int pc)
{
	pc -= m68k.membase; /* Get the real program counter */

	if (pc <= 0xbfffff)
	{
		m68k.membase = (int)MEM;
		return m68k.membase + pc;
	}
	if ((pc >= 0xfc0000) && (pc <= 0xffffff))
	{
		m68k.membase = (int)IPL - 0xfc0000;
		return m68k.membase + pc;
	}
	if ((pc >= 0xc00000) && (pc <= 0xc7ffff))
		m68k.membase = (int)GVRAM - 0xc00000;
	if ((pc >= 0xe00000) && (pc <= 0xe7ffff))
		m68k.membase = (int)TVRAM - 0xe00000;
	if ((pc >= 0xea0000) && (pc <= 0xea1fff))
		m68k.membase = (int)SCSIIPL - 0xea0000;
	if ((pc >= 0xed0000) && (pc <= 0xed3fff))
		m68k.membase = (int)SRAM - 0xed0000;
	if ((pc >= 0xf00000) && (pc <= 0xfbffff))
		m68k.membase = (int)FONT - 0xf00000;

	return m68k.membase + pc; /* New program counter */
}

/* M68K Interface */

static void M68000CycloneInit(void)
{
	m68k.read8  = read8;
	m68k.read16 = read16;
	m68k.read32 = read32;

	m68k.fetch8  = read8;
	m68k.fetch16 = read16;
	m68k.fetch32 = read32;

	m68k.write8  = write8;
	m68k.write16 = write16;
	m68k.write32 = write32;

	m68k.checkpc = MyCheckPc;
	m68k.IrqCallback = my_irqh_callback;
	CycloneInit();
}

static void M68000CycloneClose(void) { }

static void M68000CycloneReset(void)
{
	CycloneReset(&m68k);
	m68k.state_flags = 0; /* Go to default state (not stopped, halted, etc.) */
	m68k.srh = 0x27; /* Set supervisor mode */
}

static int32_t FASTCALL M68000CycloneExec(int32_t cycle)
{
	m68k.cycles = cycle;
	CycloneRun(&m68k);
	return m68k.cycles;
}

static uint32_t M68000CycloneGetDReg(uint32_t num)
{
	return m68k.d[num];
}

static uint32_t M68000CycloneGetAReg(uint32_t num)
{
	return m68k.a[num];
}

static uint32_t M68000CycloneGetPC(void)
{
	return m68k.pc - m68k.membase;
}

static uint32_t M68000CycloneGetSR(void)
{
	return CycloneGetSr(&m68k);
}

static uint32_t M68000CycloneGetUSP(void)
{
	return 0;
}

static uint32_t M68000CycloneGetMSP(void)
{
	return 0
}

static void M68000CycloneSetDReg(uint32_t num, uint32_t val)
{
	m68k.d[0] = val;
}

static void M68000CycloneSetAReg(uint32_t num, uint32_t val)
{
	m68k.a[0] = val;
}

static void M68000CycloneSetPC(uint32_t val)
{
	m68k.pc = m68k.checkpc(val+m68k.membase);
}

static void M68000CycloneSetSR(uint32_t val)
{
	CycloneSetSr(&m68k, val);
}

static void M68000CycloneSetUSP(uint32_t val)
{
}

static void M68000CycloneSetMSP(uint32_t val)
{
}

static void M68000CycloneSetFetch(uint32_t low_adr, uint32_t high_adr, uintptr_t fetch_adr)
{
}

static void FASTCALL M68000CycloneSetIRQ(int32_t level)
{
	m68k.irq = level;
}

static void M68000CycloneSetReadB(M68K_READ *Func)
{
}

static void M68000CycloneSetReadW(M68K_READ *Func)
{
}

static void M68000CycloneSetWriteB(M68K_WRITE *Func)
{
}

static void M68000CycloneSetWriteW(M68K_WRITE *Func)
{
}

static int M68000CycloneStateContext(void *f, int writing)
{
	return 1;
}

M68K_struct m68000_Cyclone = {
	.Init         = M68000CycloneInit,
	.Close        = M68000CycloneClose,
	.Reset        = M68000CycloneReset,
	.SetFetch     = M68000CycloneSetFetch,
	.SetReadB     = M68000CycloneSetReadB,
	.SetReadW     = M68000CycloneSetReadW,
	.SetWriteB    = M68000CycloneSetWriteB,
	.SetWriteW    = M68000CycloneSetWriteW,
	.Exec         = M68000CycloneExec,
	.SetIRQ       = M68000CycloneSetIRQ,
	.GetDReg      = M68000CycloneGetDReg,
	.GetAReg      = M68000CycloneGetAReg,
	.GetPC        = M68000CycloneGetPC,
	.GetSR        = M68000CycloneGetSR,
	.GetUSP       = M68000CycloneGetUSP,
	.GetMSP       = M68000CycloneGetMSP,
	.SetDReg      = M68000CycloneSetDReg,
	.SetAReg      = M68000CycloneSetAReg,
	.SetPC        = M68000CycloneSetPC,
	.SetSR        = M68000CycloneSetSR,
	.SetUSP       = M68000CycloneSetUSP,
	.SetMSP       = M68000CycloneSetMSP,
	.StateContext = M68000CycloneStateContext,
};
