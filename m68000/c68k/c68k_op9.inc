
/* SUBaD */
OP_0x9000:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* SUBaD */
OP_0x9008:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	RET(4)
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* SUBaD */
OP_0x9010:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* SUBaD */
OP_0x9018:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* SUBaD */
OP_0x9020:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* SUBaD */
OP_0x9028:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* SUBaD */
OP_0x9030:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* SUBaD */
OP_0x9038:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* SUBaD */
OP_0x9039:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* SUBaD */
OP_0x903A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* SUBaD */
OP_0x903B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* SUBaD */
OP_0x903C:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* SUBaD */
OP_0x901F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* SUBaD */
OP_0x9027:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* SUBaD */
OP_0x9040:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* SUBaD */
OP_0x9048:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* SUBaD */
OP_0x9050:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* SUBaD */
OP_0x9058:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* SUBaD */
OP_0x9060:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* SUBaD */
OP_0x9068:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* SUBaD */
OP_0x9070:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* SUBaD */
OP_0x9078:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* SUBaD */
OP_0x9079:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* SUBaD */
OP_0x907A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* SUBaD */
OP_0x907B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* SUBaD */
OP_0x907C:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* SUBaD */
OP_0x905F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* SUBaD */
OP_0x9067:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* SUBaD */
OP_0x9080:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* SUBaD */
OP_0x9088:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* SUBaD */
OP_0x9090:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* SUBaD */
OP_0x9098:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* SUBaD */
OP_0x90A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* SUBaD */
OP_0x90A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* SUBaD */
OP_0x90B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* SUBaD */
OP_0x90B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* SUBaD */
OP_0x90B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(24)

/* SUBaD */
OP_0x90BA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* SUBaD */
OP_0x90BB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* SUBaD */
OP_0x90BC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(14)

/* SUBaD */
OP_0x909F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* SUBaD */
OP_0x90A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* SUBDa */
OP_0x9110:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* SUBDa */
OP_0x9118:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* SUBDa */
OP_0x9120:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* SUBDa */
OP_0x9128:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* SUBDa */
OP_0x9130:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* SUBDa */
OP_0x9138:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* SUBDa */
OP_0x9139:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* SUBDa */
OP_0x911F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* SUBDa */
OP_0x9127:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* SUBDa */
OP_0x9150:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* SUBDa */
OP_0x9158:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* SUBDa */
OP_0x9160:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* SUBDa */
OP_0x9168:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* SUBDa */
OP_0x9170:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* SUBDa */
OP_0x9178:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* SUBDa */
OP_0x9179:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* SUBDa */
OP_0x915F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* SUBDa */
OP_0x9167:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* SUBDa */
OP_0x9190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* SUBDa */
OP_0x9198:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* SUBDa */
OP_0x91A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* SUBDa */
OP_0x91A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* SUBDa */
OP_0x91B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(26)

/* SUBDa */
OP_0x91B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* SUBDa */
OP_0x91B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(28)

/* SUBDa */
OP_0x919F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* SUBDa */
OP_0x91A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* SUBX */
OP_0x9100:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ |= res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* SUBX */
OP_0x9140:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* SUBX */
OP_0x9180:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((((uint32_t)src & 1) + (res & 1) + (((CPU->flag_X >> 8) & 1) & 1)) >> 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* SUBXM */
OP_0x9108:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SUBXM */
OP_0x9148:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	READ_WORD_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* SUBXM */
OP_0x9188:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	READ_LONG_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((((uint32_t)src & 1) + (res & 1) + (((CPU->flag_X >> 8) & 1) & 1)) >> 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* SUBX7M */
OP_0x910F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SUBX7M */
OP_0x914F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	READ_WORD_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* SUBX7M */
OP_0x918F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	READ_LONG_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((((uint32_t)src & 1) + (res & 1) + (((CPU->flag_X >> 8) & 1) & 1)) >> 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* SUBXM7 */
OP_0x9F08:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SUBXM7 */
OP_0x9F48:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	READ_WORD_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* SUBXM7 */
OP_0x9F88:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	READ_LONG_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((((uint32_t)src & 1) + (res & 1) + (((CPU->flag_X >> 8) & 1) & 1)) >> 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* SUBX7M7 */
OP_0x9F0F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SUBX7M7 */
OP_0x9F4F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	READ_WORD_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* SUBX7M7 */
OP_0x9F8F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	READ_LONG_F(adr, dst)
	res = (uint32_t)dst - (uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((((uint32_t)src & 1) + (res & 1) + (((CPU->flag_X >> 8) & 1) & 1)) >> 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* SUBA */
OP_0x90C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* SUBA */
OP_0x90C8:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* SUBA */
OP_0x90D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* SUBA */
OP_0x90D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* SUBA */
OP_0x90E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)

/* SUBA */
OP_0x90E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* SUBA */
OP_0x90F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* SUBA */
OP_0x90F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* SUBA */
OP_0x90F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* SUBA */
OP_0x90FA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* SUBA */
OP_0x90FB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* SUBA */
OP_0x90FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(12)

/* SUBA */
OP_0x90DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* SUBA */
OP_0x90E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)

/* SUBA */
OP_0x91C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(6)

/* SUBA */
OP_0x91C8:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(6)

/* SUBA */
OP_0x91D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* SUBA */
OP_0x91D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* SUBA */
OP_0x91E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* SUBA */
OP_0x91E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* SUBA */
OP_0x91F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(22)

/* SUBA */
OP_0x91F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* SUBA */
OP_0x91F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(24)

/* SUBA */
OP_0x91FA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* SUBA */
OP_0x91FB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(22)

/* SUBA */
OP_0x91FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(14)

/* SUBA */
OP_0x91DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* SUBA */
OP_0x91E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)
