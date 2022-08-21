// ---------------------------------------------------------------------------
//	FM sound generator common timer module
//	Copyright (C) cisc 1998, 2000.
// ---------------------------------------------------------------------------
//	$fmgen-Id: fmtimer.cpp,v 1.1 2000/09/08 13:45:56 cisc Exp $

#include <stdint.h>
#include "common.h"
#include "headers.h"
#include "fmtimer.h"

using namespace FM;

// ---------------------------------------------------------------------------
//	タイマー制御
//
void Timer::SetTimerControl(uint32_t data)
{
	uint32_t tmp = regtc ^ data;
	regtc = uint8_t(data);
	
	if (data & 0x10) 
		ResetStatus(1);
	if (data & 0x20) 
		ResetStatus(2);

	if (tmp & 0x01)
		timera_count = (data & 1) ? timera : 0;
	if (tmp & 0x02)
		timerb_count = (data & 2) ? timerb : 0;
}

// ---------------------------------------------------------------------------
//	タイマーA 周期設定
//
void Timer::SetTimerA(uint32_t addr, uint32_t data)
{
	uint32_t tmp;
	regta[addr & 1] = uint8_t(data);
	tmp = (regta[0] << 2) + (regta[1] & 3);
	timera = (1024-tmp) * timer_step;
}

// ---------------------------------------------------------------------------
//	タイマーB 周期設定
//
void Timer::SetTimerB(uint32_t data)
{
	timerb = (256-data) * timer_step;
}

// ---------------------------------------------------------------------------
//	タイマー時間処理
//
bool Timer::Count(int32_t us)
{
	bool event = false;

	if (timera_count)
	{
		timera_count -= us << 16;
		if (timera_count <= 0)
		{
			event = true;
			TimerA();

			while (timera_count <= 0)
				timera_count += timera;
			
			if (regtc & 4)
				SetStatus(1);
		}
	}
	if (timerb_count)
	{
		timerb_count -= us << 12;
		if (timerb_count <= 0)
		{
			event = true;
			while (timerb_count <= 0)
				timerb_count += timerb;
			
			if (regtc & 8)
				SetStatus(2);
		}
	}
	return event;
}

// ---------------------------------------------------------------------------
//	次にタイマーが発生するまでの時間を求める
//
int32_t Timer::GetNextEvent()
{
	uint32_t ta = ((timera_count + 0xffff) >> 16) - 1;
	uint32_t tb = ((timerb_count + 0xfff) >> 12) - 1;
	return (ta < tb ? ta : tb) + 1;
}

// ---------------------------------------------------------------------------
//	タイマー基準値設定
//
void Timer::SetTimerBase(uint32_t clock)
{
	timer_step = int32_t(1000000. * 65536 / clock);
}
