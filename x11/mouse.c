/*
 * Copyright (c) 2003,2008 NONAKA Kimihiro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "common.h"

#include "mouse.h"
#include "prop.h"

#include "../x68k/scc.h"

static float MouseDX = 0;
static float MouseDY = 0;
static uint8_t MouseStat = 0;
static uint8_t MouseSW = 0;

void Mouse_Init(void)
{
	if (Config.JoyOrMouse)
	{
		Mouse_StartCapture(1);
	}
}

void Mouse_Event(int param, float dx, float dy)
{
	if (MouseSW)
	{
		switch (param)
		{
		case 0:
			MouseDX += dx;
			MouseDY += dy;
			break;
		case 1:
			if (dx != 0)
				MouseStat |= 1;
			else
				MouseStat &= 0xfe;
			break;
		case 2:
			if (dx != 0)
				MouseStat |= 2;
			else
				MouseStat &= 0xfd;
			break;
		default:
			break;
		}
	}
}

/*
 * Mouse Data send to SCC
 */
void Mouse_SetData(void)
{
	int x, y;

	if (MouseSW)
	{
		x = (int)MouseDX;
		y = (int)MouseDY;

		MouseDX = MouseDY = 0;

		MouseSt = MouseStat;

		if (x > 127)
		{
			MouseSt |= 0x10;
			MouseX = 127;
		}
		else if (x < -128)
		{
			MouseSt |= 0x20;
			MouseX = -128;
		}
		else
		{
			MouseX = (int8_t)x;
		}

		if (y > 127)
		{
			MouseSt |= 0x40;
			MouseY = 127;
		}
		else if (y < -128)
		{
			MouseSt |= 0x80;
			MouseY = -128;
		}
		else
		{
			MouseY = (int8_t)y;
		}
	}
	else
	{
		MouseSt = 0;
		MouseX = 0;
		MouseY = 0;
	}
}

/*
 *	Start Capture
 */
void Mouse_StartCapture(int flag)
{
	if (flag && !MouseSW)
	{
		MouseSW = 1;
	}
	else if (!flag && MouseSW)
	{
		MouseSW = 0;
	}
}
