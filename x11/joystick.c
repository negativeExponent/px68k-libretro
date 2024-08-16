/* JOYSTICK.C - joystick support for WinX68k */

#include "common.h"
#include "joystick.h"
#include "keyboard.h"
#include "prop.h"
#include "winui.h"

#include <libretro.h>
extern retro_input_state_t input_state_cb;
extern uint32_t libretro_supports_input_bitmasks;

#ifndef MAX_BUTTON
#define MAX_BUTTON 32
#endif

uint8_t joy[2];
uint8_t JoyKeyState;
uint8_t JoyKeyState0;
uint8_t JoyKeyState1;

static uint8_t JoyState0[2];
static uint8_t JoyState1[2];
static uint8_t JoyPortData[2];

/* This stores whether the buttons were down. This avoids key repeats. */
static uint8_t JoyDownState0;

/* This stores whether the buttons were up. This avoids key repeats. */
static uint8_t JoyUpState0;

void Joystick_Init(void)
{
	joy[0]         = 1; /* activate JOY1 */
	joy[1]         = 1; /* activate JOY2 */
	JoyKeyState    = 0;
	JoyKeyState0   = 0;
	JoyKeyState1   = 0;
	JoyState0[0]   = 0xff;
	JoyState0[1]   = 0xff;
	JoyState1[0]   = 0xff;
	JoyState1[1]   = 0xff;
	JoyPortData[0] = 0;
	JoyPortData[1] = 0;
}

void Joystick_Cleanup(void) { }

uint8_t FASTCALL Joystick_Read(uint8_t num)
{
	uint8_t joynum = num;
	uint8_t ret0 = 0xff, ret1 = 0xff, ret;

	if (Config.JoySwap)
		joynum ^= 1;
	if (joy[num])
	{
		ret0 = JoyState0[num];
		ret1 = JoyState1[num];
	}

	if (Config.JoyKey)
	{
		if ((Config.JoyKeyJoy2) && (num == 1))
			ret0 ^= JoyKeyState;
		else if ((!Config.JoyKeyJoy2) && (num == 0))
			ret0 ^= JoyKeyState;
	}

	ret = ((~JoyPortData[num]) & ret0) | (JoyPortData[num] & ret1);

	return ret;
}

void FASTCALL Joystick_Write(uint8_t num, uint8_t data)
{
	if ((num == 0) || (num == 1))
		JoyPortData[num] = data;
}

/* Menu navigation related vars */
#define RATE  3  /* repeat rate */
#define DELAY 30 /* delay before 1st repeat */

static int get_px68k_input_bitmasks(int port)
{
	return input_state_cb(port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
}

static int get_px68k_input(int port)
{
	int i   = 0;
	int res = 0;

	for (i = 0; i <= RETRO_DEVICE_ID_JOYPAD_R3; i++)
		res |= input_state_cb(port, RETRO_DEVICE_JOYPAD, 0, i) ? (1 << i) : 0;

	return res;
}

void FASTCALL Joystick_Update(int is_menu, int key, int port)
{
	static uint8_t pre_ret0 = 0xff;

	uint8_t ret0 = 0xff;
	uint8_t ret1 = 0xff;
	int input    = 0;

	if (libretro_supports_input_bitmasks)
		input = get_px68k_input_bitmasks(port);
	else
		input = get_px68k_input(port);

	/* D-Pad */
	if (input & (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT))
		ret0 &= ~JOY_RIGHT;

	if (input & (1 << RETRO_DEVICE_ID_JOYPAD_LEFT))
		ret0 &= ~JOY_LEFT;

	if (input & (1 << RETRO_DEVICE_ID_JOYPAD_UP))
		ret0 &= ~JOY_UP;

	if (input & (1 << RETRO_DEVICE_ID_JOYPAD_DOWN))
		ret0 &= ~JOY_DOWN;

	/* disallow invalid button combinations */
	{
		uint8_t mask = (JOY_LEFT | JOY_RIGHT);
		if ((ret0 & ~mask) == mask)
			ret0 &= ~mask;
		mask = (JOY_UP | JOY_DOWN);
		if ((ret0 & ~mask) == mask)
			ret0 &= ~mask;
	}

	/* Buttons */
	switch (Config.joyType[port])
	{
	case PAD_2BUTTON:
		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_A))
			ret0 &= ~(Config.VbtnSwap ? JOY_TRG1 : JOY_TRG2);

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_B))
			ret0 &= ~(Config.VbtnSwap ? JOY_TRG2 : JOY_TRG1);

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_X))
			ret0 &= ~(Config.VbtnSwap ? JOY_TRG2 : JOY_TRG1);

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_Y))
			ret0 &= ~(Config.VbtnSwap ? JOY_TRG1 : JOY_TRG2);

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_START))
			ret0 &= ~JOY_START;

		if (!Config.P1SelectMap)
			if (input & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT))
				ret0 &= ~JOY_SELECT;
		break;

	case PAD_CPSF_MD:
		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_A))
			ret0 &= ~JOY_TRG1;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_B))
			ret0 &= ~JOY_TRG2;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_X))
			ret1 &= ~JOY_TRG4;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_Y))
			ret1 &= ~JOY_TRG3;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_L))
			ret1 &= ~JOY_TRG5;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_R))
			ret1 &= ~JOY_TRG8;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_START))
			ret1 &= ~JOY_TRG6;

		if (!Config.P1SelectMap)
			if (input & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT))
				ret1 &= ~JOY_TRG7;
		break;

	case PAD_CPSF_SFC:
		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_A))
			ret0 &= ~JOY_TRG2;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_B))
			ret0 &= ~JOY_TRG1;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_X))
			ret1 &= ~JOY_TRG3;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_Y))
			ret1 &= ~JOY_TRG4;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_L))
			ret1 &= ~JOY_TRG8;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_R))
			ret1 &= ~JOY_TRG5;

		if (input & (1 << RETRO_DEVICE_ID_JOYPAD_START))
			ret1 ^= JOY_TRG6;

		if (!Config.P1SelectMap)
			if (input & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT))
				ret1 ^= JOY_TRG7;
		break;
	}

	JoyDownState0 = ~(ret0 ^ pre_ret0) | ret0;
	JoyUpState0   = (ret0 ^ pre_ret0) & ret0;
	pre_ret0      = ret0;

	JoyState0[port] = ret0;
	JoyState1[port] = ret1;

	if (is_menu)
	{
		/* input overrides section during Menu mode for faster menu browsing
	 	 * by pressing and holding key or button aka turbo mode */

		static int repeat_rate, repeat_delay;
		static uint8_t last_inbuf;
		uint8_t inbuf  = ((ret0 ^ 0xff) | key);
		int i;

		if ((inbuf & (JOY_LEFT | JOY_RIGHT)) == (JOY_LEFT | JOY_RIGHT))
			inbuf &= ~(JOY_LEFT | JOY_RIGHT);
		if ((inbuf & (JOY_UP | JOY_DOWN)) == (JOY_UP | JOY_DOWN))
			inbuf &= ~(JOY_UP | JOY_DOWN);

		if (last_inbuf != inbuf)
		{
			last_inbuf    = inbuf;
			repeat_delay  = DELAY;
			repeat_rate   = 0;
			JoyDownState0 = (inbuf ^ 0xff);
		}
		else
		{
			if (repeat_delay)
				repeat_delay--;
			if (repeat_delay == 0)
			{
				if (repeat_rate)
					repeat_rate--;
				if (repeat_rate == 0)
				{
					repeat_rate = RATE;
					for (i = 0; i < 4; i++)
					{
						/* which direction? UP/DOWN/LEFT/RIGHT */
						uint8_t tmp = (1 << i);
						if ((inbuf & tmp) == tmp)
							JoyDownState0 &= ~tmp;
					}
				}
			}
		}
	}
}

uint8_t get_joy_downstate(void) { return JoyDownState0; }
void reset_joy_downstate(void) { JoyDownState0 = 0xff; }

uint8_t get_joy_upstate(void) { return JoyUpState0; }
void reset_joy_upstate(void) { JoyUpState0 = 0x00; }
