// ---------------------------------------------------------------------------------------
//  IRQH.C - IRQ Handler (�Ͷ��ΥǥХ����ˤ�)
// ---------------------------------------------------------------------------------------

#include "common.h"
#include "../m68000/m68000.h"
#include "irqh.h"

#ifdef HAVE_CYCLONE
extern struct Cyclone m68k;
typedef signed int  FASTCALL C68K_INT_CALLBACK(signed int level);
#endif /* HAVE_CYCLONE */

	BYTE	IRQH_IRQ[8];
	void	*IRQH_CallBack[8];

// -----------------------------------------------------------------------
//   �����
// -----------------------------------------------------------------------
void IRQH_Init(void)
{
	ZeroMemory(IRQH_IRQ, 8);
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
#if 0
	int i;
	IRQH_IRQ[irq] = 0;
	C68k_Set_IRQ(&C68K, 0);
	for (i=7; i>0; i--)
	{
		if (IRQH_IRQ[i])
		{
			C68k_Set_IRQ_Callback(&C68K, IRQH_CallBack[i]);
			C68k_Set_IRQ(&C68K, i); // xxx 
			if ( C68K.ICount) {					// ¿�ų����߻���CARAT��
				m68000_ICountBk += C68K.ICount;		// ����Ū�˳����ߥ����å��򤵤���
				C68K.ICount = 0;				// �����κ� ^^;
			}
			break;
		}
	}
#endif
	IRQH_IRQ[irq&7] = 0;
int i;

#ifdef HAVE_CYCLONE
	m68k.irq =0;
#endif /* HAVE_CYCLONE */

#ifdef HAVE_C68K
	C68k_Set_IRQ(&C68K, 0);
#endif /* HAVE_C68K */

	for (i=7; i>0; i--)
	{
	    if (IRQH_IRQ[i])
	    {
#ifdef HAVE_CYCLONE
			m68k.irq = i;
#endif /* HAVE_CYCLONE */

#ifdef HAVE_C68K
			C68k_Set_IRQ(&C68K, i);
#endif /* HAVE_C68K */
		return;
	    }
	}
}

// -----------------------------------------------------------------------
//   ������ȯ��
// -----------------------------------------------------------------------
void IRQH_Int(BYTE irq, void* handler)
{
#if 0
    int i;
	IRQH_IRQ[irq] = 1;
	if (handler==NULL)
		IRQH_CallBack[irq] = &IRQH_DefaultVector;
	else
		IRQH_CallBack[irq] = handler;
	for (i=7; i>0; i--)
	{
		if (IRQH_IRQ[i])
		{
                        C68k_Set_IRQ_Callback(&C68K, IRQH_CallBack[i]);
                        C68k_Set_IRQ(&C68K, i, HOLD_LINE); //xxx
			if ( C68K.ICount ) {					// ¿�ų����߻���CARAT��
				m68000_ICountBk += C68K.ICount;		// ����Ū�˳����ߥ����å��򤵤���
				C68K.ICount = 0;				// �����κ� ^^;
			}
			return;
		}
	}
#endif
#if 1
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
#ifdef HAVE_CYCLONE

			m68k.irq = i;
#endif /* HAVE_CYCLONE */

#ifdef HAVE_C68K
			C68k_Set_IRQ(&C68K, i);
#endif /* HAVE_C68K */
			return;
	    }
	}
#endif
#if 0
	int i;
	IRQH_IRQ[irq&7] = 1;
	if (handler==NULL)
	    IRQH_CallBack[irq&7] = &IRQH_DefaultVector;
	else
	    IRQH_CallBack[irq&7] = handler;
	C68k_Set_IRQ(&C68K, irq&7);
#endif
}

signed int  my_irqh_callback(signed int  level)
{
#if 0
    int i;
    int vect = -1;
    for (i=7; i>0; i--)
    {
	if (IRQH_IRQ[i])
	{
	    IRQH_IRQ[level&7] = 0;
	    C68K_INT_CALLBACK *func = IRQH_CallBack[i];
	    vect = (func)(level&7);
	    break;
	}
    }
#endif

    int i;
    C68K_INT_CALLBACK *func = IRQH_CallBack[level&7];
    int vect = (func)(level&7);
    //p6logd("irq vect = %x line = %d\n", vect, level);

    for (i=7; i>0; i--)
    {
		if (IRQH_IRQ[i])
		{
#ifdef HAVE_CYCLONE
			m68k.irq = i;
#endif /* HAVE_CYCLONE */

#ifdef HAVE_C68K
	    	C68k_Set_IRQ(&C68K, i);
#endif /* HAVE_C68K */
			break;
		}
    }

    return (signed int )vect;
}
