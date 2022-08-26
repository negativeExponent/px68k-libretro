// ---------------------------------------------------------------------------------------
//  IRQH.C - IRQ Handler (架空のデバイスにょ)
// ---------------------------------------------------------------------------------------

#include "common.h"
#include "../m68000/m68000.h"
#include "irqh.h"

#if defined (HAVE_CYCLONE)
extern struct Cyclone m68k;
typedef int32_t  FASTCALL C68K_INT_CALLBACK(int32_t level);
#elif defined (HAVE_M68000)
typedef int32_t  FASTCALL C68K_INT_CALLBACK(int32_t level);
#elif defined (HAVE_MUSASHI)
typedef int32_t  FASTCALL C68K_INT_CALLBACK(int32_t level);
#endif

	uint8_t	IRQH_IRQ[8];
	void	*IRQH_CallBack[8];

// -----------------------------------------------------------------------
//   初期化
// -----------------------------------------------------------------------
void IRQH_Init(void)
{
	memset(IRQH_IRQ, 0, 8);
}


// -----------------------------------------------------------------------
//   デフォルトのベクタを返す（これが起こったら変だお）
// -----------------------------------------------------------------------
uint32_t FASTCALL IRQH_DefaultVector(uint8_t irq)
{
	IRQH_IRQCallBack(irq);
	return (uint32_t)-1;
}


// -----------------------------------------------------------------------
//   他の割り込みのチェック
//   各デバイスのベクタを返すルーチンから呼ばれます
// -----------------------------------------------------------------------
void IRQH_IRQCallBack(uint8_t irq)
{
	int i;

	IRQH_IRQ[irq&7] = 0;
#if defined (HAVE_CYCLONE)
	m68k.irq =0;
#elif defined (HAVE_M68000)
	C68k_Set_IRQ(&C68K, 0, 0);
#elif defined (HAVE_C68K)
	C68k_Set_IRQ(&C68K, 0);
#elif defined (HAVE_MUSASHI)
	m68k_set_irq(0);
#endif

	for (i=7; i>0; i--)
	{
		if (IRQH_IRQ[i])
		{
#if defined (HAVE_CYCLONE)
			m68k.irq = i;
#elif defined (HAVE_M68000)
			C68k_Set_IRQ_Callback(&C68K, IRQH_CallBack[i]);
			C68k_Set_IRQ(&C68K, i, HOLD_LINE); // xxx
			if ( C68K.ICount) {					// 多重割り込み時（CARAT）
				m68000_ICountBk += C68K.ICount;		// 強制的に割り込みチェックをさせる
				C68K.ICount = 0;				// 苦肉の策 ^^;
			}
#elif defined (HAVE_C68K)
			C68k_Set_IRQ(&C68K, i);
#elif defined (HAVE_MUSASHI)
			m68k_set_irq(i);
#endif
			return;
		}
	}
}

// -----------------------------------------------------------------------
//   割り込み発生
// -----------------------------------------------------------------------
void IRQH_Int(uint8_t irq, void* handler)
{
	int i;

	IRQH_IRQ[irq&7] = 1;
	if (handler==NULL)
		IRQH_CallBack[irq&7] = &IRQH_DefaultVector;
	else
		IRQH_CallBack[irq&7] = handler;
	for (i=7; i>0; i--)
	{
		if (IRQH_IRQ[i])
		{
#if defined (HAVE_CYCLONE)
			m68k.irq = i;
#elif defined (HAVE_M68000)
			C68k_Set_IRQ_Callback(&C68K, IRQH_CallBack[i]);
			C68k_Set_IRQ(&C68K, i, HOLD_LINE); //xxx
			if ( C68K.ICount ) {					// 多重割り込み時（CARAT）
				m68000_ICountBk += C68K.ICount;		// 強制的に割り込みチェックをさせる
				C68K.ICount = 0;				// 苦肉の策 ^^;
			}
#elif defined (HAVE_C68K)
			C68k_Set_IRQ(&C68K, i);
#elif defined (HAVE_MUSASHI)
		m68k_set_irq(i);
#endif
			return;
		}
	}
}

int32_t  my_irqh_callback(int32_t  level)
{
	C68K_INT_CALLBACK *func = IRQH_CallBack[level&7];
	int vect = (func)(level&7);
   	int i;

	for (i=7; i>0; i--)
	{
		if (IRQH_IRQ[i])
		{
#if defined (HAVE_CYCLONE)
			m68k.irq = i;
#elif defined (HAVE_C68K)
			C68k_Set_IRQ(&C68K, i);
#elif defined (HAVE_MUSASHI)
			m68k_set_irq(i);
#endif
			break;
		}
	}

	return (int32_t )vect;
}
