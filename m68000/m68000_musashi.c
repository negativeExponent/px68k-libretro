#include "../x11/common.h"
#include "../x11/state.h"

#include "musashi/m68k.h"
#include "musashi/m68kcpu.h"

#include "m68000_musashi.h"

/* musashi read/write functions */

static M68K_READ *read_byte;
static M68K_READ *read_word;
static M68K_WRITE *write_byte;
static M68K_WRITE *write_word;

uint32_t m68k_read_memory_8(uint32_t address)
{
	return read_byte(address);
}

uint32_t m68k_read_memory_16(uint32_t address)
{
	return read_word(address);
}

uint32_t m68k_read_memory_32(uint32_t address)
{
	return ((read_word(address) & 0xffff) << 16) | (read_word(address + 2) & 0xffff);
}

void m68k_write_memory_8(uint32_t address, uint32_t data)
{
	write_byte(address, data);
}

void m68k_write_memory_16(uint32_t address, uint32_t data)
{
	write_word(address, data);
}

void m68k_write_memory_32(uint32_t address, uint32_t data)
{
	write_word(address, (data >> 16) & 0xffff);
	write_word(address + 2, data & 0xffff);
}

/* M68K Interface */

static void M68000MusashiInit(void)
{
	m68k_init();
	m68k_set_reset_instr_callback(m68k_pulse_reset);
	m68k_set_cpu_type(M68K_CPU_TYPE_68000);
}

static void M68000MusashiClose(void) { }

static void M68000MusashiReset(void)
{
	m68k_pulse_reset();
}

static int32_t FASTCALL M68000MusashiExec(int32_t cycle)
{
	return m68k_execute(cycle);
}

static uint32_t M68000MusashiGetDReg(uint32_t num)
{
	return m68k_get_reg(NULL, M68K_REG_D0 + num);
}

static uint32_t M68000MusashiGetAReg(uint32_t num)
{
	return m68k_get_reg(NULL, M68K_REG_A0 + num);
}

static uint32_t M68000MusashiGetPC(void)
{
	return m68k_get_reg(NULL, M68K_REG_PC);
}

static uint32_t M68000MusashiGetSR(void)
{
	return m68k_get_reg(NULL, M68K_REG_SR);
}

static uint32_t M68000MusashiGetUSP(void)
{
	return m68k_get_reg(NULL, M68K_REG_USP);
}

static uint32_t M68000MusashiGetMSP(void)
{
	return m68k_get_reg(NULL, M68K_REG_MSP);
}

static void M68000MusashiSetDReg(uint32_t num, uint32_t val)
{
	m68k_set_reg(M68K_REG_D0 + num, val);
}

static void M68000MusashiSetAReg(uint32_t num, uint32_t val)
{
	m68k_set_reg(M68K_REG_A0 + num, val);
}

static void M68000MusashiSetPC(uint32_t val)
{
	m68k_set_reg(M68K_REG_PC, val);
}

static void M68000MusashiSetSR(uint32_t val)
{
	m68k_set_reg(M68K_REG_SR, val);
}

static void M68000MusashiSetUSP(uint32_t val)
{
	m68k_set_reg(M68K_REG_USP, val);
}

static void M68000MusashiSetMSP(uint32_t val)
{
	m68k_set_reg(M68K_REG_MSP, val);
}

static void M68000MusashiSetFetch(uint32_t low_adr, uint32_t high_adr, uintptr_t fetch_adr)
{
}

static void FASTCALL M68000MusashiSetIRQ(int32_t level)
{
	m68k_set_irq(level);
}

static void M68000MusashiSetReadB(M68K_READ *Func)
{
	read_byte = Func;
}

static void M68000MusashiSetReadW(M68K_READ *Func)
{
	read_word = Func;
}

static void M68000MusashiSetWriteB(M68K_WRITE *Func)
{
	write_byte = Func;
}

static void M68000MusashiSetWriteW(M68K_WRITE *Func)
{
	write_word = Func;
}

static int M68000MusashiStateContext(void *f, int writing)
{
	if (!writing)
	{
		uint32_t tmp32;
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D0, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D1, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D2, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D3, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D4, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D5, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D6, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_D7, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A0, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A1, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A2, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A3, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A4, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A5, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A6, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_A7, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_PC, tmp32);
		state_context_f(&tmp32, 2); m68k_set_reg(M68K_REG_SR, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_USP, tmp32);
		state_context_f(&tmp32, 4); m68k_set_reg(M68K_REG_ISP, tmp32);

		state_context_f(&m68ki_remaining_cycles, sizeof(m68ki_remaining_cycles));
		state_context_f(&m68ki_cpu.int_level, sizeof(m68ki_cpu.int_level));
		state_context_f(&m68ki_cpu.stopped, sizeof(m68ki_cpu.stopped));
	}
	else
	{
		uint32_t tmp32;
		tmp32 = m68k_get_reg(NULL, M68K_REG_D0); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_D1); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_D2); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_D3); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_D4); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_D5); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_D6); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_D7); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A0); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A1); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A2); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A3); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A4); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A5); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A6); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_A7); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_PC); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_SR); state_context_f(&tmp32, 2);
		tmp32 = m68k_get_reg(NULL, M68K_REG_USP); state_context_f(&tmp32, 4);
		tmp32 = m68k_get_reg(NULL, M68K_REG_ISP); state_context_f(&tmp32, 4);

		state_context_f(&m68ki_remaining_cycles, sizeof(m68ki_remaining_cycles));
		state_context_f(&m68ki_cpu.int_level, sizeof(m68ki_cpu.int_level));
		state_context_f(&m68ki_cpu.stopped, sizeof(m68ki_cpu.stopped));
	}

	return 1;
}

M68K_struct m68000_musashi = {
	.Init         = M68000MusashiInit,
	.Close        = M68000MusashiClose,
	.Reset        = M68000MusashiReset,
	.SetFetch     = M68000MusashiSetFetch,
	.SetReadB     = M68000MusashiSetReadB,
	.SetReadW     = M68000MusashiSetReadW,
	.SetWriteB    = M68000MusashiSetWriteB,
	.SetWriteW    = M68000MusashiSetWriteW,
	.Exec         = M68000MusashiExec,
	.SetIRQ       = M68000MusashiSetIRQ,
	.GetDReg      = M68000MusashiGetDReg,
	.GetAReg      = M68000MusashiGetAReg,
	.GetPC        = M68000MusashiGetPC,
	.GetSR        = M68000MusashiGetSR,
	.GetUSP       = M68000MusashiGetUSP,
	.GetMSP       = M68000MusashiGetMSP,
	.SetDReg      = M68000MusashiSetDReg,
	.SetAReg      = M68000MusashiSetAReg,
	.SetPC        = M68000MusashiSetPC,
	.SetSR        = M68000MusashiSetSR,
	.SetUSP       = M68000MusashiSetUSP,
	.SetMSP       = M68000MusashiSetMSP,
	.StateContext = M68000MusashiStateContext,
};
