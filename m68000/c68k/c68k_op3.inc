
/* MOVEW */
OP_0x3000:
{
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* MOVEW */
OP_0x3080:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x30C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3100:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3140:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3180:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x31C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x33C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3EC0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3F00:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3008:
{
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* MOVEW */
OP_0x3088:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x30C8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3108:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3148:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3188:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x31C8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x33C8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3EC8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3F08:
{
	uint32_t adr;
	uint32_t res;
	res = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3010:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3090:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x30D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3110:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3150:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3190:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x31D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x33D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x3ED0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3F10:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3018:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x3098:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x30D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3118:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3158:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3198:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x31D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x33D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x3ED8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3F18:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3020:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* MOVEW */
OP_0x30A0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x30E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x3120:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x3160:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x31A0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x31E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x33E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x3EE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x3F20:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x3028:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x30A8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x30E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3128:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3168:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x31A8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x31E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x33E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEW */
OP_0x3EE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3F28:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3030:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x30B0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x30F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x3130:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x3170:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x31B0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEW */
OP_0x31F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x33F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEW */
OP_0x3EF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x3F30:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x3038:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x30B8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x30F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3138:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3178:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x31B8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x31F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x33F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEW */
OP_0x3EF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3F38:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3039:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x30B9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x30F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x3139:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x3179:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEW */
OP_0x31B9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEW */
OP_0x31F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEW */
OP_0x33F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEW */
OP_0x3EF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x3F39:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x303A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x30BA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x30FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x313A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x317A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x31BA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x31FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x33FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEW */
OP_0x3EFA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x3F3A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x303B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x30BB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x30FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x313B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x317B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x31BB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEW */
OP_0x31FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x33FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEW */
OP_0x3EFB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x3F3B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x303C:
{
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* MOVEW */
OP_0x30BC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x30FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x313C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x317C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x31BC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x31FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x33FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x3EFC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3F3C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x301F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* MOVEW */
OP_0x309F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x30DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x311F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x315F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x319F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x31DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEW */
OP_0x33DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x3EDF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3F1F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEW */
OP_0x3027:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* MOVEW */
OP_0x30A7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x30E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x3127:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] - 2;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x3167:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x31A7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEW */
OP_0x31E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEW */
OP_0x33E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEW */
OP_0x3EE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEW */
OP_0x3F27:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEAW */
OP_0x3040:
{
	uint32_t res;
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(4)

/* MOVEAW */
OP_0x3048:
{
	uint32_t res;
	res = (int32_t)(int16_t)CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(4)

/* MOVEAW */
OP_0x3050:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(8)

/* MOVEAW */
OP_0x3058:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(8)

/* MOVEAW */
OP_0x3060:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(10)

/* MOVEAW */
OP_0x3068:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* MOVEAW */
OP_0x3070:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)

/* MOVEAW */
OP_0x3078:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* MOVEAW */
OP_0x3079:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* MOVEAW */
OP_0x307A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* MOVEAW */
OP_0x307B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)

/* MOVEAW */
OP_0x307C:
{
	uint32_t res;
	res = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* MOVEAW */
OP_0x305F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(8)

/* MOVEAW */
OP_0x3067:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READSX_WORD_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(10)
