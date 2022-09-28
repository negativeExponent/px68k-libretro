
/* ASRk */
OP_0xE000:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (int32_t)(int8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = ((int32_t)src) >> sft;
	CPU->flag_N = res >> 0;
	CPU->flag_notZ = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ASRk */
OP_0xE040:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = ((int32_t)src) >> sft;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ASRk */
OP_0xE080:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (int32_t)(int32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = ((int32_t)src) >> sft;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* LSRk */
OP_0xE008:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = (uint32_t)src >> sft;
	CPU->flag_notZ = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* LSRk */
OP_0xE048:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = (uint32_t)src >> sft;
	CPU->flag_notZ = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* LSRk */
OP_0xE088:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = (uint32_t)src >> sft;
	CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ROXRk */
OP_0xE010:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	src |= (CPU->flag_X & C68K_SR_X) << 0;
	res = ((uint32_t)src >> sft) | ((uint32_t)src << (9 - sft));
	CPU->flag_X = CPU->flag_C = res >> 0;
	CPU->flag_V = 0;
	CPU->flag_N = res >> 0;
	CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ROXRk */
OP_0xE050:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	src |= (CPU->flag_X & C68K_SR_X) << 8;
	res = ((uint32_t)src >> sft) | ((uint32_t)src << (17 - sft));
	CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_V = 0;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ROXRk */
OP_0xE090:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	if (sft == 1) res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << (32 - (C68K_SR_X_SFT + 1)));
	else res = ((uint32_t)src >> sft) | ((uint32_t)src << (33 - sft)) | ((CPU->flag_X & C68K_SR_X) << (32 - (C68K_SR_X_SFT + sft)));
	CPU->flag_X = CPU->flag_C;
	CPU->flag_V = 0;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* RORk */
OP_0xE018:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = ((uint32_t)src >> sft) | ((uint32_t)src << (8 - sft));
	CPU->flag_N = res >> 0;
	CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* RORk */
OP_0xE058:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = ((uint32_t)src >> sft) | ((uint32_t)src << (16 - sft));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* RORk */
OP_0xE098:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
	res = ((uint32_t)src >> sft) | ((uint32_t)src << (32 - sft));
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ASLk */
OP_0xE100:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft < 8)
	{
		CPU->flag_X = CPU->flag_C = (uint32_t)src << (0 + sft);
		res = (uint32_t)src << sft;
		CPU->flag_N = res >> 0;
		CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
		CPU->flag_V = 0;
		if ((sft > 7) && (src)) CPU->flag_V = C68K_SR_V;
		else
		{
			uint32_t msk = (((int32_t)0x80000000) >> (sft + 24)) & 0x000000FF;
			src &= msk;
			if ((src) && (src != msk)) CPU->flag_V = C68K_SR_V;
		}
	RET(6)
	}

	if (src) CPU->flag_V = C68K_SR_V;
	else CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	CPU->flag_N = 0;
	CPU->flag_notZ = 0;
}
RET(6)

/* ASLk */
OP_0xE140:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
		CPU->flag_X = CPU->flag_C = (uint32_t)src >> (8 - sft);
		res = (uint32_t)src << sft;
		CPU->flag_N = res >> 8;
		CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
		CPU->flag_V = 0;
		{
			uint32_t msk = (((int32_t)0x80000000) >> (sft + 16)) & 0x0000FFFF;
			src &= msk;
			if ((src) && (src != msk)) CPU->flag_V = C68K_SR_V;
		}
}
RET(6)

/* ASLk */
OP_0xE180:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
		CPU->flag_X = CPU->flag_C = (uint32_t)src >> (24 - sft);
		res = (uint32_t)src << sft;
		CPU->flag_N = res >> 24;
		CPU->flag_notZ = res & 0xFFFFFFFF;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
		CPU->flag_V = 0;
		{
			uint32_t msk = (((int32_t)0x80000000) >> (sft + 0)) & 0xFFFFFFFF;
			src &= msk;
			if ((src) && (src != msk)) CPU->flag_V = C68K_SR_V;
		}
}
RET(8)

/* LSLk */
OP_0xE108:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << (0 + sft);
	res = (uint32_t)src << sft;
	CPU->flag_N = res >> 0;
	CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* LSLk */
OP_0xE148:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src >> (8 - sft);
	res = (uint32_t)src << sft;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* LSLk */
OP_0xE188:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src >> (24 - sft);
	res = (uint32_t)src << sft;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res & 0xFFFFFFFF;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ROXLk */
OP_0xE110:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	src |= (CPU->flag_X & C68K_SR_X) << 0;
	res = ((uint32_t)src << sft) | ((uint32_t)src >> (9 - sft));
	CPU->flag_X = CPU->flag_C = res >> 0;
	CPU->flag_V = 0;
	CPU->flag_N = res >> 0;
	CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ROXLk */
OP_0xE150:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	src |= (CPU->flag_X & C68K_SR_X) << 8;
	res = ((uint32_t)src << sft) | ((uint32_t)src >> (17 - sft));
	CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_V = 0;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ROXLk */
OP_0xE190:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_C = (uint32_t)src >> ((32 - C68K_SR_C_SFT) - sft);
	if (sft == 1) res = ((uint32_t)src << 1) | ((CPU->flag_X & C68K_SR_X) >> ((C68K_SR_X_SFT + 1) - 1));
	else res = ((uint32_t)src << sft) | ((uint32_t)src >> (33 - sft)) | ((CPU->flag_X & C68K_SR_X) >> ((C68K_SR_X_SFT + 1) - sft));
	CPU->flag_X = CPU->flag_C;
	CPU->flag_V = 0;
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ROLk */
OP_0xE118:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)src << (0 + sft);
	res = ((uint32_t)src << sft) | ((uint32_t)src >> (8 - sft));
	CPU->flag_N = res >> 0;
	CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ROLk */
OP_0xE158:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)src >> (8 - sft);
	res = ((uint32_t)src << sft) | ((uint32_t)src >> (16 - sft));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(6)

/* ROLk */
OP_0xE198:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = (((Opcode >> 9) - 1) & 7) + 1;
	CCnt -= sft * 2;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)src >> (24 - sft);
	res = ((uint32_t)src << sft) | ((uint32_t)src >> (32 - sft));
	CPU->flag_N = res >> 24;
	CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ASRD */
OP_0xE020:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (int32_t)(int8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 8)
		{
			CPU->flag_V = 0;
			CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
			res = ((int32_t)src) >> sft;
			CPU->flag_N = res >> 0;
			CPU->flag_notZ = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		if (src & (1 << 7))
		{
			CPU->flag_N = C68K_SR_N;
			CPU->flag_notZ = 1;
			CPU->flag_V = 0;
			CPU->flag_C = C68K_SR_C;
			CPU->flag_X = C68K_SR_X;
			res = 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		CPU->flag_C = 0;
		CPU->flag_X = 0;
		res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ASRD */
OP_0xE060:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (int32_t)(int16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 16)
		{
			CPU->flag_V = 0;
			CPU->flag_X = CPU->flag_C = ((uint32_t)src >> (sft - 1)) << C68K_SR_C_SFT;
			res = ((int32_t)src) >> sft;
			CPU->flag_N = res >> 8;
			CPU->flag_notZ = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		if (src & (1 << 15))
		{
			CPU->flag_N = C68K_SR_N;
			CPU->flag_notZ = 1;
			CPU->flag_V = 0;
			CPU->flag_C = C68K_SR_C;
			CPU->flag_X = C68K_SR_X;
			res = 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		CPU->flag_C = 0;
		CPU->flag_X = 0;
		res = 0;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ASRD */
OP_0xE0A0:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (int32_t)(int32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 32)
		{
			CPU->flag_V = 0;
			CPU->flag_X = CPU->flag_C = ((uint32_t)src >> (sft - 1)) << C68K_SR_C_SFT;
			res = ((int32_t)src) >> sft;
			CPU->flag_N = res >> 24;
			CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
		}

		if (src & (1 << 31))
		{
			CPU->flag_N = C68K_SR_N;
			CPU->flag_notZ = 1;
			CPU->flag_V = 0;
			CPU->flag_C = C68K_SR_C;
			CPU->flag_X = C68K_SR_X;
			res = 0xFFFFFFFF;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
		}

		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		CPU->flag_C = 0;
		CPU->flag_X = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* LSRD */
OP_0xE028:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft <= 8)
		{
			CPU->flag_N = CPU->flag_V = 0;
			CPU->flag_X = CPU->flag_C = (uint32_t)src << ((C68K_SR_C_SFT + 1) - sft);
			res = (uint32_t)src >> sft;
			CPU->flag_notZ = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_X = CPU->flag_C = 0;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* LSRD */
OP_0xE068:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft <= 16)
		{
			CPU->flag_N = CPU->flag_V = 0;
			CPU->flag_X = CPU->flag_C = ((uint32_t)src >> (sft - 1)) << C68K_SR_C_SFT;
			res = (uint32_t)src >> sft;
			CPU->flag_notZ = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_X = CPU->flag_C = 0;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		res = 0;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* LSRD */
OP_0xE0A8:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 32)
		{
			CPU->flag_N = CPU->flag_V = 0;
			CPU->flag_X = CPU->flag_C = ((uint32_t)src >> (sft - 1)) << C68K_SR_C_SFT;
			res = (uint32_t)src >> sft;
			CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
		}

		if (sft == 32) CPU->flag_C = (uint32_t)src >> (31 - C68K_SR_C_SFT);
		else CPU->flag_C = 0;
		CPU->flag_X = CPU->flag_C;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* ROXRD */
OP_0xE030:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft %= 9;

		src |= (CPU->flag_X & C68K_SR_X) << 0;
		res = ((uint32_t)src >> sft) | ((uint32_t)src << (9 - sft));
		CPU->flag_X = CPU->flag_C = res >> 0;
		CPU->flag_V = 0;
		CPU->flag_N = res >> 0;
		CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = CPU->flag_X;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ROXRD */
OP_0xE070:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft %= 17;

		src |= (CPU->flag_X & C68K_SR_X) << 8;
		res = ((uint32_t)src >> sft) | ((uint32_t)src << (17 - sft));
		CPU->flag_X = CPU->flag_C = res >> 8;
		CPU->flag_V = 0;
		CPU->flag_N = res >> 8;
		CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = CPU->flag_X;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ROXRD */
OP_0xE0B0:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft %= 33;

		if (sft != 0)
		{
			if (sft == 1) res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << (32 - (C68K_SR_X_SFT + 1)));
			else res = ((uint32_t)src >> sft) | ((uint32_t)src << (33 - sft)) | (((CPU->flag_X & C68K_SR_X) << (32 - (C68K_SR_X_SFT + 1))) >> (sft - 1));
			CPU->flag_X = ((uint32_t)src >> (32 - sft)) << C68K_SR_X_SFT;
		}
		else res = (uint32_t)src;
		CPU->flag_C = CPU->flag_X;
		CPU->flag_V = 0;
		CPU->flag_N = res >> 24;
		CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = CPU->flag_X;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* RORD */
OP_0xE038:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft &= 0x07;
		
		CPU->flag_C = (uint32_t)src << (C68K_SR_C_SFT - ((sft - 1) & 7));
		res = ((uint32_t)src >> sft) | ((uint32_t)src << (8 - sft));
		CPU->flag_V = 0;
		CPU->flag_N = res >> 0;
		CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* RORD */
OP_0xE078:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft &= 0x0F;
		
		CPU->flag_C = ((uint32_t)src >> ((sft - 1) & 15)) << C68K_SR_C_SFT;
		res = ((uint32_t)src >> sft) | ((uint32_t)src << (16 - sft));
		CPU->flag_V = 0;
		CPU->flag_N = res >> 8;
		CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* RORD */
OP_0xE0B8:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft &= 0x1F;
		
		CPU->flag_C = ((uint32_t)src >> ((sft - 1) & 31)) << C68K_SR_C_SFT;
		res = ((uint32_t)src >> sft) | ((uint32_t)src << (32 - sft));
		CPU->flag_V = 0;
		CPU->flag_N = res >> 24;
		CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* ASLD */
OP_0xE120:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 8)
		{
			CPU->flag_X = CPU->flag_C = ((uint32_t)src << sft) >> 0;
			res = ((uint32_t)src << sft) & 0x000000FF;
			CPU->flag_N = res >> 0;
			CPU->flag_notZ = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
			CPU->flag_V = 0;
			{
				uint32_t msk = (((int32_t)0x80000000) >> (sft + 24)) & 0x000000FF;
				src &= msk;
				if ((src) && (src != msk)) CPU->flag_V = C68K_SR_V;
			}
	RET(6)
		}

		if (sft == 256) CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
		else CPU->flag_C = 0;
		CPU->flag_X = CPU->flag_C;
		if (src) CPU->flag_V = C68K_SR_V;
		else CPU->flag_V = 0;
		res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ASLD */
OP_0xE160:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 16)
		{
			CPU->flag_X = CPU->flag_C = ((uint32_t)src << sft) >> 8;
			res = ((uint32_t)src << sft) & 0x0000FFFF;
			CPU->flag_N = res >> 8;
			CPU->flag_notZ = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
			CPU->flag_V = 0;
			{
				uint32_t msk = (((int32_t)0x80000000) >> (sft + 16)) & 0x0000FFFF;
				src &= msk;
				if ((src) && (src != msk)) CPU->flag_V = C68K_SR_V;
			}
	RET(6)
		}

		if (sft == 65536) CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
		else CPU->flag_C = 0;
		CPU->flag_X = CPU->flag_C;
		if (src) CPU->flag_V = C68K_SR_V;
		else CPU->flag_V = 0;
		res = 0;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ASLD */
OP_0xE1A0:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 32)
		{
			CPU->flag_X = CPU->flag_C = ((uint32_t)src >> (32 - sft)) << C68K_SR_C_SFT;
			res = (uint32_t)(src << sft);
			CPU->flag_N = res >> 24;
			CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
			CPU->flag_V = 0;
			{
				uint32_t msk = (((int32_t)0x80000000) >> (sft + 0)) & 0xFFFFFFFF;
				src &= msk;
				if ((src) && (src != msk)) CPU->flag_V = C68K_SR_V;
			}
	RET(8)
		}

		if (sft == 0) CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
		else CPU->flag_C = 0;
		CPU->flag_X = CPU->flag_C;
		if (src) CPU->flag_V = C68K_SR_V;
		else CPU->flag_V = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* LSLD */
OP_0xE128:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft <= 8)
		{
			CPU->flag_X = CPU->flag_C = ((uint32_t)src << sft) >> 0;
			res = (src << sft) & 0x000000FF;
			CPU->flag_V = 0;
			CPU->flag_N = res >> 0;
			CPU->flag_notZ = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_X = CPU->flag_C = 0;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* LSLD */
OP_0xE168:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft <= 16)
		{
			CPU->flag_X = CPU->flag_C = ((uint32_t)src << sft) >> 8;
			res = (src << sft) & 0x0000FFFF;
			CPU->flag_V = 0;
			CPU->flag_N = res >> 8;
			CPU->flag_notZ = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_X = CPU->flag_C = 0;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		res = 0;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* LSLD */
OP_0xE1A8:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft < 32)
		{
			CPU->flag_X = CPU->flag_C = ((uint32_t)src >> (32 - sft)) << C68K_SR_C_SFT;
			res = (uint32_t)(src << sft);
			CPU->flag_V = 0;
			CPU->flag_N = res >> 24;
			CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
		}

		if (sft == 32) CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
		else CPU->flag_C = 0;
		CPU->flag_X = CPU->flag_C;
		CPU->flag_N = 0;
		CPU->flag_notZ = 0;
		CPU->flag_V = 0;
		res = 0;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* ROXLD */
OP_0xE130:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft %= 9;

		src |= (CPU->flag_X & C68K_SR_X) << 0;
		res = ((uint32_t)src << sft) | ((uint32_t)src >> (9 - sft));
		CPU->flag_X = CPU->flag_C = res >> 0;
		CPU->flag_V = 0;
		CPU->flag_N = res >> 0;
		CPU->flag_notZ = res & 0x000000FF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = CPU->flag_X;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ROXLD */
OP_0xE170:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft %= 17;

		src |= (CPU->flag_X & C68K_SR_X) << 8;
		res = ((uint32_t)src << sft) | ((uint32_t)src >> (17 - sft));
		CPU->flag_X = CPU->flag_C = res >> 8;
		CPU->flag_V = 0;
		CPU->flag_N = res >> 8;
		CPU->flag_notZ = res & 0x0000FFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = CPU->flag_X;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ROXLD */
OP_0xE1B0:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		sft %= 33;

		if (sft != 0)
		{
			if (sft == 1) res = ((uint32_t)src << 1) | ((CPU->flag_X >> ((C68K_SR_X_SFT + 1) - 1)) & 1);
			else res = ((uint32_t)src << sft) | ((uint32_t)src >> (33 - sft)) | (((CPU->flag_X >> ((C68K_SR_X_SFT + 1) - 1)) & 1) << (sft - 1));
			CPU->flag_X = ((uint32_t)src >> (32 - sft)) << C68K_SR_X_SFT;
		}
		else res = (uint32_t)src;
		CPU->flag_C = CPU->flag_X;
		CPU->flag_V = 0;
		CPU->flag_N = res >> 24;
		CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = CPU->flag_X;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* ROLD */
OP_0xE138:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft &= 0x07)
		{
			CPU->flag_C = (uint32_t)((src << sft) >> 0);
			res = (uint32_t)(((src << sft) | (src >> (8 - sft))) & 0x000000FF);
			CPU->flag_V = 0;
			CPU->flag_N = res >> 0;
			CPU->flag_notZ = res;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_V = 0;
		CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
		CPU->flag_N = (uint32_t)src >> 0;
		CPU->flag_notZ = (uint32_t)src;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 0;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ROLD */
OP_0xE178:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft &= 0x0F)
		{
			CPU->flag_C = (uint32_t)((src << sft) >> 8);
			res = (uint32_t)(((src << sft) | (src >> (16 - sft))) & 0x0000FFFF);
			CPU->flag_V = 0;
			CPU->flag_N = res >> 8;
			CPU->flag_notZ = res;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
		}

		CPU->flag_V = 0;
		CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
		CPU->flag_N = (uint32_t)src >> 8;
		CPU->flag_notZ = (uint32_t)src;
	RET(6)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 8;
	CPU->flag_notZ = (uint32_t)src;
}
RET(6)

/* ROLD */
OP_0xE1B8:
{
	uint32_t res;
	uintptr_t src;
	uint32_t sft;

	sft = CPU->D[(Opcode >> 9) & 7] & 0x3F;
	src = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	if (sft)
	{
	CCnt -= sft * 2;
		if (sft &= 0x1F)
		{
			CPU->flag_C = (uint32_t)((src >> (32 - sft)) << C68K_SR_C_SFT);
			res = (uint32_t)((src << sft) | (src >> (32 - sft)));
			CPU->flag_V = 0;
			CPU->flag_N = res >> 24;
			CPU->flag_notZ = res;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(8)
		}

		CPU->flag_V = 0;
		CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
		CPU->flag_N = (uint32_t)src >> 24;
		CPU->flag_notZ = (uint32_t)src;
	RET(8)
	}

	CPU->flag_V = 0;
	CPU->flag_C = 0;
	CPU->flag_N = (uint32_t)src >> 24;
	CPU->flag_notZ = (uint32_t)src;
}
RET(8)

/* ASR */
OP_0xE0D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ASR */
OP_0xE0D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ASR */
OP_0xE0E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ASR */
OP_0xE0E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ASR */
OP_0xE0F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ASR */
OP_0xE0F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ASR */
OP_0xE0F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ASR */
OP_0xE0DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ASR */
OP_0xE0E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = ((uint32_t)src >> 1) | ((uint32_t)src & (1 << 15));
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* LSR */
OP_0xE2D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* LSR */
OP_0xE2D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* LSR */
OP_0xE2E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* LSR */
OP_0xE2E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* LSR */
OP_0xE2F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* LSR */
OP_0xE2F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* LSR */
OP_0xE2F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* LSR */
OP_0xE2DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* LSR */
OP_0xE2E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_N = CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)src << C68K_SR_C_SFT;
	res = (uint32_t)(src >> 1);
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROXR */
OP_0xE4D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROXR */
OP_0xE4D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROXR */
OP_0xE4E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROXR */
OP_0xE4E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROXR */
OP_0xE4F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ROXR */
OP_0xE4F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROXR */
OP_0xE4F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ROXR */
OP_0xE4DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROXR */
OP_0xE4E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = ((uint32_t)src >> 1) | ((CPU->flag_X & C68K_SR_X) << 7);
	CPU->flag_C = CPU->flag_X = (uint32_t)(src << C68K_SR_C_SFT);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROR */
OP_0xE6D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROR */
OP_0xE6D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROR */
OP_0xE6E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROR */
OP_0xE6E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROR */
OP_0xE6F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ROR */
OP_0xE6F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROR */
OP_0xE6F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ROR */
OP_0xE6DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROR */
OP_0xE6E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src << C68K_SR_C_SFT);
	res = ((uint32_t)src >> 1) | ((uint32_t)src << 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ASL */
OP_0xE1D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ASL */
OP_0xE1D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ASL */
OP_0xE1E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ASL */
OP_0xE1E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ASL */
OP_0xE1F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ASL */
OP_0xE1F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ASL */
OP_0xE1F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ASL */
OP_0xE1DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ASL */
OP_0xE1E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_V = ((uint32_t)src ^ res) >> 8;
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* LSL */
OP_0xE3D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* LSL */
OP_0xE3D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* LSL */
OP_0xE3E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* LSL */
OP_0xE3E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* LSL */
OP_0xE3F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* LSL */
OP_0xE3F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* LSL */
OP_0xE3F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* LSL */
OP_0xE3DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* LSL */
OP_0xE3E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	res = (uint32_t)(src << 1);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROXL */
OP_0xE5D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROXL */
OP_0xE5D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROXL */
OP_0xE5E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROXL */
OP_0xE5E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROXL */
OP_0xE5F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ROXL */
OP_0xE5F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROXL */
OP_0xE5F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ROXL */
OP_0xE5DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROXL */
OP_0xE5E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	res = (uint32_t)(src << 1) | ((CPU->flag_X & C68K_SR_X) >> 8);
	CPU->flag_X = CPU->flag_C = (uint32_t)(src >> 7);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROL */
OP_0xE7D0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROL */
OP_0xE7D8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROL */
OP_0xE7E0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] - 2;
	CPU->A[(Opcode >> 0) & 7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)

/* ROL */
OP_0xE7E8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROL */
OP_0xE7F0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(18)

/* ROL */
OP_0xE7F8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(16)

/* ROL */
OP_0xE7F9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(20)

/* ROL */
OP_0xE7DF:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(12)

/* ROL */
OP_0xE7E7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t src;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	PRE_IO
	READ_WORD_F(adr, src)
	CPU->flag_V = 0;
	CPU->flag_C = (uint32_t)(src >> 7);
	res = ((uint32_t)src << 1) | ((uint32_t)src >> 15);
	CPU->flag_N = res >> 8;
	CPU->flag_notZ = res & 0x0000FFFF;
	WRITE_WORD_F(adr, res)
	POST_IO
}
RET(14)
