
/* ADDaD */
OP_0xD000:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ADDaD */
OP_0xD008:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ADDaD */
OP_0xD010:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_BYTE_F(adr, src)
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ADDaD */
OP_0xD018:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ADDaD */
OP_0xD020:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ADDaD */
OP_0xD028:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ADDaD */
OP_0xD030:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ADDaD */
OP_0xD038:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ADDaD */
OP_0xD039:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ADDaD */
OP_0xD03A:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ADDaD */
OP_0xD03B:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ADDaD */
OP_0xD03C:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_BYTE;
	PC += 2;
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* ADDaD */
OP_0xD01F:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ADDaD */
OP_0xD027:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ADDaD */
OP_0xD040:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ADDaD */
OP_0xD048:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ADDaD */
OP_0xD050:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ADDaD */
OP_0xD058:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ADDaD */
OP_0xD060:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ADDaD */
OP_0xD068:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ADDaD */
OP_0xD070:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ADDaD */
OP_0xD078:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ADDaD */
OP_0xD079:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ADDaD */
OP_0xD07A:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* ADDaD */
OP_0xD07B:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* ADDaD */
OP_0xD07C:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_WORD;
	PC += 2;
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* ADDaD */
OP_0xD05F:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* ADDaD */
OP_0xD067:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* ADDaD */
OP_0xD080:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* ADDaD */
OP_0xD088:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(6)

/* ADDaD */
OP_0xD090:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_LONG_F(adr, src)
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ADDaD */
OP_0xD098:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ADDaD */
OP_0xD0A0:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* ADDaD */
OP_0xD0A8:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ADDaD */
OP_0xD0B0:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* ADDaD */
OP_0xD0B8:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ADDaD */
OP_0xD0B9:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(24)

/* ADDaD */
OP_0xD0BA:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(20)

/* ADDaD */
OP_0xD0BB:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(22)

/* ADDaD */
OP_0xD0BC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(14)

/* ADDaD */
OP_0xD09F:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* ADDaD */
OP_0xD0A7:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(18)

/* ADDDa */
OP_0xD110:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ADDDa */
OP_0xD118:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* ADDDa */
OP_0xD120:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* ADDDa */
OP_0xD128:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ADDDa */
OP_0xD130:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ADDDa */
OP_0xD138:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* ADDDa */
OP_0xD139:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* ADDDa */
OP_0xD11F:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* ADDDa */
OP_0xD127:
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
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* ADDDa */
OP_0xD150:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 9) & 7];
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
RET(12)

/* ADDDa */
OP_0xD158:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ADDDa */
OP_0xD160:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ADDDa */
OP_0xD168:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ADDDa */
OP_0xD170:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ADDDa */
OP_0xD178:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ADDDa */
OP_0xD179:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ADDDa */
OP_0xD15F:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ADDDa */
OP_0xD167:
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
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ADDDa */
OP_0xD190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 9) & 7];
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
RET(20)

/* ADDDa */
OP_0xD198:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* ADDDa */
OP_0xD1A0:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* ADDDa */
OP_0xD1A8:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* ADDDa */
OP_0xD1B0:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(26)

/* ADDDa */
OP_0xD1B8:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(24)

/* ADDDa */
OP_0xD1B9:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(28)

/* ADDDa */
OP_0xD19F:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(20)

/* ADDDa */
OP_0xD1A7:
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
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(22)

/* ADDX */
OP_0xD100:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint8_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ |= res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ADDX */
OP_0xD140:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint16_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* ADDX */
OP_0xD180:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->D[(Opcode >> 9) & 7];
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* ADDXM */
OP_0xD108:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ADDXM */
OP_0xD148:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ADDXM */
OP_0xD188:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ADDX7M */
OP_0xD10F:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ADDX7M */
OP_0xD14F:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ADDX7M */
OP_0xD18F:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ADDXM7 */
OP_0xDF08:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ADDXM7 */
OP_0xDF48:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ADDXM7 */
OP_0xDF88:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ADDX7M7 */
OP_0xDF0F:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ |= res & 0xFF;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* ADDX7M7 */
OP_0xDF4F:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ |= res & 0xFFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ADDX7M7 */
OP_0xDF8F:
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
	res = (uint32_t)dst + (uint32_t)src + ((CPU->flag_X >> 8) & 1);
	CPU->flag_notZ |= res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	WRITE_LONG_F(adr, res)
	POST_IO
}
RET(30)

/* ADDA */
OP_0xD0C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* ADDA */
OP_0xD0C8:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(8)

/* ADDA */
OP_0xD0D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_WORD_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* ADDA */
OP_0xD0D8:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* ADDA */
OP_0xD0E0:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)

/* ADDA */
OP_0xD0E8:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* ADDA */
OP_0xD0F0:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* ADDA */
OP_0xD0F8:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* ADDA */
OP_0xD0F9:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* ADDA */
OP_0xD0FA:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* ADDA */
OP_0xD0FB:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* ADDA */
OP_0xD0FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(12)

/* ADDA */
OP_0xD0DF:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(12)

/* ADDA */
OP_0xD0E7:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(14)

/* ADDA */
OP_0xD1C0:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)CPU->D[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(6)

/* ADDA */
OP_0xD1C8:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)CPU->A[(Opcode >> 0) & 7];
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(6)

/* ADDA */
OP_0xD1D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READSX_LONG_F(adr, src)
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* ADDA */
OP_0xD1D8:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* ADDA */
OP_0xD1E0:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)

/* ADDA */
OP_0xD1E8:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* ADDA */
OP_0xD1F0:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(22)

/* ADDA */
OP_0xD1F8:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* ADDA */
OP_0xD1F9:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(24)

/* ADDA */
OP_0xD1FA:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(20)

/* ADDA */
OP_0xD1FB:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(22)

/* ADDA */
OP_0xD1FC:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (int32_t)(int32_t)FETCH_LONG;
	PC += 4;
	dst = (uint32_t)CPU->A[(Opcode >> 9) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
}
RET(14)

/* ADDA */
OP_0xD1DF:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(16)

/* ADDA */
OP_0xD1E7:
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
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 9) & 7] = res;
	POST_IO
}
RET(18)
