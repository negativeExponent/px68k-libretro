
/* 1010 */
OP_0xA000:
{
	uint32_t res;
	PC -= 2;
	if (!CPU->flag_S)
	{
		res = CPU->USP;
		CPU->USP = CPU->A[7];
		CPU->A[7] = res;
	}
	res = C68K_1010_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	PUSH_16_F(GET_SR)
	CPU->flag_S = C68K_SR_S;
	READ_LONG_F(res * 4, PC)
	SET_PC(PC)
	POST_IO
}
RET(4)
