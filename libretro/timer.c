// -----------------------------------------------------------------------
//   55.6fpsキープ用たいまー
// -----------------------------------------------------------------------
#include "common.h"
#include "crtc.h"
#include "mfp.h"

static int64_t	timercnt = 0;
static int64_t	tick = 0;

/* Get elapsed time from libretro frontend by way of its frame time callback,
 * if available. Only provides per frame granularity, enough for this case
 * since it's only called once per frame, so can't replace
 * timeGetTime/FAKE_GetTickCount entirely
 */
static int64_t timeGetUsec()
{
	extern int64_t total_usec;		/* from libretro.c */
	if (total_usec == -1)
		return (int64_t)timeGetTime() * 1000;
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
	int64_t ticknow   = timeGetUsec();
	int64_t dif       = ticknow-tick;
	int64_t TIMEBASE  = (int64_t)((CRTC_Regs[0x29]&0x10)?VSYNC_HIGH:VSYNC_NORM);
	timercnt       += dif*10;  /* switch from msec to usec */
	tick = ticknow;
	if ( timercnt>=TIMEBASE )
	{
		timercnt -= TIMEBASE;
		if ( timercnt>=(TIMEBASE*2) ) timercnt = 0;
		return 1;
	}
	return 0;
}
