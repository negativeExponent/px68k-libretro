
/* MOVEB */
OP_0x1000:
{
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* MOVEB */
OP_0x1080:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x10C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1100:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1140:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1180:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x11C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x13C0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1EC0:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1F00:
{
	uint32_t adr;
	uint32_t res;
	res = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1008:
{
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(4)

/* MOVEB */
OP_0x1088:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x10C8:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1108:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1148:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1188:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x11C8:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x13C8:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1EC8:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1F08:
{
	uint32_t adr;
	uint32_t res;
	/* can't read byte from Ax registers ! */
	CPU->Status |= C68K_FAULTED;
	CCnt = 0;
	goto C68k_Exec_Really_End;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1010:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1090:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x10D0:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1110:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1150:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1190:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x11D0:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x13D0:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x1ED0:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1F10:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1018:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x1098:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x10D8:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1118:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1158:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1198:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x11D8:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x13D8:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x1ED8:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1F18:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1020:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* MOVEB */
OP_0x10A0:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x10E0:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x1120:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x1160:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x11A0:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x11E0:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x13E0:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x1EE0:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x1F20:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x1028:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x10A8:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x10E8:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1128:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1168:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x11A8:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x11E8:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x13E8:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEB */
OP_0x1EE8:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1F28:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1030:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x10B0:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x10F0:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x1130:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x1170:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x11B0:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEB */
OP_0x11F0:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x13F0:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEB */
OP_0x1EF0:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x1F30:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x1038:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x10B8:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x10F8:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1138:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1178:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x11B8:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x11F8:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x13F8:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEB */
OP_0x1EF8:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1F38:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1039:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x10B9:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x10F9:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x1139:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x1179:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEB */
OP_0x11B9:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEB */
OP_0x11F9:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEB */
OP_0x13F9:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(28)

/* MOVEB */
OP_0x1EF9:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x1F39:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x103A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x10BA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x10FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x113A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x117A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x11BA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x11FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x13FA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEB */
OP_0x1EFA:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x1F3A:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC) + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x103B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x10BB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x10FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x113B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x117B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x11BB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(24)

/* MOVEB */
OP_0x11FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x13FB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(26)

/* MOVEB */
OP_0x1EFB:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x1F3B:
{
	uint32_t adr;
	uint32_t res;
	adr = (uint32_t)(PC - CPU->BasePC);
	DECODE_EXT_WORD
	PRE_IO
	READ_BYTE_F(adr, res)
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x103C:
{
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
}
RET(8)

/* MOVEB */
OP_0x10BC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x10FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x113C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x117C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x11BC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x11FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x13FC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x1EFC:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1F3C:
{
	uint32_t adr;
	uint32_t res;
	res = FETCH_BYTE;
	PC += 2;
	CPU->flag_C = 0;
	CPU->flag_V = 0;
	CPU->flag_notZ = res;
	CPU->flag_N = res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x101F:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(8)

/* MOVEB */
OP_0x109F:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x10DF:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x111F:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x115F:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x119F:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x11DF:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(16)

/* MOVEB */
OP_0x13DF:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x1EDF:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1F1F:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(12)

/* MOVEB */
OP_0x1027:
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
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 9) & 7])) = res;
	POST_IO
}
RET(10)

/* MOVEB */
OP_0x10A7:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x10E7:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	CPU->A[(Opcode >> 9) & 7] += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x1127:
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
	adr = CPU->A[(Opcode >> 9) & 7] - 1;
	CPU->A[(Opcode >> 9) & 7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x1167:
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
	adr = CPU->A[(Opcode >> 9) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x11A7:
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
	adr = CPU->A[(Opcode >> 9) & 7];
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(20)

/* MOVEB */
OP_0x11E7:
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
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(18)

/* MOVEB */
OP_0x13E7:
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
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(22)

/* MOVEB */
OP_0x1EE7:
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
	adr = CPU->A[7];
	CPU->A[7] += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)

/* MOVEB */
OP_0x1F27:
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
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
}
RET(14)
