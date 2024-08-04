#include "../x11/common.h"
#include "../x11/state.h"

#include "c68k/c68k.h"
#include "m68000_c68k.h"

static void M68000C68KInit(void)
{
	C68k_Init(&C68K, my_irqh_callback);
}

static void M68000C68KClose(void) { }

static void M68000C68KReset(void)
{
	C68k_Reset(&C68K);
}

static int32_t FASTCALL M68000C68KExec(int32_t cycle)
{
	return C68k_Exec(&C68K, cycle);
}

static uint32_t M68000C68KGetDReg(uint32_t num)
{
	return C68k_Get_DReg(&C68K, num);
}

static uint32_t M68000C68KGetAReg(uint32_t num)
{
	return C68k_Get_AReg(&C68K, num);
}

static uint32_t M68000C68KGetPC(void)
{
	return C68k_Get_PC(&C68K);
}

static uint32_t M68000C68KGetSR(void)
{
	return C68k_Get_SR(&C68K);
}

static uint32_t M68000C68KGetUSP(void)
{
	return C68k_Get_USP(&C68K);
}

static uint32_t M68000C68KGetMSP(void)
{
	return C68k_Get_MSP(&C68K);
}

static void M68000C68KSetDReg(uint32_t num, uint32_t val)
{
	C68k_Set_DReg(&C68K, num, val);
}

static void M68000C68KSetAReg(uint32_t num, uint32_t val)
{
	C68k_Set_AReg(&C68K, num, val);
}

static void M68000C68KSetPC(uint32_t val)
{
	C68k_Set_PC(&C68K, val);
}

static void M68000C68KSetSR(uint32_t val)
{
	C68k_Set_SR(&C68K, val);
}

static void M68000C68KSetUSP(uint32_t val)
{
	C68k_Set_USP(&C68K, val);
}

static void M68000C68KSetMSP(uint32_t val)
{
	C68k_Set_MSP(&C68K, val);
}

static void M68000C68KSetFetch(uint32_t low_adr, uint32_t high_adr, uintptr_t fetch_adr)
{
	C68k_Set_Fetch(&C68K, low_adr, high_adr, fetch_adr);
}

static void FASTCALL M68000C68KSetIRQ(int32_t level)
{
	C68k_Set_IRQ(&C68K, level);
}

static void M68000C68KSetReadB(M68K_READ *Func)
{
	C68k_Set_ReadB(&C68K, Func);
}

static void M68000C68KSetReadW(M68K_READ *Func)
{
	C68k_Set_ReadW(&C68K, Func);
}

static void M68000C68KSetWriteB(M68K_WRITE *Func)
{
	C68k_Set_WriteB(&C68K, Func);
}

static void M68000C68KSetWriteW(M68K_WRITE *Func)
{
	C68k_Set_WriteW(&C68K, Func);
}

static int M68000C68KStateContext(void *f, int writing)
{
	uint32_t pc = 0;
	int i;

	if (writing)
	{
		pc = C68k_Get_PC(&C68K);
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
		C68k_Set_PC(&C68K, pc);
	}

	state_context_f((void *)&C68K.Status, sizeof(uint32_t));
	state_context_f((void *)&C68K.IRQLine, sizeof(int32_t));

	state_context_f((void *)&C68K.CycleToDo, sizeof(int32_t));
	state_context_f((void *)&C68K.CycleIO, sizeof(int32_t));
	state_context_f((void *)&C68K.CycleSup, sizeof(int32_t));
	state_context_f((void *)&C68K.dirty1, sizeof(uint32_t));

	return 1;
}

M68K_struct m68000_c68k = {
	.Init         = M68000C68KInit,
	.Close        = M68000C68KClose,
	.Reset        = M68000C68KReset,
	.SetFetch     = M68000C68KSetFetch,
	.SetReadB     = M68000C68KSetReadB,
	.SetReadW     = M68000C68KSetReadW,
	.SetWriteB    = M68000C68KSetWriteB,
	.SetWriteW    = M68000C68KSetWriteW,
	.Exec         = M68000C68KExec,
	.SetIRQ       = M68000C68KSetIRQ,
	.GetDReg      = M68000C68KGetDReg,
	.GetAReg      = M68000C68KGetAReg,
	.GetPC        = M68000C68KGetPC,
	.GetSR        = M68000C68KGetSR,
	.GetUSP       = M68000C68KGetUSP,
	.GetMSP       = M68000C68KGetMSP,
	.SetDReg      = M68000C68KSetDReg,
	.SetAReg      = M68000C68KSetAReg,
	.SetPC        = M68000C68KSetPC,
	.SetSR        = M68000C68KSetSR,
	.SetUSP       = M68000C68KSetUSP,
	.SetMSP       = M68000C68KSetMSP,
	.StateContext = M68000C68KStateContext,
};
