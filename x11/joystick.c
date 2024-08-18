/* JOYSTICK.C - joystick support for WinX68k */

#include "common.h"
#include "joystick.h"
#include "keyboard.h"
#include "prop.h"
#include "winui.h"

#include <libretro.h>
extern retro_input_state_t input_state_cb;
extern uint32_t libretro_supports_input_bitmasks;

/* Input from keyboard when Key2Joy is enabled */
uint8_t JoyKeyState;

/* input data from controllers */
static uint8_t JoyState[2][12];

/* joystick control data */
static uint8_t JoyPortData[2];

/* This stores whether the buttons were down. This avoids key repeats. */
static uint8_t JoyDownState0;

/* This stores whether the buttons were up. This avoids key repeats. */
static uint8_t JoyUpState0;

/* CyberStick Analog/Digital */

#define CYBERA_LATENCY 3

/* Cyberstick analog sequence counter */
static uint8_t JoyCyberCounter[2];

/* Cyberstick analog internal latency */
static uint8_t JoyCyberLatency[2];

static void JoyCyber_Init(int num)
{
	int i;

	for (i = 0; i < 12; i++)
	{
		/* ACK, L/H, button data */
		if (i & 1)
		{
			JoyState[num][i] = 0xbf;
		}
		else
		{
			JoyState[num][i] = 0x9f;
		}

		if ((i >= 2) && (i <= 5))
		{
			/* set analog data H to 7 */
			JoyState[num][i] &= 0xf7;
		}
	}

	JoyCyberCounter[num] = 0;
	JoyCyberLatency[num] = CYBERA_LATENCY;
}

static uint8_t JoyCyberA_Read(int num)
{
	uint8_t ret = 0xff;

	switch (JoyCyberCounter[num])
	{
	case 0:
		/* data start - waits a bit after REQ */
		/* Suppose to take about 50us to respond, using counters here instead */
		ret = 0xff;
		break;
	case 1:
		/* button A, B, C, D */
		ret = JoyState[num][0];
		break;
	case 2:
		/* button E1, E2, F (Start), G (Select) */
		ret = JoyState[num][1];
		break;
	case 3:
		/* Y axis, b4-b7 */
		ret = JoyState[num][2];
		break;
	case 4:
		/* X axis, b4-b7 */
		ret = JoyState[num][3];
		break;
	case 5:
		/* Throttle Up/Down, b4-b7 */
		ret = JoyState[num][4];
		break;
	case 6:
		/* reserved */
		ret = JoyState[num][5];
		break;
	case 7:
		/* Y axis, b0-b3 */
		ret = JoyState[num][6];
		break;
	case 8:
		/* X axis, b0-b3 */
		ret = JoyState[num][7];
		break;
	case 9:
		/* Throttle Up/Down, b0-b3 */
		ret = JoyState[num][8];
		break;
	case 10:
		/* reserved */
		ret = JoyState[num][9];
		break;
	case 11:
		/* mini buttons A/B on lever */
		ret = JoyState[num][10];
		break;
	case 12:
		ret = JoyState[num][11];
		break;
	default:
		ret = 0xff;
		break;
	}

	/* p6logd("count = %2d state = %d ret = %02x\n", JoyCyberLatency[num], JoyCyberCounter[num], ret); */

	/* decrement internal counter */
	JoyCyberLatency[num]--;

	if (JoyCyberLatency[num] == 0)
	{
		if (JoyCyberCounter[num] >= 13)
		{
			ret = 0xff;
		}
		else
		{
			/* next data cycle */
			JoyCyberCounter[num]++;

			/* reset internal counter */
			JoyCyberLatency[num] = CYBERA_LATENCY;
		}
	}

	return ret;
}

static void JoyCyberA_Write(int num, uint8_t data)
{
	if ((data == 0) && (JoyPortData[num] == 0xff))
	{
		/* reset data acquisition cycle */
		JoyCyberCounter[num] = 0;

		/* initialize internal latenct */
		JoyCyberLatency[num] = CYBERA_LATENCY;
	}
	JoyPortData[num] = data;
}

/* Cyber Stick end */

void Joystick_Init(void)
{
	int num;

	JoyKeyState    = 0;

	JoyPortData[0] = 0;
	JoyPortData[1] = 0;

	for (num = 0; num < MAX_PORT; num++)
	{
		switch (Config.joyType[num])
		{
		case PAD_CYBERSTICK_ANALOG:
			JoyCyber_Init(num);
			break;
		
		default: /* 2Button/CPSF/CPSFMD/CyberstickDigital */
			memset(&JoyState[num], 0xff, sizeof(JoyState[num]));
			break;
		}
	}
}

void Joystick_Cleanup(void) { }

uint8_t FASTCALL Joystick_Read(uint8_t num)
{
	uint8_t joynum = num;
	uint8_t ret0 = 0xff;

	switch (Config.joyType[num])
	{
	case PAD_CYBERSTICK_ANALOG:
		return JoyCyberA_Read(num);
	
	case PAD_CPSF_MD:
	case PAD_CPSF_SFC:
	case PAD_CYBERSTICK_DIGITAL:
		if (JoyPortData[num] == 0xff)
		{
			return JoyState[num][1];
		}
		return JoyState[num][0];

	case PAD_2BUTTON:
		if (Config.JoySwap)
			joynum ^= 1;

		ret0 = JoyState[joynum][0];

		if (Config.JoyKey)
		{
			if ((Config.JoyKeyJoy2) && (num == 1))
				ret0 ^= JoyKeyState;
			else if ((!Config.JoyKeyJoy2) && (num == 0))
				ret0 ^= JoyKeyState;
		}

		if (JoyPortData[num] == 0xff)
		{
			return 0xff;
		}

		return ret0;
	}

	return 0xff;
}

void FASTCALL Joystick_Write(uint8_t num, uint8_t data)
{
	switch (Config.joyType[num])
	{
	case PAD_CYBERSTICK_ANALOG:
		JoyCyberA_Write(num, data);
		break;
	
	case PAD_2BUTTON:
	case PAD_CPSF_SFC:
	case PAD_CPSF_MD:
	case PAD_CYBERSTICK_DIGITAL:	
		JoyPortData[num] = data;
		break;
	}
}

/* Menu navigation related vars */
#define RATE  3  /* repeat rate */
#define DELAY 30 /* delay before 1st repeat */

static int get_px68k_input_bitmasks(int port)
{
	return (input_state_cb(port,
		RETRO_DEVICE_JOYPAD, 0,
	    RETRO_DEVICE_ID_JOYPAD_MASK));
}

static int get_px68k_input(int port)
{
	int i   = 0;
	int res = 0;

	for (i = 0; i <= RETRO_DEVICE_ID_JOYPAD_R3; i++)
	{
		res |= input_state_cb(port,
			RETRO_DEVICE_JOYPAD,0, i) ? (1 << i) : 0;
	}

	return res;
}

void FASTCALL Joystick_Update(int is_menu, int key, int port)
{
#define BIT(x) (1 << (x))
#define BUTTON(x) (input & BIT(x))

	static uint8_t pre_ret0 = 0xff;

	uint8_t ret0      = 0xff;
	uint8_t ret1      = 0xff;

	int32_t analog_x = 0;
	int32_t analog_y = 0;
	int32_t analog_z = 0;
	int32_t input    = 0;

	if (libretro_supports_input_bitmasks)
		input = get_px68k_input_bitmasks(port);
	else
		input = get_px68k_input(port);
	
	/* disallow invalid button combinations */
	{
		int32_t mask = (BIT(RETRO_DEVICE_ID_JOYPAD_RIGHT) | BIT(RETRO_DEVICE_ID_JOYPAD_LEFT));
		if ((input & mask) == mask)
		{
			input &= ~mask;
		}
		mask = (BIT(RETRO_DEVICE_ID_JOYPAD_UP) | BIT(RETRO_DEVICE_ID_JOYPAD_DOWN));
		if ((input & mask) == mask)
		{
			input &= ~mask;
		}
	}

	/* D-Pad button data for menu handling */
	if (BUTTON(RETRO_DEVICE_ID_JOYPAD_RIGHT))
	{
		ret0 &= ~JOY_RIGHT;
	}

	if (BUTTON(RETRO_DEVICE_ID_JOYPAD_LEFT))
	{
		ret0 &= ~JOY_LEFT;
	}

	if (BUTTON(RETRO_DEVICE_ID_JOYPAD_UP))
	{
		ret0 &= ~JOY_UP;
	}

	if (BUTTON(RETRO_DEVICE_ID_JOYPAD_DOWN))
	{
		ret0 &= ~JOY_DOWN;
	}

	if (BUTTON(RETRO_DEVICE_ID_JOYPAD_A))
	{
		ret0 &= ~(Config.VbtnSwap ? JOY_TRG1 : JOY_TRG2);
	}

	if (BUTTON(RETRO_DEVICE_ID_JOYPAD_B))
	{
		ret0 &= ~(Config.VbtnSwap ? JOY_TRG2 : JOY_TRG1);
	}

	switch (Config.joyType[port])
	{
	case PAD_2BUTTON:
		JoyState[port][0] = 0xff;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_RIGHT))
		{
			JoyState[port][0] &= ~JOY_RIGHT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_LEFT))
		{
			JoyState[port][0] &= ~JOY_LEFT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_UP))
		{
			JoyState[port][0] &= ~JOY_UP;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_DOWN))
		{
			JoyState[port][0] &= ~JOY_DOWN;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_A))
		{
			JoyState[port][0] &= ~(Config.VbtnSwap ? JOY_TRG1 : JOY_TRG2);
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_B))
		{
			JoyState[port][0] &= ~(Config.VbtnSwap ? JOY_TRG2 : JOY_TRG1);
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_X))
		{
			JoyState[port][0] &= ~(Config.VbtnSwap ? JOY_TRG2 : JOY_TRG1);
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_Y))
		{
			JoyState[port][0] &= ~(Config.VbtnSwap ? JOY_TRG1 : JOY_TRG2);
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_START))
		{
			JoyState[port][0] &= ~JOY_START;
		}

		if (!Config.P1SelectMap)
		{
			if (BUTTON(RETRO_DEVICE_ID_JOYPAD_SELECT))
			{
				JoyState[port][0] &= ~JOY_SELECT;
			}
		}
		break;

	case PAD_CPSF_MD:
		/* data[0] Right, Left, Up, Down, A, B */
		JoyState[port][0] = 0xff;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_RIGHT))
		{
			JoyState[port][0] &= ~JOY_RIGHT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_LEFT))
		{
			JoyState[port][0] &= ~JOY_LEFT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_UP))
		{
			JoyState[port][0] &= ~JOY_UP;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_DOWN))
		{
			JoyState[port][0] &= ~JOY_DOWN;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_A))
		{
			JoyState[port][0] &= ~CPSFMD_A;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_B))
		{
			JoyState[port][0] &= ~CPSFMD_B;
		}

		/* data[1] C, X, T, Z, Start, Mode */
		JoyState[port][1] = 0xff;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_X))
		{
			JoyState[port][1] &= ~CPSFMD_C;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_Y))
		{
			JoyState[port][1] &= ~CPSFMD_X;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_L))
		{
			JoyState[port][1] &= ~CPSFMD_Y;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_R))
		{
			JoyState[port][1] &= ~CPSFMD_Z;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_START))
		{
			JoyState[port][1] &= ~CPSFMD_START;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_SELECT))
		{
			JoyState[port][1] &= ~CPSFMD_MODE;
		}
		break;

	case PAD_CPSF_SFC:
		/* data[0] Right, Left, Up, Down, A, B */
		JoyState[port][0] = 0xff;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_RIGHT))
		{
			JoyState[port][0] &= ~JOY_RIGHT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_LEFT))
		{
			JoyState[port][0] &= ~JOY_LEFT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_UP))
		{
			JoyState[port][0] &= ~JOY_UP;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_DOWN))
		{
			JoyState[port][0] &= ~JOY_DOWN;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_A))
		{
			JoyState[port][0] &= ~CPSF_A;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_B))
		{
			JoyState[port][0] &= ~CPSF_B;
		}

		/* data[1] X, Y, L, R, Start, Select */
		JoyState[port][1] = 0xff;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_X))
		{
			JoyState[port][1] &= ~CPSF_X;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_Y))
		{
			JoyState[port][1] &= ~CPSF_Y;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_L))
		{
			JoyState[port][1] &= ~CPSF_L;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_R))
		{
			JoyState[port][1] &= ~CPSF_R;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_START))
		{
			JoyState[port][1] &= ~CPSF_START;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_SELECT))
		{
			JoyState[port][1] &= ~CPSF_SELECT;
		}
		break;

	case PAD_CYBERSTICK_DIGITAL:
		/* data[0] Right, Left, Up, Down, A, B */
		JoyState[port][0] = 0xff;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_RIGHT))
		{
			JoyState[port][0] &= ~JOY_RIGHT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_LEFT))
		{
			JoyState[port][0] &= ~JOY_LEFT;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_UP))
		{
			JoyState[port][0] &= ~JOY_UP;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_DOWN))
		{
			JoyState[port][0] &= ~JOY_DOWN;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_A))
		{
			JoyState[port][0] &= ~CYBERD_A;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_B))
		{
			JoyState[port][0] &= ~CYBERD_B;
		}

		/* data[1]: buttons C, D, E1, E2 */
		JoyState[port][1] = 0xff;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_X))
		{
			JoyState[port][1] &= ~CYBERD_C;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_Y))
		{
			JoyState[port][1] &= ~CYBERD_D;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_L))
		{
			JoyState[port][1] &= ~CYBERD_E1;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_R))
		{
			JoyState[port][1] &= ~CYBERD_E2;
		}

		/* EXTRA: for compatiblity. not normally mapped on CyberStick Digital */
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_START))
		{
			JoyState[port][0] &= ~JOY_START;
		}

		if (!Config.P1SelectMap)
		{
			if (BUTTON(RETRO_DEVICE_ID_JOYPAD_SELECT))
			{
				JoyState[port][0] &= ~JOY_SELECT;
			}
		}
		break;

	case PAD_CYBERSTICK_ANALOG:
#if 0
		analog_z = input_state_cb(port, RETRO_DEVICE_ANALOG,
			RETRO_DEVICE_INDEX_ANALOG_BUTTON,
		    RETRO_DEVICE_ID_JOYPAD_L2);

		if (analog_z == 0)
		{
			if (input_state_cb(port, RETRO_DEVICE_JOYPAD, 0,
			                   RETRO_DEVICE_ID_JOYPAD_L2))
			{
				analog_z = 0x8000;
			}
			else
			{
				analog_z = 0;
			}
		}
#endif
		analog_x = input_state_cb(port,
			RETRO_DEVICE_ANALOG,
			RETRO_DEVICE_INDEX_ANALOG_LEFT,
			RETRO_DEVICE_ID_ANALOG_X);

		analog_y = input_state_cb(port,
			RETRO_DEVICE_ANALOG,
			RETRO_DEVICE_INDEX_ANALOG_LEFT,
			RETRO_DEVICE_ID_ANALOG_Y);

		analog_z = input_state_cb(port,
			RETRO_DEVICE_ANALOG,
			RETRO_DEVICE_INDEX_ANALOG_RIGHT,
			RETRO_DEVICE_ID_ANALOG_Y);

		analog_y += 0x8000;
		analog_y >>= 8;

		JoyState[port][2] &= 0xf0;
		JoyState[port][2] |= (analog_y >> 4) & 0X0f;
		JoyState[port][6] &= 0xf0;
		JoyState[port][6] |= analog_y & 0x0f;

		if (analog_y < 30)
		{
			ret0 &= ~JOY_UP;
		}
		else if (analog_y > (255 - 30))
		{
			ret0 &= ~JOY_DOWN;
		}

		analog_x += 0x8000;
		analog_x >>= 8;

		JoyState[port][3] &= 0xf0;
		JoyState[port][3] |= (analog_x >> 4) & 0X0f;
		JoyState[port][7] &= 0xf0;
		JoyState[port][7] |= analog_x & 0x0f;

		if (analog_x < 30)
		{
			ret0 &= ~JOY_LEFT;
		}
		else if (analog_x > (255 - 30))
		{
			ret0 &= ~JOY_RIGHT;
		}

		analog_z = 0 - analog_z;
		analog_z += 0x8000;
		analog_z >>= 8;

		JoyState[port][4] &= 0xf0;
		JoyState[port][4] |= (analog_z >> 4) & 0X0f;
		JoyState[port][8] &= 0xf0;
		JoyState[port][8] |= analog_z & 0x0f;

		JoyState[port][5] &= 0xf0;
		JoyState[port][9] &= 0xf0;

		/* data[0]: buttons A, B, C, D */
		/* data[10]: mini buttons A, B on lever */
		/* ret0 is cached keys for menu handling */
		JoyState[port][0]  |= 0x0f;
		JoyState[port][10] &= 0xf0;
		JoyState[port][10] |= 0x0f;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_A))
		{
			JoyState[port][0] &= ~CYBERA_A;
			JoyState[port][10] &= ~CYBERA_A;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_B))
		{
			JoyState[port][0] &= ~CYBERA_B;
			JoyState[port][10] &= ~CYBERA_B;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_X))
		{
			JoyState[port][0] &= ~CYBERA_C;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_Y))
		{
			JoyState[port][0] &= ~CYBERA_D;
		}

		/* data[1]: buttons E1, E2, F (Start), G (Select) */
		JoyState[port][1] |= 0x0f;
		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_L))
		{
			JoyState[port][1] &= ~CYBERA_E1;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_R))
		{
			JoyState[port][1] &= ~CYBERA_E2;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_START))
		{
			JoyState[port][1] &= ~CYBERA_START;
		}

		if (BUTTON(RETRO_DEVICE_ID_JOYPAD_SELECT))
		{
			JoyState[port][1] &= ~CYBERA_SELECT;
		}
	}

	JoyDownState0 = ~(ret0 ^ pre_ret0) | ret0;
	JoyUpState0   = (ret0 ^ pre_ret0) & ret0;
	pre_ret0      = ret0;

#undef BIT
#undef BUTTON

	if (is_menu)
	{
		/* input overrides section during Menu mode for faster menu browsing
		 * by pressing and holding key or button aka turbo mode */

		static int repeat_rate, repeat_delay;
		static uint8_t last_inbuf;
		uint8_t inbuf = ((ret0 ^ 0xff) | key);
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

uint8_t get_joy_downstate(void)
{
	return JoyDownState0;
}
void reset_joy_downstate(void)
{
	JoyDownState0 = 0xff;
}

uint8_t get_joy_upstate(void)
{
	return JoyUpState0;
}
void reset_joy_upstate(void)
{
	JoyUpState0 = 0x00;
}
