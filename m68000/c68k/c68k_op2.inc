
/* MOVEL */
OP_0x2000:
{
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* MOVEL */
OP_0x2080:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x20C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2100:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2140:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEL */
OP_0x2180:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEL */
OP_0x21C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEL */
OP_0x23C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2EC0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2F00:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2008:
{
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* MOVEL */
OP_0x2088:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x20C8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2108:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2148:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEL */
OP_0x2188:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEL */
OP_0x21C8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEL */
OP_0x23C8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2EC8:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2F08:
{
	uint32_t adr;
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2010:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2090:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x20D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2110:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2150:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2190:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x21D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x23D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x2ED0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2F10:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2018:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x2098:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x20D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2118:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2158:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2198:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x21D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x23D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x2ED8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2F18:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2020:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* MOVEL */
OP_0x20A0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x20E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x2120:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x2160:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x21A0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x21E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x23E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x2EE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x2F20:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x2028:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* MOVEL */
OP_0x20A8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x20E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2128:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2168:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x21A8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x21E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x23E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* MOVEL */
OP_0x2EE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2F28:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2030:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* MOVEL */
OP_0x20B0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x20F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x2130:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x2170:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x21B0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* MOVEL */
OP_0x21F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x23F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* MOVEL */
OP_0x2EF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x2F30:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x2038:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* MOVEL */
OP_0x20B8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x20F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2138:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2178:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x21B8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x21F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x23F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* MOVEL */
OP_0x2EF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2F38:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2039:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x20B9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x20F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x2139:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x2179:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* MOVEL */
OP_0x21B9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* MOVEL */
OP_0x21F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* MOVEL */
OP_0x23F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(36)

/* MOVEL */
OP_0x2EF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x2F39:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x203A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* MOVEL */
OP_0x20BA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x20FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x213A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x217A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x21BA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x21FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x23FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* MOVEL */
OP_0x2EFA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x2F3A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x203B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* MOVEL */
OP_0x20BB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x20FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x213B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x217B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x21BB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(32)

/* MOVEL */
OP_0x21FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x23FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(34)

/* MOVEL */
OP_0x2EFB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x2F3B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x203C:
{
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(12)

/* MOVEL */
OP_0x20BC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x20FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x213C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x217C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x21BC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x21FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x23FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x2EFC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2F3C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_LONG;
	PC += 4;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x201F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEL */
OP_0x209F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x20DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x211F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x215F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x219F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x21DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEL */
OP_0x23DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x2EDF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2F1F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEL */
OP_0x2027:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* MOVEL */
OP_0x20A7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x20E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x2127:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] - 4;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x2167:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x21A7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEL */
OP_0x21E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEL */
OP_0x23E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* MOVEL */
OP_0x2EE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEL */
OP_0x2F27:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEAL */
OP_0x2040:
{
	uint32_t res;
	res = (int32_t)(int32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(4)

/* MOVEAL */
OP_0x2048:
{
	uint32_t res;
	res = (int32_t)(int32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(4)

/* MOVEAL */
OP_0x2050:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* MOVEAL */
OP_0x2058:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* MOVEAL */
OP_0x2060:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)

/* MOVEAL */
OP_0x2068:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* MOVEAL */
OP_0x2070:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* MOVEAL */
OP_0x2078:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* MOVEAL */
OP_0x2079:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* MOVEAL */
OP_0x207A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* MOVEAL */
OP_0x207B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* MOVEAL */
OP_0x207C:
{
	uint32_t res;
	res = (int32_t)(int32_t)FETCH_LONG;
	PC += 4;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(12)

/* MOVEAL */
OP_0x205F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* MOVEAL */
OP_0x2067:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READSX_LONG_F(adr, res)
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)
