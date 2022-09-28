
/* MOVEQ */
OP_0x7000:
{
	uint32_t res;
	res = (int32_t)(int8_t)Opcode;
	CPU->flag_C = CPU->flag_V = 0;
	CPU->flag_N = CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)
