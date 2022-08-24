// ---------------------------------------------------------------------------------------
//  IRQH.C - IRQ Handler (架空のデバイスにょ)
// ---------------------------------------------------------------------------------------

#include "common.h"
#include "../m68000/m68000.h"
#include "irqh.h"

#if defined (HAVE_CYCLONE)
extern struct Cyclone m68k;
typedef signed int  FASTCALL C68K_INT_CALLBACK(signed int level);
#elif defined (HAVE_M68000)
typedef signed int  FASTCALL C68K_INT_CALLBACK(signed int level);
#elif defined (HAVE_MUSASHI)
typedef signed int  FASTCALL C68K_INT_CALLBACK(signed int level);
#endif

	BYTE	IRQH_IRQ[8];
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
DWORD FASTCALL IRQH_DefaultVector(BYTE irq)
{
	IRQH_IRQCallBack(irq);
	return -1;
}


// -----------------------------------------------------------------------
//   他の割り込みのチェック
//   各デバイスのベクタを返すルーチンから呼ばれます
// -----------------------------------------------------------------------
void IRQH_IRQCallBack(BYTE irq)
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
void IRQH_Int(BYTE irq, void* handler)
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

signed int  my_irqh_callback(signed int  level)
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

	return (signed int )vect;
}
