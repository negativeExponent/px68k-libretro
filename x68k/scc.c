/*
 *  SCC.C - Z8530 SCC (mouse only)
 */

#include "../x11/common.h"
#include "../x11/state.h"

#include "../x11/mouse.h"

#include "scc.h"
#include "irqh.h"

int8_t MouseX = 0;
int8_t MouseY = 0;
uint8_t MouseSt    = 0;

#if 0
static uint8_t SCC_RegsA[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#endif
static uint8_t SCC_RegNumA   = 0;
static uint8_t SCC_RegSetA   = 0;
static uint8_t SCC_RegsB[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t SCC_RegNumB   = 0;
static uint8_t SCC_RegSetB   = 0;
static uint8_t SCC_Vector    = 0;
static uint8_t SCC_Dat[3]    = { 0, 0, 0 };
static uint8_t SCC_DatNum    = 0;

static int32_t FASTCALL SCC_Int(int32_t irq)
{
	IRQH_IRQCallBack(irq);
	if ((irq == 5) && (!(SCC_RegsB[9] & 2)))
	{
		if (SCC_RegsB[9] & 1)
		{
			if (SCC_RegsB[9] & 0x10)
			{
				return ((int32_t)(SCC_Vector & 0x8f) + 0x20);
			}
			else
			{
				return ((int32_t)(SCC_Vector & 0xf1) + 4);
			}
		}
	}

	return IRQ_DEFAULT_VECTOR;
}

void SCC_IntCheck(void)
{
	if ((SCC_DatNum) && ((SCC_RegsB[1] & 0x18) == 0x10) && (SCC_RegsB[9] & 0x08))
	{
		IRQH_Int(5, &SCC_Int);
	}
	else if ((SCC_DatNum == 3) && ((SCC_RegsB[1] & 0x18) == 0x08) && (SCC_RegsB[9] & 0x08))
	{
		IRQH_Int(5, &SCC_Int);
	}
}

void SCC_Init(void)
{
	MouseX      = 0;
	MouseY      = 0;
	MouseSt     = 0;
	SCC_RegNumA = 0;
	SCC_RegSetA = 0;
	SCC_RegNumB = 0;
	SCC_RegSetB = 0;
	SCC_Vector  = 0;
	SCC_DatNum  = 0;
}

/* I/O Write */
void FASTCALL SCC_Write(uint32_t adr, uint8_t data)
{
	if (adr >= 0xe98008)
		return;

	if ((adr & 7) == 1)
	{
		if (SCC_RegSetB)
		{
			if (SCC_RegNumB == 5)
			{
				if ((!(SCC_RegsB[5] & 2)) && (data & 2) && (SCC_RegsB[3] & 1) &&
					(!SCC_DatNum)) /* Only do this when there is no data (Dark Bloodline) */
				{
					/* Generate mouse data */
					Mouse_SetData();
					SCC_DatNum = 3;
					SCC_Dat[2] = MouseSt;
					SCC_Dat[1] = MouseX;
					SCC_Dat[0] = MouseY;
				}
			}
			else if (SCC_RegNumB == 2)
				SCC_Vector = data;
			SCC_RegSetB            = 0;
			SCC_RegsB[SCC_RegNumB] = data;
			SCC_RegNumB            = 0;
		}
		else
		{
			if (!(data & 0xf0))
			{
				data &= 15;
				SCC_RegSetB = 1;
				SCC_RegNumB = data;
			}
			else
			{
				SCC_RegSetB = 0;
				SCC_RegNumB = 0;
			}
		}
	}
	else if ((adr & 7) == 5)
	{
		if (SCC_RegSetA)
		{
			SCC_RegSetA = 0;
			switch (SCC_RegNumA)
			{
			case 2:
				SCC_RegsB[2] = data;
				SCC_Vector   = data;
				break;
			case 9:
				SCC_RegsB[9] = data;
				break;
			}
		}
		else
		{
			data &= 15;
			if (data)
			{
				SCC_RegSetA = 1;
				SCC_RegNumA = data;
			}
			else
			{
				SCC_RegSetA = 0;
				SCC_RegNumA = 0;
			}
		}
	}
	else if ((adr & 7) == 3)
	{
		/* nothing to do */
	}
	else if ((adr & 7) == 7)
	{
		/* nothing to do */
	}
}

/* I/O Read */
uint8_t FASTCALL SCC_Read(uint32_t adr)
{
	uint8_t ret = 0;

	if (adr >= 0xe98008)
		return ret;

	if ((adr & 7) == 1)
	{
		if (!SCC_RegNumB)
			ret = ((SCC_DatNum) ? 1 : 0);
		SCC_RegNumB = 0;
		SCC_RegSetB = 0;
	}
	else if ((adr & 7) == 3)
	{
		if (SCC_DatNum)
		{
			SCC_DatNum--;
			ret = SCC_Dat[SCC_DatNum];
		}
	}
	else if ((adr & 7) == 5)
	{
		switch (SCC_RegNumA)
		{
		case 0:
			ret = 4; /* Send buffer empty (Xna) */
			break;
		case 3:
			ret = ((SCC_DatNum) ? 4 : 0);
			break;
		}
		SCC_RegNumA = 0;
		SCC_RegSetA = 0;
	}
	return ret;
}

int SCC_StateContext(void *f, int writing) {
	state_context_f(&MouseX, 1);
	state_context_f(&MouseY, 1);
	state_context_f(&MouseSt, 1);

	state_context_f(&SCC_RegNumA, 1);
	state_context_f(&SCC_RegSetA, 1);
	state_context_f(SCC_RegsB, sizeof(SCC_RegsB));
	state_context_f(&SCC_RegNumB, 1);
	state_context_f(&SCC_RegSetB, 1);
	state_context_f(&SCC_Vector, 1);
	state_context_f(SCC_Dat, sizeof(SCC_RegsB));
	state_context_f(&SCC_DatNum, 1);

	return 1;
}
