#include "../x11/common.h"
#include "../x11/state.h"

#include "m68k/c68k.h"
#include "m68000_m68k.h"

static void M68000M68KInit(void)
{
	C68k_Init(&C68K, my_irqh_callback);
}

static void M68000M68KClose(void) { }

static void M68000M68KReset(void)
{
	C68k_Reset(&C68K);
}

static int32_t FASTCALL M68000M68KExec(int32_t cycle)
{
	return C68k_Exec(&C68K, cycle);
}

static uint32_t M68000M68KGetDReg(uint32_t num)
{
	return C68k_Get_Reg(&C68K, C68K_D0 + num);
}

static uint32_t M68000M68KGetAReg(uint32_t num)
{
	return C68k_Get_Reg(&C68K, C68K_A0 + num);
}

static uint32_t M68000M68KGetPC(void)
{
	return C68k_Get_Reg(&C68K, C68K_PC);
}

static uint32_t M68000M68KGetSR(void)
{
	return C68k_Get_Reg(&C68K, C68K_SR);
}

static uint32_t M68000M68KGetUSP(void)
{
	return C68k_Get_Reg(&C68K, C68K_USP);
}

static uint32_t M68000M68KGetMSP(void)
{
	return C68k_Get_Reg(&C68K, C68K_MSP);
}

static void M68000M68KSetDReg(uint32_t num, uint32_t val)
{
	C68k_Set_Reg(&C68K, C68K_D0 + num, val);
}

static void M68000M68KSetAReg(uint32_t num, uint32_t val)
{
	C68k_Set_Reg(&C68K, C68K_A0 + num, val);
}

static void M68000M68KSetPC(uint32_t val)
{
	C68k_Set_Reg(&C68K, C68K_PC, val);
}

static void M68000M68KSetSR(uint32_t val)
{
	C68k_Set_Reg(&C68K, C68K_SR, val);
}

static void M68000M68KSetUSP(uint32_t val)
{
	C68k_Set_Reg(&C68K, C68K_USP, val);
}

static void M68000M68KSetMSP(uint32_t val)
{
	C68k_Set_Reg(&C68K, C68K_MSP, val);
}

static void M68000M68KSetFetch(uint32_t low_adr, uint32_t high_adr, uintptr_t fetch_adr)
{
	C68k_Set_Fetch(&C68K, low_adr, high_adr, fetch_adr);
}

static void FASTCALL M68000M68KSetIRQ(int32_t level)
{
	int32_t state = (level <= 0) ? CLEAR_LINE : HOLD_LINE;
	C68k_Set_IRQ(&C68K, level, state);
}

static void M68000M68KSetReadB(M68K_READ *Func)
{
	C68k_Set_ReadB(&C68K, Func);
}

static void M68000M68KSetReadW(M68K_READ *Func)
{
	C68k_Set_ReadW(&C68K, Func);
}

static void M68000M68KSetWriteB(M68K_WRITE *Func)
{
	C68k_Set_WriteB(&C68K, Func);
}

static void M68000M68KSetWriteW(M68K_WRITE *Func)
{
	C68k_Set_WriteW(&C68K, Func);
}

static int M68000M68KStateContext(void *f, int writing)
{
	uint32_t pc = 0;
	int i;

	if (writing)
	{
		pc = C68k_Get_Reg(&C68K, C68K_PC);
	}

	for (i = 0; i < 8; i++)
		state_context_f((void *)&C68K.D[i], sizeof(uint32_t));

	for (i = 0; i < 8; i++)
		state_context_f((void *)&C68K.A[i], sizeof(uint32_t));

	state_context_f((void *)&C68K.flag_C, sizeof(uint32_t));
	state_context_f((void *)&C68K.flag_V, sizeof(uint32_t));
	state_context_f((void *)&C68K.flag_notZ, sizeof(uint32_t));
	state_context_f((void *)&C68K.flag_N, sizeof(uint32_t));

	state_context_f((void *)&C68K.flag_X, sizeof(uint32_t));
	state_context_f((void *)&C68K.flag_I, sizeof(uint32_t));
	state_context_f((void *)&C68K.flag_S, sizeof(uint32_t));

	state_context_f((void *)&C68K.USP, sizeof(uint32_t));

	state_context_f((void *)&pc, sizeof(uint32_t));

	if (!writing)
	{
		C68k_Set_Reg(&C68K, C68K_PC, pc);
	}

	state_context_f((void *)&C68K.HaltState, sizeof(uint32_t));
	state_context_f((void *)&C68K.IRQLine, sizeof(int32_t));
	state_context_f((void *)&C68K.IRQState, sizeof(int32_t));
	state_context_f((void *)&C68K.ICount, sizeof(int32_t));
	state_context_f((void *)&C68K.ICountBk, sizeof(int32_t));

	return 1;
}

M68K_struct m68000_m68k = {
	.Init         = M68000M68KInit,
	.Close        = M68000M68KClose,
	.Reset        = M68000M68KReset,
	.SetFetch     = M68000M68KSetFetch,
	.SetReadB     = M68000M68KSetReadB,
	.SetReadW     = M68000M68KSetReadW,
	.SetWriteB    = M68000M68KSetWriteB,
	.SetWriteW    = M68000M68KSetWriteW,
	.Exec         = M68000M68KExec,
	.SetIRQ       = M68000M68KSetIRQ,
	.GetDReg      = M68000M68KGetDReg,
	.GetAReg      = M68000M68KGetAReg,
	.GetPC        = M68000M68KGetPC,
	.GetSR        = M68000M68KGetSR,
	.GetUSP       = M68000M68KGetUSP,
	.GetMSP       = M68000M68KGetMSP,
	.SetDReg      = M68000M68KSetDReg,
	.SetAReg      = M68000M68KSetAReg,
	.SetPC        = M68000M68KSetPC,
	.SetSR        = M68000M68KSetSR,
	.SetUSP       = M68000M68KSetUSP,
	.SetMSP       = M68000M68KSetMSP,
	.StateContext = M68000M68KStateContext,
};
