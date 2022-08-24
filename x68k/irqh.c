// ---------------------------------------------------------------------------------------
//  IRQH.C - IRQ Handler (�Ͷ��ΥǥХ����ˤ�)
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
//   �����
// -----------------------------------------------------------------------
void IRQH_Init(void)
{
	memset(IRQH_IRQ, 0, 8);
}


// -----------------------------------------------------------------------
//   �ǥե���ȤΥ٥������֤��ʤ��줬�����ä����Ѥ�����
// -----------------------------------------------------------------------
DWORD FASTCALL IRQH_DefaultVector(BYTE irq)
{
	IRQH_IRQCallBack(irq);
	return -1;
}


// -----------------------------------------------------------------------
//   ¾�γ����ߤΥ����å�
//   �ƥǥХ����Υ٥������֤��롼���󤫤�ƤФ�ޤ�
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
			if ( C68K.ICount) {					// ¿�ų����߻���CARAT��
				m68000_ICountBk += C68K.ICount;		// ����Ū�˳����ߥ����å��򤵤���
				C68K.ICount = 0;				// �����κ� ^^;
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
//   ������ȯ��
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
			if ( C68K.ICount ) {					// ¿�ų����߻���CARAT��
				m68000_ICountBk += C68K.ICount;		// ����Ū�˳����ߥ����å��򤵤���
				C68K.ICount = 0;				// �����κ� ^^;
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
