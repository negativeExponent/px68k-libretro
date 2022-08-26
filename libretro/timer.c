// -----------------------------------------------------------------------
//   55.6fpsキープ用たいまー
// -----------------------------------------------------------------------
#include "common.h"
#include "crtc.h"
#include "mfp.h"

extern int64_t total_usec;		/* from libretro.c */

uint32_t	timercnt = 0;
uint32_t	tick = 0;

/* Get elapsed time from libretro frontend by way of its frame time callback,
 * if available. Only provides per frame granularity, enough for this case
 * since it's only called once per frame, so can't replace
 * timeGetTime/FAKE_GetTickCount entirely
 */
static int64_t timeGetUsec()
{
	if (total_usec == -1)
		return timeGetTime() * 1000;
	else
		return total_usec;
}

void Timer_Init(void)
{
	tick = timeGetUsec();
}

void Timer_Reset(void)
{
	tick = timeGetUsec();
}

uint16_t Timer_GetCount(void)
{
	int64_t ticknow = timeGetUsec();
	int64_t dif = ticknow-tick;
	int64_t TIMEBASE = (int64_t)((CRTC_Regs[0x29]&0x10)?VSYNC_HIGH:VSYNC_NORM);

	/*timercnt += dif*10000;*/
	timercnt += dif*10;  /* switch from msec to usec */
	tick = ticknow;
	if ( timercnt>=TIMEBASE ) {
//		timercnt = 0;
		timercnt -= TIMEBASE;
		if ( timercnt>=(TIMEBASE*2) ) timercnt = 0;
		return 1;
	} else
		return 0;
}
