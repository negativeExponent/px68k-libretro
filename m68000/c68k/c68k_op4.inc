
/* NEGX */
OP_0x4000:
{
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* NEGX */
OP_0x4010:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NEGX */
OP_0x4018:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NEGX */
OP_0x4020:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* NEGX */
OP_0x4028:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* NEGX */
OP_0x4030:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* NEGX */
OP_0x4038:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* NEGX */
OP_0x4039:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* NEGX */
OP_0x401F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NEGX */
OP_0x4027:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* NEGX */
OP_0x4040:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* NEGX */
OP_0x4050:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NEGX */
OP_0x4058:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NEGX */
OP_0x4060:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* NEGX */
OP_0x4068:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* NEGX */
OP_0x4070:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* NEGX */
OP_0x4078:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* NEGX */
OP_0x4079:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* NEGX */
OP_0x405F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NEGX */
OP_0x4067:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* NEGX */
OP_0x4080:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* NEGX */
OP_0x4090:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NEGX */
OP_0x4098:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NEGX */
OP_0x40A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* NEGX */
OP_0x40A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* NEGX */
OP_0x40B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* NEGX */
OP_0x40B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* NEGX */
OP_0x40B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* NEGX */
OP_0x409F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NEGX */
OP_0x40A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src - ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* CLR */
OP_0x4200:
{
	uint32_t res;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* CLR */
OP_0x4210:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* CLR */
OP_0x4218:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* CLR */
OP_0x4220:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* CLR */
OP_0x4228:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* CLR */
OP_0x4230:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* CLR */
OP_0x4238:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* CLR */
OP_0x4239:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* CLR */
OP_0x421F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* CLR */
OP_0x4227:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* CLR */
OP_0x4240:
{
	uint32_t res;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* CLR */
OP_0x4250:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* CLR */
OP_0x4258:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* CLR */
OP_0x4260:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* CLR */
OP_0x4268:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* CLR */
OP_0x4270:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* CLR */
OP_0x4278:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* CLR */
OP_0x4279:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* CLR */
OP_0x425F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* CLR */
OP_0x4267:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* CLR */
OP_0x4280:
{
	uint32_t res;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* CLR */
OP_0x4290:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* CLR */
OP_0x4298:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* CLR */
OP_0x42A0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* CLR */
OP_0x42A8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* CLR */
OP_0x42B0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* CLR */
OP_0x42B8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* CLR */
OP_0x42B9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* CLR */
OP_0x429F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* CLR */
OP_0x42A7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	res = 0;
	CPU->flag_N = CPU->flag_notZ = CPU->flag_V = CPU->flag_C = 0;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* NEG */
OP_0x4400:
{
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* NEG */
OP_0x4410:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NEG */
OP_0x4418:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NEG */
OP_0x4420:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* NEG */
OP_0x4428:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* NEG */
OP_0x4430:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* NEG */
OP_0x4438:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* NEG */
OP_0x4439:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* NEG */
OP_0x441F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NEG */
OP_0x4427:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = res & (uint32_t)src;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* NEG */
OP_0x4440:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* NEG */
OP_0x4450:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NEG */
OP_0x4458:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NEG */
OP_0x4460:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* NEG */
OP_0x4468:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* NEG */
OP_0x4470:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* NEG */
OP_0x4478:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* NEG */
OP_0x4479:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* NEG */
OP_0x445F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NEG */
OP_0x4467:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_V = (res & (uint32_t)src) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* NEG */
OP_0x4480:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* NEG */
OP_0x4490:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NEG */
OP_0x4498:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NEG */
OP_0x44A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* NEG */
OP_0x44A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* NEG */
OP_0x44B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* NEG */
OP_0x44B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* NEG */
OP_0x44B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* NEG */
OP_0x449F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NEG */
OP_0x44A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = -(uint32_t)src;
	CPU->flag_notZ = res;
	CPU->flag_V = (res & (uint32_t)src) >> 24;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* NOT */
OP_0x4600:
{
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* NOT */
OP_0x4610:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NOT */
OP_0x4618:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NOT */
OP_0x4620:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* NOT */
OP_0x4628:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* NOT */
OP_0x4630:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* NOT */
OP_0x4638:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* NOT */
OP_0x4639:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* NOT */
OP_0x461F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* NOT */
OP_0x4627:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_N = res;
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* NOT */
OP_0x4640:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* NOT */
OP_0x4650:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NOT */
OP_0x4658:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NOT */
OP_0x4660:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* NOT */
OP_0x4668:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* NOT */
OP_0x4670:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* NOT */
OP_0x4678:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* NOT */
OP_0x4679:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* NOT */
OP_0x465F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* NOT */
OP_0x4667:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res & 0xFFFF;
	CPU->flag_N = res >> 8;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* NOT */
OP_0x4680:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* NOT */
OP_0x4690:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NOT */
OP_0x4698:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NOT */
OP_0x46A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 4;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* NOT */
OP_0x46A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* NOT */
OP_0x46B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* NOT */
OP_0x46B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* NOT */
OP_0x46B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* NOT */
OP_0x469F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* NOT */
OP_0x46A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 4;
	CPU->A[7] = adr;
	PRE_IO
	READ_LONG_F(adr, src)
	res = ~(uint32_t)src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* MOVESRa */
OP_0x40C0:
{
	uint32_t res;
	res = GET_SR;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* MOVESRa */
OP_0x40D0:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVESRa */
OP_0x40D8:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVESRa */
OP_0x40E0:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVESRa */
OP_0x40E8:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVESRa */
OP_0x40F0:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* MOVESRa */
OP_0x40F8:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* MOVESRa */
OP_0x40F9:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* MOVESRa */
OP_0x40DF:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* MOVESRa */
OP_0x40E7:
{
	uint32_t adr;
	uint32_t res;
	res = GET_SR;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEaCCR */
OP_0x44C0:
{
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	SET_CCR(res)
}
RET(12)

/* MOVEaCCR */
OP_0x44D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(16)

/* MOVEaCCR */
OP_0x44D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(16)

/* MOVEaCCR */
OP_0x44E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(18)

/* MOVEaCCR */
OP_0x44E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(20)

/* MOVEaCCR */
OP_0x44F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(22)

/* MOVEaCCR */
OP_0x44F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(20)

/* MOVEaCCR */
OP_0x44F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(24)

/* MOVEaCCR */
OP_0x44FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(20)

/* MOVEaCCR */
OP_0x44FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(22)

/* MOVEaCCR */
OP_0x44FC:
{
	uint32_t res;
	res = FETCH_WORD;
	PC += 2;
	SET_CCR(res)
}
RET(16)

/* MOVEaCCR */
OP_0x44DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(16)

/* MOVEaCCR */
OP_0x44E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
	SET_CCR(res)
	POST_IO
}
RET(18)

/* MOVEaSR */
OP_0x46C0:
{
	uint32_t res;
	if (CPU->flag_S)
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
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
CCnt -= 12;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46D0:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 16;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46D8:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 16;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46E0:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 18;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46E8:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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

/* MOVEaSR */
OP_0x46F0:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 22;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46F8:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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

/* MOVEaSR */
OP_0x46F9:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 24;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46FA:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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

/* MOVEaSR */
OP_0x46FB:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 22;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46FC:
{
	uint32_t res;
	if (CPU->flag_S)
	{
	res = FETCH_WORD;
	PC += 2;
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
CCnt -= 16;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46DF:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 16;
goto C68k_Exec_End;

/* MOVEaSR */
OP_0x46E7:
{
	uint32_t adr;
	uint32_t res;
	if (CPU->flag_S)
	{
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, res)
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
	POST_IO
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
CCnt -= 18;
goto C68k_Exec_End;

/* NBCD */
OP_0x4800:
{
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
}
RET(6)

/* NBCD */
OP_0x4810:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(12)

/* NBCD */
OP_0x4818:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(12)

/* NBCD */
OP_0x4820:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(14)

/* NBCD */
OP_0x4828:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(16)

/* NBCD */
OP_0x4830:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(18)

/* NBCD */
OP_0x4838:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(16)

/* NBCD */
OP_0x4839:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(20)

/* NBCD */
OP_0x481F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(12)

/* NBCD */
OP_0x4827:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	res = 0x9a - res - ((CPU->flag_X >> C68K_SR_X_SFT) & 1);

	if (res != 0x9a)
	{
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
		res &= 0xFF;
	WRITE_BYTE_F(adr, res)
		CPU->flag_notZ |= res;
		CPU->flag_X = CPU->flag_C = C68K_SR_C;
	}
	else CPU->flag_X = CPU->flag_C = 0;
	CPU->flag_N = res;
	POST_IO
}
RET(14)

/* PEA */
OP_0x4850:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
}
RET(12)

/* PEA */
OP_0x4868:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
}
RET(16)

/* PEA */
OP_0x4870:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
}
RET(20)

/* PEA */
OP_0x4878:
{
	uint32_t adr;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
}
RET(16)

/* PEA */
OP_0x4879:
{
	uint32_t adr;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
}
RET(20)

/* PEA */
OP_0x487A:
{
	uint32_t adr;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
}
RET(16)

/* PEA */
OP_0x487B:
{
	uint32_t adr;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
}
RET(20)

/* SWAP */
OP_0x4840:
{
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (res >> 16) | (res << 16);
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* MOVEMRa */
OP_0x4890:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(uint16_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(12)

/* MOVEMRa */
OP_0x48A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->A[7]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 2;
			WRITE_WORD_F(adr, *(uint16_t*)src)
		}
		src -= 4;
	} while (res >>= 1);
	CPU->A[(Opcode >> 0) & 7] = adr;
	POST_IO
	CCnt -= ((uint32_t)dst - adr) * 2;
}
RET(8)

/* MOVEMRa */
OP_0x48A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(uint16_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(20)

/* MOVEMRa */
OP_0x48B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(uint16_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(24)

/* MOVEMRa */
OP_0x48B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(uint16_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(20)

/* MOVEMRa */
OP_0x48B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(uint16_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(28)

/* MOVEMRa */
OP_0x48A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	src = (uintptr_t)(&CPU->A[7]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 2;
			WRITE_WORD_F(adr, *(uint16_t*)src)
		}
		src -= 4;
	} while (res >>= 1);
	CPU->A[7] = adr;
	POST_IO
	CCnt -= ((uint32_t)dst - adr) * 2;
}
RET(8)

/* MOVEMRa */
OP_0x48D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(16)

/* MOVEMRa */
OP_0x48E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->A[7]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 4;
			WRITE_LONG_DEC_F(adr, *(uint32_t*)src)
		}
		src -= 4;
	} while (res >>= 1);
	CPU->A[(Opcode >> 0) & 7] = adr;
	POST_IO
	CCnt -= ((uint32_t)dst - adr) * 2;
}
RET(8)

/* MOVEMRa */
OP_0x48E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(24)

/* MOVEMRa */
OP_0x48F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(28)

/* MOVEMRa */
OP_0x48F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(24)

/* MOVEMRa */
OP_0x48F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(32)

/* MOVEMRa */
OP_0x48E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	src = (uintptr_t)(&CPU->A[7]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 4;
			WRITE_LONG_DEC_F(adr, *(uint32_t*)src)
		}
		src -= 4;
	} while (res >>= 1);
	CPU->A[7] = adr;
	POST_IO
	CCnt -= ((uint32_t)dst - adr) * 2;
}
RET(8)

/* EXT */
OP_0x4880:
{
	uint32_t res;
	res = (int32_t)(int8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* EXT */
OP_0x48C0:
{
	uint32_t res;
	res = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* TST */
OP_0x4A00:
{
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
}
RET(4)

/* TST */
OP_0x4A10:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(8)

/* TST */
OP_0x4A18:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(8)

/* TST */
OP_0x4A20:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(10)

/* TST */
OP_0x4A28:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(12)

/* TST */
OP_0x4A30:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(14)

/* TST */
OP_0x4A38:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(12)

/* TST */
OP_0x4A39:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(16)

/* TST */
OP_0x4A1F:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(8)

/* TST */
OP_0x4A27:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	POST_IO
}
RET(10)

/* TST */
OP_0x4A40:
{
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
}
RET(4)

/* TST */
OP_0x4A50:
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
	POST_IO
}
RET(8)

/* TST */
OP_0x4A58:
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
	POST_IO
}
RET(8)

/* TST */
OP_0x4A60:
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
	POST_IO
}
RET(10)

/* TST */
OP_0x4A68:
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
	POST_IO
}
RET(12)

/* TST */
OP_0x4A70:
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
	POST_IO
}
RET(14)

/* TST */
OP_0x4A78:
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
	POST_IO
}
RET(12)

/* TST */
OP_0x4A79:
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
	POST_IO
}
RET(16)

/* TST */
OP_0x4A5F:
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
	POST_IO
}
RET(8)

/* TST */
OP_0x4A67:
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
	POST_IO
}
RET(10)

/* TST */
OP_0x4A80:
{
	uint32_t res;
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
}
RET(4)

/* TST */
OP_0x4A90:
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
	POST_IO
}
RET(12)

/* TST */
OP_0x4A98:
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
	POST_IO
}
RET(12)

/* TST */
OP_0x4AA0:
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
	POST_IO
}
RET(14)

/* TST */
OP_0x4AA8:
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
	POST_IO
}
RET(16)

/* TST */
OP_0x4AB0:
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
	POST_IO
}
RET(18)

/* TST */
OP_0x4AB8:
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
	POST_IO
}
RET(16)

/* TST */
OP_0x4AB9:
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
	POST_IO
}
RET(20)

/* TST */
OP_0x4A9F:
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
	POST_IO
}
RET(12)

/* TST */
OP_0x4AA7:
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
	POST_IO
}
RET(14)

/* TAS */
OP_0x4AC0:
{
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* TAS */
OP_0x4AD0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* TAS */
OP_0x4AD8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* TAS */
OP_0x4AE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(10)

/* TAS */
OP_0x4AE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* TAS */
OP_0x4AF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* TAS */
OP_0x4AF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* TAS */
OP_0x4AF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* TAS */
OP_0x4ADF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* TAS */
OP_0x4AE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	res |= 0x80;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(10)

/* ILLEGAL */
OP_0x4AFC:
{
	uint32_t res;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_ILLEGAL_INSTRUCTION_EX;
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

/* MOVEMaR */
OP_0x4C90:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(16)

/* MOVEMaR */
OP_0x4C98:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	CPU->A[(Opcode >> 0) & 7] = adr;
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(12)

/* MOVEMaR */
OP_0x4CA8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(24)

/* MOVEMaR */
OP_0x4CB0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(28)

/* MOVEMaR */
OP_0x4CB8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(24)

/* MOVEMaR */
OP_0x4CB9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(32)

/* MOVEMaR */
OP_0x4CBA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(24)

/* MOVEMaR */
OP_0x4CBB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(28)

/* MOVEMaR */
OP_0x4C9F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READSX_WORD_F(adr, *(int32_t*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	CPU->A[7] = adr;
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(12)

/* MOVEMaR */
OP_0x4CD0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(20)

/* MOVEMaR */
OP_0x4CD8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	CPU->A[(Opcode >> 0) & 7] = adr;
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(12)

/* MOVEMaR */
OP_0x4CE8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(28)

/* MOVEMaR */
OP_0x4CF0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(32)

/* MOVEMaR */
OP_0x4CF8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(28)

/* MOVEMaR */
OP_0x4CF9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(36)

/* MOVEMaR */
OP_0x4CFA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(28)

/* MOVEMaR */
OP_0x4CFB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(32)

/* MOVEMaR */
OP_0x4CDF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	res = FETCH_WORD;
	PC += 2;
	adr = CPU->A[7];
	src = (uintptr_t)(&CPU->D[0]);
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			READ_LONG_F(adr, *(uint32_t*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	CPU->A[7] = adr;
	POST_IO
	CCnt -= (adr - (uint32_t)dst) * 2;
}
RET(12)

/* TRAP */
OP_0x4E40:
{
	uint32_t res;
	if (!CPU->flag_S)
	{
		res = CPU->USP;
		CPU->USP = CPU->A[7];
		CPU->A[7] = res;
	}
	res = C68K_TRAP_BASE_EX + (Opcode & 0xF);
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

/* LINK */
OP_0x4E50:
{
	uint32_t res;
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	PUSH_32_F(res)
	res = CPU->A[7];
	CPU->A[(Opcode >> 0) & 7] = res;
	CPU->A[7] += (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	POST_IO
}
RET(16)

/* LINKA7 */
OP_0x4E57:
{
	CPU->A[7] -= 4;
	PRE_IO
	WRITE_LONG_DEC_F(CPU->A[7], CPU->A[7])
	CPU->A[7] += (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	POST_IO
}
RET(16)

/* ULNK */
OP_0x4E58:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->A[7] = (uint32_t)src + 4;
	PRE_IO
	READ_LONG_F((uint32_t)src, res)
	CPU->A[(Opcode >> 0) & 7] = res;
	POST_IO
}
RET(12)

/* ULNKA7 */
OP_0x4E5F:
{
	PRE_IO
	READ_LONG_F(CPU->A[7], CPU->A[7])
	POST_IO
}
RET(12)

/* MOVEAUSP */
OP_0x4E60:
{
	uint32_t res;
	if (!CPU->flag_S)
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
	POST_IO
	RET(4)
	}
	res = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	CPU->USP = res;
}
RET(4)

/* MOVEUSPA */
OP_0x4E68:
{
	uint32_t res;
	if (!CPU->flag_S)
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
	POST_IO
	RET(4)
	}
	res = CPU->USP;
	CPU->A[(Opcode >> 0) & 7] = res;
}
RET(4)

/* RESET */
OP_0x4E70:
{
	uint32_t res;
	if (!CPU->flag_S)
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
	POST_IO
	RET(4)
	}
	PRE_IO
	CPU->Reset_CallBack();
	POST_IO
}
RET(132)

/* NOP */
OP_0x4E71:
{
}
RET(4)

/* STOP */
OP_0x4E72:
{
	uint32_t res;
	if (!CPU->flag_S)
	{
		PC += 2;
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
	POST_IO
	RET(4)
	}
	res = FETCH_WORD & C68K_SR_MASK;
	PC += 2;
	SET_SR(res)
	if (!CPU->flag_S)
	{
		res = CPU->A[7];
		CPU->A[7] = CPU->USP;
		CPU->USP = res;
	}
	CPU->Status |= C68K_HALTED;
	CCnt = 0;
}
CCnt -= 4;
goto C68k_Exec_End;

/* RTE */
OP_0x4E73:
{
	uint32_t res;
	if (!CPU->flag_S)
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
	POST_IO
	RET(4)
	}
	PRE_IO
	POP_16_F(res)
	SET_SR(res)
	POP_32_F(res)
	SET_PC(res)
	if (!CPU->flag_S)
	{
		res = CPU->A[7];
		CPU->A[7] = CPU->USP;
		CPU->USP = res;
	}
}
POST_IO
CCnt -= 20;
goto C68k_Exec_End;

/* RTS */
OP_0x4E75:
{
	uint32_t res;
	PRE_IO
	POP_32_F(res)
	SET_PC(res)
	POST_IO
}
RET(16)

/* TRAPV */
OP_0x4E76:
{
	uint32_t res;
	if (CPU->flag_V & 0x80)
	{
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_TRAPV_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(4)

/* RTR */
OP_0x4E77:
{
	uint32_t res;
	PRE_IO
	POP_16_F(res)
	SET_CCR(res)
	POP_32_F(res)
	SET_PC(res)
	POST_IO
}
RET(20)

/* JSR */
OP_0x4E90:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	SET_PC(adr)
	POST_IO
}
RET(16)

/* JSR */
OP_0x4EA8:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	SET_PC(adr)
	POST_IO
}
RET(18)

/* JSR */
OP_0x4EB0:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	SET_PC(adr)
	POST_IO
}
RET(22)

/* JSR */
OP_0x4EB8:
{
	uint32_t adr;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	SET_PC(adr)
	POST_IO
}
RET(18)

/* JSR */
OP_0x4EB9:
{
	uint32_t adr;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	SET_PC(adr)
	POST_IO
}
RET(20)

/* JSR */
OP_0x4EBA:
{
	uint32_t adr;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	SET_PC(adr)
	POST_IO
}
RET(18)

/* JSR */
OP_0x4EBB:
{
	uint32_t adr;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F((uint32_t)(PC - CPU->BasePC))
	SET_PC(adr)
	POST_IO
}
RET(22)

/* JMP */
OP_0x4ED0:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7];
	SET_PC(adr)
}
RET(8)

/* JMP */
OP_0x4EE8:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	SET_PC(adr)
}
RET(10)

/* JMP */
OP_0x4EF0:
{
	uint32_t adr;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	SET_PC(adr)
}
RET(14)

/* JMP */
OP_0x4EF8:
{
	uint32_t adr;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	SET_PC(adr)
}
RET(10)

/* JMP */
OP_0x4EF9:
{
	uint32_t adr;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	SET_PC(adr)
}
RET(12)

/* JMP */
OP_0x4EFA:
{
	uint32_t adr;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	SET_PC(adr)
}
RET(10)

/* JMP */
OP_0x4EFB:
{
	uint32_t adr;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	SET_PC(adr)
}
RET(14)

/* CHK */
OP_0x4180:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(10)

/* CHK */
OP_0x4190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(14)

/* CHK */
OP_0x4198:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(14)

/* CHK */
OP_0x41A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(16)

/* CHK */
OP_0x41A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(18)

/* CHK */
OP_0x41B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(20)

/* CHK */
OP_0x41B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(18)

/* CHK */
OP_0x41B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(22)

/* CHK */
OP_0x41BA:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(18)

/* CHK */
OP_0x41BB:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(20)

/* CHK */
OP_0x41BC:
{
	uint32_t res;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(14)

/* CHK */
OP_0x419F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(14)

/* CHK */
OP_0x41A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	res = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	if (((int32_t)res < 0) || (res > src))
	{
		CPU->flag_N = res >> 8;
		if (!CPU->flag_S)
		{
			res = CPU->USP;
			CPU->USP = CPU->A[7];
			CPU->A[7] = res;
		}
		res = C68K_CHK_EX;
	POST_IO
	CCnt -= c68k_exception_cycle_table[res];
	PRE_IO
		PUSH_32_F((uint32_t)(PC - CPU->BasePC))
		PUSH_16_F(GET_SR)
		CPU->flag_S = C68K_SR_S;
		READ_LONG_F(res * 4, PC)
		SET_PC(PC)
	}
	POST_IO
}
RET(16)

/* LEA */
OP_0x41D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	res = adr;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(4)

/* LEA */
OP_0x41E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = adr;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* LEA */
OP_0x41F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	res = adr;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(12)

/* LEA */
OP_0x41F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = adr;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* LEA */
OP_0x41F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	res = adr;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(12)

/* LEA */
OP_0x41FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = adr;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* LEA */
OP_0x41FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	res = adr;
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(12)
