
/* ORaD */
OP_0x8000:
{
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ORaD */
OP_0x8010:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ORaD */
OP_0x8018:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ORaD */
OP_0x8020:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ORaD */
OP_0x8028:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ORaD */
OP_0x8030:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ORaD */
OP_0x8038:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ORaD */
OP_0x8039:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ORaD */
OP_0x803A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ORaD */
OP_0x803B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ORaD */
OP_0x803C:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* ORaD */
OP_0x801F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ORaD */
OP_0x8027:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ORaD */
OP_0x8040:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ORaD */
OP_0x8050:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ORaD */
OP_0x8058:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ORaD */
OP_0x8060:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ORaD */
OP_0x8068:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ORaD */
OP_0x8070:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ORaD */
OP_0x8078:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ORaD */
OP_0x8079:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ORaD */
OP_0x807A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ORaD */
OP_0x807B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ORaD */
OP_0x807C:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* ORaD */
OP_0x805F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ORaD */
OP_0x8067:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ORaD */
OP_0x8080:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* ORaD */
OP_0x8090:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ORaD */
OP_0x8098:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ORaD */
OP_0x80A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* ORaD */
OP_0x80A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ORaD */
OP_0x80B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* ORaD */
OP_0x80B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ORaD */
OP_0x80B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(24)

/* ORaD */
OP_0x80BA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ORaD */
OP_0x80BB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* ORaD */
OP_0x80BC:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(14)

/* ORaD */
OP_0x809F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ORaD */
OP_0x80A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res |= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* ORDa */
OP_0x8110:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ORDa */
OP_0x8118:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ORDa */
OP_0x8120:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ORDa */
OP_0x8128:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ORDa */
OP_0x8130:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* ORDa */
OP_0x8138:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ORDa */
OP_0x8139:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ORDa */
OP_0x811F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ORDa */
OP_0x8127:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ORDa */
OP_0x8150:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ORDa */
OP_0x8158:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ORDa */
OP_0x8160:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ORDa */
OP_0x8168:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ORDa */
OP_0x8170:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* ORDa */
OP_0x8178:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ORDa */
OP_0x8179:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ORDa */
OP_0x815F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ORDa */
OP_0x8167:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ORDa */
OP_0x8190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ORDa */
OP_0x8198:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ORDa */
OP_0x81A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* ORDa */
OP_0x81A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* ORDa */
OP_0x81B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(26)

/* ORDa */
OP_0x81B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* ORDa */
OP_0x81B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(28)

/* ORDa */
OP_0x819F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ORDa */
OP_0x81A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* SBCD */
OP_0x8100:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (dst & 0xF) - (src & 0xF) - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99)
	{
		res += 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* SBCDM */
OP_0x8108:
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
	res = (dst & 0xF) - (src & 0xF) - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99)
	{
		res += 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SBCD7M */
OP_0x810F:
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
	res = (dst & 0xF) - (src & 0xF) - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99)
	{
		res += 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SBCDM7 */
OP_0x8F08:
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
	res = (dst & 0xF) - (src & 0xF) - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99)
	{
		res += 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* SBCD7M7 */
OP_0x8F0F:
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
	res = (dst & 0xF) - (src & 0xF) - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99)
	{
		res += 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* DIVU */
OP_0x80C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(10)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(70)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(90)

/* DIVU */
OP_0x80D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(74)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(94)

/* DIVU */
OP_0x80D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(74)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(94)

/* DIVU */
OP_0x80E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(16)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(76)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(96)

/* DIVU */
OP_0x80E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(18)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(78)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(98)

/* DIVU */
OP_0x80F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(20)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(80)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(100)

/* DIVU */
OP_0x80F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(18)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(78)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(98)

/* DIVU */
OP_0x80F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(22)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(82)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(102)

/* DIVU */
OP_0x80FA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(18)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(78)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(98)

/* DIVU */
OP_0x80FB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(20)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(80)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(100)

/* DIVU */
OP_0x80FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(74)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(94)

/* DIVU */
OP_0x80DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(74)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(94)

/* DIVU */
OP_0x80E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(16)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	{
		uint32_t q, r;

		q = (uint32_t)dst / (uint32_t)src;
		r = (uint32_t)dst % (uint32_t)src;

		if (q & 0xFFFF0000)
		{
			CPU->flag_V = C68K_SR_V;
	RET(76)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(96)

/* DIVS */
OP_0x81C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(10)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(50)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(80)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(108)

/* DIVS */
OP_0x81D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(54)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(84)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(112)

/* DIVS */
OP_0x81D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(54)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(84)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(112)

/* DIVS */
OP_0x81E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(16)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(56)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(86)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(114)

/* DIVS */
OP_0x81E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(18)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(58)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(88)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(116)

/* DIVS */
OP_0x81F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(20)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(60)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(90)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(118)

/* DIVS */
OP_0x81F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(18)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(58)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(88)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(116)

/* DIVS */
OP_0x81F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(22)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(62)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(92)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(120)

/* DIVS */
OP_0x81FA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(18)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(58)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(88)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(116)

/* DIVS */
OP_0x81FB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(20)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(60)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(90)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(118)

/* DIVS */
OP_0x81FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(54)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(84)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(112)

/* DIVS */
OP_0x81DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(14)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(54)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(84)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(112)

/* DIVS */
OP_0x81E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READSX_WORD_F(adr, src)
	if (src == 0)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ZERO_DIVIDE_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	POST_IO
	RET(16)
	}
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	if ((dst == 0x80000000) && ((int32_t)src == -1))
	{
		CPU->flag_notZ = CPU->flag_N = 0;
		CPU->flag_V = CPU->flag_C = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	RET(56)
	}
	{
		int32_t q, r;

		q = (int32_t)dst / (int32_t)src;
		r = (int32_t)dst % (int32_t)src;

		if ((q > 0x7FFF) || (q < -0x8000))
		{
			CPU->flag_V = C68K_SR_V;
	RET(86)
		}
		q &= 0x0000FFFF;
		CPU->flag_notZ = q;
		CPU->flag_N = q >> 8;
		CPU->flag_V = CPU->flag_C = 0;
		res = q | (r << 16);
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	}
}
RET(114)
