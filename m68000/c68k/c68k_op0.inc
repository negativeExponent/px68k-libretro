
/* ORI */
OP_0x0000:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ORI */
OP_0x0010:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ORI */
OP_0x0018:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ORI */
OP_0x0020:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ORI */
OP_0x0028:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* ORI */
OP_0x0030:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* ORI */
OP_0x0038:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* ORI */
OP_0x0039:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* ORI */
OP_0x001F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ORI */
OP_0x0027:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ORI */
OP_0x0040:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ORI */
OP_0x0050:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ORI */
OP_0x0058:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ORI */
OP_0x0060:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ORI */
OP_0x0068:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ORI */
OP_0x0070:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* ORI */
OP_0x0078:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ORI */
OP_0x0079:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* ORI */
OP_0x005F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ORI */
OP_0x0067:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ORI */
OP_0x0080:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(16)

/* ORI */
OP_0x0090:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ORI */
OP_0x0098:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ORI */
OP_0x00A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ORI */
OP_0x00A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* ORI */
OP_0x00B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* ORI */
OP_0x00B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* ORI */
OP_0x00B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(36)

/* ORI */
OP_0x009F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ORI */
OP_0x00A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ORICCR */
OP_0x003C:
{
	uint32_t res;
	res = FETCH_BYTE & C68K_CCR_MASK;
	PC += 2;
	res |= GET_CCR;
	SET_CCR(res)
}
RET(20)

/* ORISR */
OP_0x007C:
{
	uint32_t res;
	if (CPU->flag_S)
	{
		res = FETCH_WORD & C68K_SR_MASK;
		PC += 2;
		res |= GET_SR;
		SET_SR(res)
	}
	else
	{
		res = CPU->USP;
		CPU->USP = CPU->A[7];
		CPU->A[7] = res;
		res = C68K_PRIVILEGE_VIOLATION_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
}
POST_IO
CCnt -= 20;
goto C68k_Exec_End;

/* ANDI */
OP_0x0200:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ANDI */
OP_0x0210:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ANDI */
OP_0x0218:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ANDI */
OP_0x0220:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ANDI */
OP_0x0228:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* ANDI */
OP_0x0230:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* ANDI */
OP_0x0238:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* ANDI */
OP_0x0239:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* ANDI */
OP_0x021F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ANDI */
OP_0x0227:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ANDI */
OP_0x0240:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ANDI */
OP_0x0250:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ANDI */
OP_0x0258:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ANDI */
OP_0x0260:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ANDI */
OP_0x0268:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ANDI */
OP_0x0270:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* ANDI */
OP_0x0278:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ANDI */
OP_0x0279:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* ANDI */
OP_0x025F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ANDI */
OP_0x0267:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ANDI */
OP_0x0280:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(16)

/* ANDI */
OP_0x0290:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ANDI */
OP_0x0298:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ANDI */
OP_0x02A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ANDI */
OP_0x02A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* ANDI */
OP_0x02B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* ANDI */
OP_0x02B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* ANDI */
OP_0x02B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(36)

/* ANDI */
OP_0x029F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ANDI */
OP_0x02A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ANDICCR */
OP_0x023C:
{
	uint32_t res;
	res = FETCH_BYTE & C68K_CCR_MASK;
	PC += 2;
	res &= GET_CCR;
	SET_CCR(res)
}
RET(20)

/* ANDISR */
OP_0x027C:
{
	uint32_t res;
	if (CPU->flag_S)
	{
		res = FETCH_WORD & C68K_SR_MASK;
		PC += 2;
		res &= GET_SR;
		SET_SR(res)
		if (!CPU->flag_S)
		{
			res = CPU->A[7];
			CPU->A[7] = CPU->USP;
			CPU->USP = res;
		}
	}
	else
	{
		res = CPU->USP;
		CPU->USP = CPU->A[7];
		CPU->A[7] = res;
		res = C68K_PRIVILEGE_VIOLATION_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
}
POST_IO
CCnt -= 20;
goto C68k_Exec_End;

/* EORI */
OP_0x0A00:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* EORI */
OP_0x0A10:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* EORI */
OP_0x0A18:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* EORI */
OP_0x0A20:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* EORI */
OP_0x0A28:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* EORI */
OP_0x0A30:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* EORI */
OP_0x0A38:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* EORI */
OP_0x0A39:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* EORI */
OP_0x0A1F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* EORI */
OP_0x0A27:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* EORI */
OP_0x0A40:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* EORI */
OP_0x0A50:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* EORI */
OP_0x0A58:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* EORI */
OP_0x0A60:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* EORI */
OP_0x0A68:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* EORI */
OP_0x0A70:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* EORI */
OP_0x0A78:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* EORI */
OP_0x0A79:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* EORI */
OP_0x0A5F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* EORI */
OP_0x0A67:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* EORI */
OP_0x0A80:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(16)

/* EORI */
OP_0x0A90:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* EORI */
OP_0x0A98:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* EORI */
OP_0x0AA0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* EORI */
OP_0x0AA8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* EORI */
OP_0x0AB0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* EORI */
OP_0x0AB8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* EORI */
OP_0x0AB9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(36)

/* EORI */
OP_0x0A9F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* EORI */
OP_0x0AA7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* EORICCR */
OP_0x0A3C:
{
	uint32_t res;
	res = FETCH_BYTE & C68K_CCR_MASK;
	PC += 2;
	res ^= GET_CCR;
	SET_CCR(res)
}
RET(20)

/* EORISR */
OP_0x0A7C:
{
	uint32_t res;
	if (CPU->flag_S)
	{
		res = FETCH_WORD & C68K_SR_MASK;
		PC += 2;
		res ^= GET_SR;
		SET_SR(res)
		if (!CPU->flag_S)
		{
			res = CPU->A[7];
			CPU->A[7] = CPU->USP;
			CPU->USP = res;
		}
	}
	else
	{
		res = CPU->USP;
		CPU->USP = CPU->A[7];
		CPU->A[7] = res;
		res = C68K_PRIVILEGE_VIOLATION_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
}
POST_IO
CCnt -= 20;
goto C68k_Exec_End;

/* SUBI */
OP_0x0400:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	dst = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* SUBI */
OP_0x0410:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* SUBI */
OP_0x0418:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* SUBI */
OP_0x0420:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SUBI */
OP_0x0428:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* SUBI */
OP_0x0430:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* SUBI */
OP_0x0438:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* SUBI */
OP_0x0439:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* SUBI */
OP_0x041F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* SUBI */
OP_0x0427:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SUBI */
OP_0x0440:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	dst = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* SUBI */
OP_0x0450:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* SUBI */
OP_0x0458:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* SUBI */
OP_0x0460:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* SUBI */
OP_0x0468:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* SUBI */
OP_0x0470:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* SUBI */
OP_0x0478:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* SUBI */
OP_0x0479:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* SUBI */
OP_0x045F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* SUBI */
OP_0x0467:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* SUBI */
OP_0x0480:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(16)

/* SUBI */
OP_0x0490:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* SUBI */
OP_0x0498:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* SUBI */
OP_0x04A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* SUBI */
OP_0x04A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* SUBI */
OP_0x04B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* SUBI */
OP_0x04B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* SUBI */
OP_0x04B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(36)

/* SUBI */
OP_0x049F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* SUBI */
OP_0x04A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ADDI */
OP_0x0600:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	dst = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ADDI */
OP_0x0610:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ADDI */
OP_0x0618:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ADDI */
OP_0x0620:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ADDI */
OP_0x0628:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* ADDI */
OP_0x0630:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* ADDI */
OP_0x0638:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* ADDI */
OP_0x0639:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* ADDI */
OP_0x061F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ADDI */
OP_0x0627:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ADDI */
OP_0x0640:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	dst = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ADDI */
OP_0x0650:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ADDI */
OP_0x0658:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ADDI */
OP_0x0660:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ADDI */
OP_0x0668:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ADDI */
OP_0x0670:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* ADDI */
OP_0x0678:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ADDI */
OP_0x0679:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* ADDI */
OP_0x065F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ADDI */
OP_0x0667:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ADDI */
OP_0x0680:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(16)

/* ADDI */
OP_0x0690:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ADDI */
OP_0x0698:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ADDI */
OP_0x06A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ADDI */
OP_0x06A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* ADDI */
OP_0x06B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* ADDI */
OP_0x06B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* ADDI */
OP_0x06B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(36)

/* ADDI */
OP_0x069F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ADDI */
OP_0x06A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* CMPI */
OP_0x0C00:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	dst = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
}
RET(8)

/* CMPI */
OP_0x0C10:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMPI */
OP_0x0C18:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMPI */
OP_0x0C20:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(14)

/* CMPI */
OP_0x0C28:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(16)

/* CMPI */
OP_0x0C30:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(18)

/* CMPI */
OP_0x0C38:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(16)

/* CMPI */
OP_0x0C39:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(20)

/* CMPI */
OP_0x0C1F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMPI */
OP_0x0C27:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(14)

/* CMPI */
OP_0x0C40:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	dst = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
}
RET(8)

/* CMPI */
OP_0x0C50:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMPI */
OP_0x0C58:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMPI */
OP_0x0C60:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(14)

/* CMPI */
OP_0x0C68:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(16)

/* CMPI */
OP_0x0C70:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(18)

/* CMPI */
OP_0x0C78:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(16)

/* CMPI */
OP_0x0C79:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(20)

/* CMPI */
OP_0x0C5F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMPI */
OP_0x0C67:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(14)

/* CMPI */
OP_0x0C80:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(14)

/* CMPI */
OP_0x0C90:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMPI */
OP_0x0C98:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMPI */
OP_0x0CA0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(22)

/* CMPI */
OP_0x0CA8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(24)

/* CMPI */
OP_0x0CB0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(26)

/* CMPI */
OP_0x0CB8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(24)

/* CMPI */
OP_0x0CB9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(28)

/* CMPI */
OP_0x0C9F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMPI */
OP_0x0CA7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(22)

/* BTSTn */
OP_0x0800:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
}
RET(10)

/* BTSTn */
OP_0x0810:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(12)

/* BTSTn */
OP_0x0818:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(12)

/* BTSTn */
OP_0x0820:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(14)

/* BTSTn */
OP_0x0828:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(16)

/* BTSTn */
OP_0x0830:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(18)

/* BTSTn */
OP_0x0838:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(16)

/* BTSTn */
OP_0x0839:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(20)

/* BTSTn */
OP_0x083A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(16)

/* BTSTn */
OP_0x083B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(18)

/* BTSTn */
OP_0x081F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(12)

/* BTSTn */
OP_0x0827:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(14)

/* BCHGn */
OP_0x0840:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
	res ^= src;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(12)

/* BCHGn */
OP_0x0850:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCHGn */
OP_0x0858:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCHGn */
OP_0x0860:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BCHGn */
OP_0x0868:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BCHGn */
OP_0x0870:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* BCHGn */
OP_0x0878:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BCHGn */
OP_0x0879:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* BCHGn */
OP_0x085F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCHGn */
OP_0x0867:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BCLRn */
OP_0x0880:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
	res &= ~src;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(14)

/* BCLRn */
OP_0x0890:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCLRn */
OP_0x0898:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCLRn */
OP_0x08A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BCLRn */
OP_0x08A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BCLRn */
OP_0x08B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* BCLRn */
OP_0x08B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BCLRn */
OP_0x08B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* BCLRn */
OP_0x089F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCLRn */
OP_0x08A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BSETn */
OP_0x08C0:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
	res |= src;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(12)

/* BSETn */
OP_0x08D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BSETn */
OP_0x08D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BSETn */
OP_0x08E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BSETn */
OP_0x08E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BSETn */
OP_0x08F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* BSETn */
OP_0x08F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BSETn */
OP_0x08F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* BSETn */
OP_0x08DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BSETn */
OP_0x08E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BTST */
OP_0x0100:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
}
RET(6)

/* BTST */
OP_0x0110:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(8)

/* BTST */
OP_0x0118:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(8)

/* BTST */
OP_0x0120:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(10)

/* BTST */
OP_0x0128:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(12)

/* BTST */
OP_0x0130:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(14)

/* BTST */
OP_0x0138:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(12)

/* BTST */
OP_0x0139:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(16)

/* BTST */
OP_0x013A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(12)

/* BTST */
OP_0x013B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(14)

/* BTST */
OP_0x013C:
{
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_notZ = res & src;
}
RET(8)

/* BTST */
OP_0x011F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(8)

/* BTST */
OP_0x0127:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	POST_IO
}
RET(10)

/* BCHG */
OP_0x0140:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
	res ^= src;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* BCHG */
OP_0x0150:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BCHG */
OP_0x0158:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BCHG */
OP_0x0160:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* BCHG */
OP_0x0168:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCHG */
OP_0x0170:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BCHG */
OP_0x0178:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCHG */
OP_0x0179:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BCHG */
OP_0x015F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BCHG */
OP_0x0167:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* BCLR */
OP_0x0180:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
	res &= ~src;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(10)

/* BCLR */
OP_0x0190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BCLR */
OP_0x0198:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BCLR */
OP_0x01A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* BCLR */
OP_0x01A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCLR */
OP_0x01B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BCLR */
OP_0x01B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BCLR */
OP_0x01B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BCLR */
OP_0x019F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BCLR */
OP_0x01A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* BSET */
OP_0x01C0:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 31));
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_notZ = res & src;
	res |= src;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* BSET */
OP_0x01D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BSET */
OP_0x01D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BSET */
OP_0x01E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* BSET */
OP_0x01E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BSET */
OP_0x01F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* BSET */
OP_0x01F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* BSET */
OP_0x01F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* BSET */
OP_0x01DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* BSET */
OP_0x01E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	src = (uint32_t)(1 << (src & 7));
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_notZ = res & src;
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEPWaD */
OP_0x0108:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr + 0, res)
	READ_BYTE_F(adr + 2, src)
	*(uint16_t*)(&CPU->D[(Opcode >> 9) & 7]) = (res << 8) | (uint16_t)src;
	POST_IO
}
RET(24)

/* MOVEPLaD */
OP_0x0148:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res <<= 24;
	adr += 2;
	READ_BYTE_F(adr, src)
	res |= src << 16;
	adr += 2;
	READ_BYTE_F(adr, src)
	res |= src << 8;
	adr += 2;
	READ_BYTE_F(adr, src)
	CPU->D[(Opcode >> 9) & 7] = res | (uint32_t)src;
	POST_IO
}
RET(32)

/* MOVEPWDa */
OP_0x0188:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr + 0, res >> 8)
	WRITE_BYTE_F(adr + 2, res >> 0)
	POST_IO
}
RET(24)

/* MOVEPLDa */
OP_0x01C8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res >> 24)
	adr += 2;
	WRITE_BYTE_F(adr, res >> 16)
	adr += 2;
	WRITE_BYTE_F(adr, res >> 8)
	adr += 2;
	WRITE_BYTE_F(adr, res >> 0)
	POST_IO
}
RET(32)
