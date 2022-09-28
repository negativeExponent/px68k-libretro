
/* STCC */
OP_0x50C0:
{
	uint32_t res;
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
}

/* STCC */
OP_0x51C0:
{
	uint32_t res;
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x52C0:
{
	uint32_t res;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x53C0:
{
	uint32_t res;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x54C0:
{
	uint32_t res;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x55C0:
{
	uint32_t res;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x56C0:
{
	uint32_t res;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x57C0:
{
	uint32_t res;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x58C0:
{
	uint32_t res;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x59C0:
{
	uint32_t res;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x5AC0:
{
	uint32_t res;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x5BC0:
{
	uint32_t res;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x5CC0:
{
	uint32_t res;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x5DC0:
{
	uint32_t res;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x5EC0:
{
	uint32_t res;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x5FC0:
{
	uint32_t res;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(6)
	}
	res = 0;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	RET(4)
}

/* STCC */
OP_0x50D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x51D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x52D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x53D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x54D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x55D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x56D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x57D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x58D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x59D0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5AD0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5BD0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5CD0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5DD0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5ED0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5FD0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x50D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x51D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x52D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x53D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x54D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x55D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x56D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x57D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x58D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x59D8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5AD8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5BD8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5CD8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5DD8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5ED8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5FD8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	CPU->A[(Opcode >> 0) & 7] += 1;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x50E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x51E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x52E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x53E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x54E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x55E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x56E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x57E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x58E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x59E0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5AE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5BE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5CE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5DE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5EE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5FE0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] - 1;
	CPU->A[(Opcode >> 0) & 7] = adr;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x50E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x51E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x52E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x53E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x54E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x55E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x56E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x57E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x58E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x59E8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5AE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5BE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5CE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5DE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5EE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5FE8:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7] + (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x50F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x51F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x52F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x53F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x54F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x55F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x56F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x57F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x58F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x59F0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x5AF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x5BF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x5CF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x5DF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x5EF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x5FF0:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[(Opcode >> 0) & 7];
	DECODE_EXT_WORD
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(18)
}

/* STCC */
OP_0x50F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x51F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x52F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x53F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x54F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x55F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x56F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x57F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x58F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x59F8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5AF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5BF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5CF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5DF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5EF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x5FF8:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)(int16_t)FETCH_WORD;
	PC += 2;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(16)
}

/* STCC */
OP_0x50F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x51F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x52F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x53F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x54F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x55F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x56F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x57F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x58F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x59F9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x5AF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x5BF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x5CF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x5DF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x5EF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x5FF9:
{
	uint32_t adr;
	uint32_t res;
	adr = (int32_t)FETCH_LONG;
	PC += 4;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(20)
}

/* STCC */
OP_0x50DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x51DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x52DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x53DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x54DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x55DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x56DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x57DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x58DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x59DF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5ADF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5BDF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5CDF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5DDF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5EDF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x5FDF:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7];
	CPU->A[7] += 2;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(12)
}

/* STCC */
OP_0x50E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x51E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x52E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x53E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x54E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (!(CPU->flag_C & 0x100))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x55E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (CPU->flag_C & 0x100)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x56E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x57E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (!CPU->flag_notZ)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x58E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (!(CPU->flag_V & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x59E7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (CPU->flag_V & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5AE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (!(CPU->flag_N & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5BE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (CPU->flag_N & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5CE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5DE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5EE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* STCC */
OP_0x5FE7:
{
	uint32_t adr;
	uint32_t res;
	adr = CPU->A[7] - 2;
	CPU->A[7] = adr;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = 0xFF;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
	}
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	RET(14)
}

/* DBCC */
OP_0x50C8:
{
	PC += 2;
}
RET(12)

/* DBCC */
OP_0x51C8:
{
	uint32_t res;
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x52C8:
{
	uint32_t res;
	if ((!CPU->flag_notZ) || (CPU->flag_C & 0x100))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x53C8:
{
	uint32_t res;
	if (CPU->flag_notZ && (!(CPU->flag_C & 0x100)))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x54C8:
{
	uint32_t res;
	if (CPU->flag_C & 0x100)
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x55C8:
{
	uint32_t res;
	if (!(CPU->flag_C & 0x100))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x56C8:
{
	uint32_t res;
	if (!CPU->flag_notZ)
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x57C8:
{
	uint32_t res;
	if (CPU->flag_notZ)
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x58C8:
{
	uint32_t res;
	if (CPU->flag_V & 0x80)
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x59C8:
{
	uint32_t res;
	if (!(CPU->flag_V & 0x80))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x5AC8:
{
	uint32_t res;
	if (CPU->flag_N & 0x80)
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x5BC8:
{
	uint32_t res;
	if (!(CPU->flag_N & 0x80))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x5CC8:
{
	uint32_t res;
	if ((CPU->flag_N ^ CPU->flag_V) & 0x80)
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x5DC8:
{
	uint32_t res;
	if (!((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x5EC8:
{
	uint32_t res;
	if ((!CPU->flag_notZ) || ((CPU->flag_N ^ CPU->flag_V) & 0x80))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* DBCC */
OP_0x5FC8:
{
	uint32_t res;
	if (CPU->flag_notZ && (!((CPU->flag_N ^ CPU->flag_V) & 0x80)))
	{
	res = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res--;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
	if ((int32_t)res != -1)
	{
		PC += (int32_t)(int16_t)FETCH_WORD;
		PC -= CPU->BasePC;
		SET_PC(PC);
	RET(10)
	}
	}
	else
	{
		PC += 2;
	RET(12)
	}
	PC += 2;
}
RET(14)

/* ADDQ */
OP_0x5000:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res));
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* ADDQ */
OP_0x5010:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5018:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5020:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5028:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5030:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5038:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5039:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x501F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5027:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5040:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_V = (uint32_t)((src ^ res) & (dst ^ res)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* ADDQ */
OP_0x5048:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 0) & 7] = res;
}
RET(8)

/* ADDQ */
OP_0x5050:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5058:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5060:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5068:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5070:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5078:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5079:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x505F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5067:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5080:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & (uint32_t)dst & 1) + ((uint32_t)src >> 1) + ((uint32_t)dst >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ res) & ((uint32_t)dst ^ res)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* ADDQ */
OP_0x5088:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	res = (uint32_t)(dst + src);
	CPU->A[(Opcode >> 0) & 7] = res;
}
RET(8)

/* ADDQ */
OP_0x5090:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x5098:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x50A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x50A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x50B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x50B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x50B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x509F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* ADDQ */
OP_0x50A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5100:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint8_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res;
	CPU->flag_V = ((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst);
	CPU->flag_notZ = res & 0xFF;
	*(BYTE_OFF + (uint8_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* SUBQ */
OP_0x5110:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5118:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5120:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5128:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5130:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5138:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5139:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x511F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5127:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5140:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint16_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 8;
	CPU->flag_N = CPU->flag_X = CPU->flag_C = res >> 8;
	CPU->flag_notZ = res & 0xFFFF;
	*(WORD_OFF + (uint16_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(4)

/* SUBQ */
OP_0x5148:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 0) & 7] = res;
}
RET(8)

/* SUBQ */
OP_0x5150:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5158:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5160:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5168:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5170:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5178:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5179:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x515F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5167:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5180:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint32_t)CPU->D[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->flag_notZ = res;
	CPU->flag_X = CPU->flag_C = (((uint32_t)src & res & 1) + ((uint32_t)src >> 1) + (res >> 1)) >> 23;
	CPU->flag_V = (((uint32_t)src ^ (uint32_t)dst) & (res ^ (uint32_t)dst)) >> 24;
	CPU->flag_N = res >> 24;
	*((uint32_t*)(&CPU->D[(Opcode >> 0) & 7])) = res;
}
RET(8)

/* SUBQ */
OP_0x5188:
{
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
	dst = (uint32_t)CPU->A[(Opcode >> 0) & 7];
	res = (uint32_t)(dst - src);
	CPU->A[(Opcode >> 0) & 7] = res;
}
RET(8)

/* SUBQ */
OP_0x5190:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x5198:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x51A0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x51A8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x51B0:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x51B8:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x51B9:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x519F:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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

/* SUBQ */
OP_0x51A7:
{
	uint32_t adr;
	uint32_t res;
	uintptr_t dst;
	uintptr_t src;
	src = (((Opcode >> 9) - 1) & 7) + 1;
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
