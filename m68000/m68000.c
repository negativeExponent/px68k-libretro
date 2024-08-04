/******************************************************************************

	m68000.c

	M68000 CPUインタフェース関数

******************************************************************************/

#include "../x11/common.h"
#include "../x68k/x68kmemory.h"
#include "../x11/state.h"

#include "m68000.h"

int32_t ICount;

#if defined (HAVE_CYCLONE)
#include "m68000_cyclone.h"
M68K_struct *M68K = &m68000_Cyclone;
#elif defined (HAVE_M68000)
#include "m68000_m68k.h"
M68K_struct *M68K = &m68000_m68k;
#elif defined (HAVE_C68K)
#include "m68000_c68k.h"
M68K_struct *M68K = &m68000_c68k;
#elif defined (HAVE_MUSASHI)
#include "m68000_musashi.h"
M68K_struct *M68K = &m68000_musashi;
#endif

/******************************************************************************
	M68000インタフェース関数
******************************************************************************/

/*--------------------------------------------------------
	CPU初期化
--------------------------------------------------------*/

void m68000_init(void)
{
	M68K->Init();

	M68K->SetReadB((M68K_READ *)cpu_readmem24);
	M68K->SetReadW((M68K_READ *)cpu_readmem24_word);
	M68K->SetWriteB((M68K_WRITE *)cpu_writemem24);
	M68K->SetWriteW((M68K_WRITE *)cpu_writemem24_word);

	M68K->SetFetch(0x000000, 0xbfffff, (uintptr_t)MEM);
    M68K->SetFetch(0xc00000, 0xc7ffff, (uintptr_t)GVRAM);
    M68K->SetFetch(0xe00000, 0xe7ffff, (uintptr_t)TVRAM);
    M68K->SetFetch(0xea0000, 0xea1fff, (uintptr_t)SCSIIPL);
    M68K->SetFetch(0xed0000, 0xed3fff, (uintptr_t)SRAM);
    M68K->SetFetch(0xf00000, 0xfbffff, (uintptr_t)FONT);
    M68K->SetFetch(0xfc0000, 0xffffff, (uintptr_t)IPL);
}

/*--------------------------------------------------------
	CPUリセット
--------------------------------------------------------*/

void m68000_reset(void)
{
	M68K->Reset();
	M68K->SetAReg(7, ((*(uint16_t *)&IPL[0x30000]) << 16) | (*(uint16_t *)&IPL[0x30002]));
	M68K->SetPC(     ((*(uint16_t *)&IPL[0x30004]) << 16) | (*(uint16_t *)&IPL[0x30006]));
	ICount = 0;
}

/*--------------------------------------------------------
	CPU停止
--------------------------------------------------------*/

void m68000_exit(void)
{
}

/*--------------------------------------------------------
	CPU実行
--------------------------------------------------------*/

int32_t m68000_execute(int32_t cycles)
{
	return M68K->Exec(cycles);
}

/*--------------------------------------------------------
	割り込み処理
--------------------------------------------------------*/

void m68000_set_irq_line(uint32_t irqline)
{
	M68K->SetIRQ((int32_t)irqline);
}

int M68000_StateContext(void *f, int writing)
{
	state_context_f(&ICount, sizeof(ICount));
	M68K->StateContext(f, writing);

	return 1;
}
