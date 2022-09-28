
/* CMP */
OP_0xB000:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
}
RET(4)

/* CMP */
OP_0xB008:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
}
RET(4)

/* CMP */
OP_0xB010:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(8)

/* CMP */
OP_0xB018:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(8)

/* CMP */
OP_0xB020:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(10)

/* CMP */
OP_0xB028:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMP */
OP_0xB030:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(14)

/* CMP */
OP_0xB038:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMP */
OP_0xB039:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(16)

/* CMP */
OP_0xB03A:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMP */
OP_0xB03B:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(14)

/* CMP */
OP_0xB03C:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
}
RET(8)

/* CMP */
OP_0xB01F:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(8)

/* CMP */
OP_0xB027:
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
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(10)

/* CMP */
OP_0xB040:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
}
RET(4)

/* CMP */
OP_0xB048:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
}
RET(4)

/* CMP */
OP_0xB050:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(8)

/* CMP */
OP_0xB058:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(8)

/* CMP */
OP_0xB060:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(10)

/* CMP */
OP_0xB068:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMP */
OP_0xB070:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(14)

/* CMP */
OP_0xB078:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMP */
OP_0xB079:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(16)

/* CMP */
OP_0xB07A:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMP */
OP_0xB07B:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(14)

/* CMP */
OP_0xB07C:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
}
RET(8)

/* CMP */
OP_0xB05F:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(8)

/* CMP */
OP_0xB067:
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
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(10)

/* CMP */
OP_0xB080:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(6)

/* CMP */
OP_0xB088:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(6)

/* CMP */
OP_0xB090:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(16)

/* CMP */
OP_0xB098:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(16)

/* CMP */
OP_0xB0A0:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(18)

/* CMP */
OP_0xB0A8:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMP */
OP_0xB0B0:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(22)

/* CMP */
OP_0xB0B8:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMP */
OP_0xB0B9:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(24)

/* CMP */
OP_0xB0BA:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMP */
OP_0xB0BB:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(22)

/* CMP */
OP_0xB0BC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(14)

/* CMP */
OP_0xB09F:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(16)

/* CMP */
OP_0xB0A7:
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
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(18)

/* CMPM */
OP_0xB108:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMPM */
OP_0xB148:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMPM */
OP_0xB188:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMP7M */
OP_0xB10F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMP7M */
OP_0xB14F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 2;
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMP7M */
OP_0xB18F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 4;
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMPM7 */
OP_0xBF08:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[7];
	CPU->A[7] += 2;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMPM7 */
OP_0xBF48:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[7];
	CPU->A[7] += 2;
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMPM7 */
OP_0xBF88:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[7];
	CPU->A[7] += 4;
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMP7M7 */
OP_0xBF0F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_BYTE_F(adr, src)
	adr = CPU->A[7];
	CPU->A[7] += 2;
	READ_BYTE_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	POST_IO
}
RET(12)

/* CMP7M7 */
OP_0xBF4F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	adr = CPU->A[7];
	CPU->A[7] += 2;
	READ_WORD_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	POST_IO
}
RET(12)

/* CMP7M7 */
OP_0xBF8F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 4;
	PRE_IO
	READ_LONG_F(adr, src)
	adr = CPU->A[7];
	CPU->A[7] += 4;
	READ_LONG_F(adr, dst)
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* EORDa */
OP_0xB100:
{
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* EORDa */
OP_0xB110:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* EORDa */
OP_0xB118:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* EORDa */
OP_0xB120:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* EORDa */
OP_0xB128:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* EORDa */
OP_0xB130:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* EORDa */
OP_0xB138:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* EORDa */
OP_0xB139:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* EORDa */
OP_0xB11F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* EORDa */
OP_0xB127:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* EORDa */
OP_0xB140:
{
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 8;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* EORDa */
OP_0xB150:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* EORDa */
OP_0xB158:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* EORDa */
OP_0xB160:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* EORDa */
OP_0xB168:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* EORDa */
OP_0xB170:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(18)

/* EORDa */
OP_0xB178:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(16)

/* EORDa */
OP_0xB179:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* EORDa */
OP_0xB15F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* EORDa */
OP_0xB167:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(14)

/* EORDa */
OP_0xB180:
{
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res ^= src;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* EORDa */
OP_0xB190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* EORDa */
OP_0xB198:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* EORDa */
OP_0xB1A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* EORDa */
OP_0xB1A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* EORDa */
OP_0xB1B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(26)

/* EORDa */
OP_0xB1B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(24)

/* EORDa */
OP_0xB1B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(28)

/* EORDa */
OP_0xB19F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* EORDa */
OP_0xB1A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(22)

/* CMPA */
OP_0xB0C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(6)

/* CMPA */
OP_0xB0C8:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(6)

/* CMPA */
OP_0xB0D0:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(10)

/* CMPA */
OP_0xB0D8:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(10)

/* CMPA */
OP_0xB0E0:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(12)

/* CMPA */
OP_0xB0E8:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(14)

/* CMPA */
OP_0xB0F0:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(16)

/* CMPA */
OP_0xB0F8:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(14)

/* CMPA */
OP_0xB0F9:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(18)

/* CMPA */
OP_0xB0FA:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(14)

/* CMPA */
OP_0xB0FB:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(16)

/* CMPA */
OP_0xB0FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(10)

/* CMPA */
OP_0xB0DF:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(10)

/* CMPA */
OP_0xB0E7:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(12)

/* CMPA */
OP_0xB1C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(6)

/* CMPA */
OP_0xB1C8:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(6)

/* CMPA */
OP_0xB1D0:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(14)

/* CMPA */
OP_0xB1D8:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(14)

/* CMPA */
OP_0xB1E0:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(16)

/* CMPA */
OP_0xB1E8:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(18)

/* CMPA */
OP_0xB1F0:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMPA */
OP_0xB1F8:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(18)

/* CMPA */
OP_0xB1F9:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(22)

/* CMPA */
OP_0xB1FA:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(18)

/* CMPA */
OP_0xB1FB:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(20)

/* CMPA */
OP_0xB1FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
}
RET(14)

/* CMPA */
OP_0xB1DF:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(14)

/* CMPA */
OP_0xB1E7:
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
	CPU->flag_notZ = res;
	CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	POST_IO
}
RET(16)
