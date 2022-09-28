
/* ANDaD */
OP_0xC000:
{
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ANDaD */
OP_0xC010:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ANDaD */
OP_0xC018:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ANDaD */
OP_0xC020:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ANDaD */
OP_0xC028:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ANDaD */
OP_0xC030:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ANDaD */
OP_0xC038:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ANDaD */
OP_0xC039:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ANDaD */
OP_0xC03A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ANDaD */
OP_0xC03B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ANDaD */
OP_0xC03C:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* ANDaD */
OP_0xC01F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ANDaD */
OP_0xC027:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ANDaD */
OP_0xC040:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ANDaD */
OP_0xC050:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ANDaD */
OP_0xC058:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ANDaD */
OP_0xC060:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ANDaD */
OP_0xC068:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ANDaD */
OP_0xC070:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ANDaD */
OP_0xC078:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ANDaD */
OP_0xC079:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ANDaD */
OP_0xC07A:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ANDaD */
OP_0xC07B:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ANDaD */
OP_0xC07C:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* ANDaD */
OP_0xC05F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ANDaD */
OP_0xC067:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ANDaD */
OP_0xC080:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* ANDaD */
OP_0xC090:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ANDaD */
OP_0xC098:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ANDaD */
OP_0xC0A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* ANDaD */
OP_0xC0A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ANDaD */
OP_0xC0B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* ANDaD */
OP_0xC0B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ANDaD */
OP_0xC0B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(24)

/* ANDaD */
OP_0xC0BA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ANDaD */
OP_0xC0BB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* ANDaD */
OP_0xC0BC:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(14)

/* ANDaD */
OP_0xC09F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ANDaD */
OP_0xC0A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res &= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* ANDDa */
OP_0xC110:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ANDDa */
OP_0xC118:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ANDDa */
OP_0xC120:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ANDDa */
OP_0xC128:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ANDDa */
OP_0xC130:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* ANDDa */
OP_0xC138:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ANDDa */
OP_0xC139:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ANDDa */
OP_0xC11F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ANDDa */
OP_0xC127:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ANDDa */
OP_0xC150:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ANDDa */
OP_0xC158:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ANDDa */
OP_0xC160:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ANDDa */
OP_0xC168:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ANDDa */
OP_0xC170:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* ANDDa */
OP_0xC178:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* ANDDa */
OP_0xC179:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ANDDa */
OP_0xC15F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ANDDa */
OP_0xC167:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* ANDDa */
OP_0xC190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ANDDa */
OP_0xC198:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ANDDa */
OP_0xC1A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* ANDDa */
OP_0xC1A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* ANDDa */
OP_0xC1B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(26)

/* ANDDa */
OP_0xC1B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* ANDDa */
OP_0xC1B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(28)

/* ANDDa */
OP_0xC19F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ANDDa */
OP_0xC1A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* ABCD */
OP_0xC100:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (dst & 0xF) + (src & 0xF) + ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99)
	{
		res -= 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* ABCDM */
OP_0xC108:
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
	res = (dst & 0xF) + (src & 0xF) + ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99)
	{
		res -= 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ABCD7M */
OP_0xC10F:
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
	res = (dst & 0xF) + (src & 0xF) + ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99)
	{
		res -= 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ABCDM7 */
OP_0xCF08:
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
	res = (dst & 0xF) + (src & 0xF) + ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99)
	{
		res -= 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ABCD7M7 */
OP_0xCF0F:
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
	res = (dst & 0xF) + (src & 0xF) + ((CPU->flag_X >> C68K_SR_X_SFT) & 1);
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99)
	{
		res -= 0xA0;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_notZ |= res & 0xFF;
	CPU->flag_N = res;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MULU */
OP_0xC0C0:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(50)

/* MULU */
OP_0xC0D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(54)

/* MULU */
OP_0xC0D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(54)

/* MULU */
OP_0xC0E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(56)

/* MULU */
OP_0xC0E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(58)

/* MULU */
OP_0xC0F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(60)

/* MULU */
OP_0xC0F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(58)

/* MULU */
OP_0xC0F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(62)

/* MULU */
OP_0xC0FA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(58)

/* MULU */
OP_0xC0FB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(60)

/* MULU */
OP_0xC0FC:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(54)

/* MULU */
OP_0xC0DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(54)

/* MULU */
OP_0xC0E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (uint32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(56)

/* MULS */
OP_0xC1C0:
{
	uint32_t res;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(50)

/* MULS */
OP_0xC1D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(54)

/* MULS */
OP_0xC1D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(54)

/* MULS */
OP_0xC1E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(56)

/* MULS */
OP_0xC1E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(58)

/* MULS */
OP_0xC1F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(60)

/* MULS */
OP_0xC1F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(58)

/* MULS */
OP_0xC1F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(62)

/* MULS */
OP_0xC1FA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(58)

/* MULS */
OP_0xC1FB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(60)

/* MULS */
OP_0xC1FC:
{
	uint32_t res;
	uintptr_t src;
	src = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(54)

/* MULS */
OP_0xC1DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(54)

/* MULS */
OP_0xC1E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READSX_WORD_F(adr, src)
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 9) & 7];
	res *= (int32_t)src;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(56)

/* EXGDD */
OP_0xC140:
{
	uint32_t res;
	uintptr_t src;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	res = (uint32_t)src;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* EXGAA */
OP_0xC148:
{
	uint32_t res;
	uintptr_t src;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	src = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] = res;
	res = (uint32_t)src;
	CPU->A[(Opcode >> 0) & 7] = res;
}
RET(6)

/* EXGAD */
OP_0xC188:
{
	uint32_t res;
	uintptr_t src;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	res = (uint32_t)src;
	CPU->A[(Opcode >> 0) & 7] = res;
}
RET(6)
