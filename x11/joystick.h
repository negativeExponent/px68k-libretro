#ifndef _X68K_JOY_H
#define _X68K_JOY_H

#define MAX_PORT     2

#define PAD_2BUTTON  0
#define PAD_CPSF_MD  1
#define PAD_CPSF_SFC 2
#define PAD_CYBERSTICK_ANALOG 3
#define PAD_CYBERSTICK_DIGITAL 4

/* standard controller map */
/* used for menu navigation as well */

/* data port 0 */
#define JOY_UP          0x01
#define JOY_DOWN        0x02
#define JOY_LEFT        0x04
#define JOY_RIGHT       0x08
#define JOY_TRG2        0x20
#define JOY_TRG1        0x40
/* button combination for start/select button */
#define JOY_SELECT      0x03 /* up + down */
#define JOY_START       0x0c /* left + right */

/* CPSF_SFC */
/* data port 0 */
#define CPSF_A          0x20
#define CPSF_B          0x40
/* data port 1 */
#define CPSF_X          0x04
#define CPSF_Y          0x02
#define CPSF_L          0x20
#define CPSF_R          0x01
#define CPSF_START      0x40
#define CPSF_SELECT     0x08

/* CPSF_MD */
/* data port 0 */
#define CPSFMD_A          0x20
#define CPSFMD_B          0x40
/* data port 1 */
#define CPSFMD_C          0x20
#define CPSFMD_X          0x04
#define CPSFMD_Y          0x02
#define CPSFMD_Z          0x01
#define CPSFMD_START      0x40
#define CPSFMD_MODE       0x08

/* Cyberstick Analog button map */
/* data port 0 */
#define CYBERA_A        0x08
#define CYBERA_B        0x04
#define CYBERA_C        0x02
#define CYBERA_D        0x01
/* data port 1 */
#define CYBERA_E1       0x08
#define CYBERA_E2       0x04
#define CYBERA_START    0x02 /* F */
#define CYBERA_SELECT   0x01 /* G */

/* Cyberstick Analog button map */
/* data port 0 */
#define CYBERD_A        0x20
#define CYBERD_B        0x40
/* data port 1 */
#define CYBERD_C        0x04
#define CYBERD_D        0x08
#define CYBERD_E1       0x20
#define CYBERD_E2       0x40

void Joystick_Init(void);
void Joystick_Cleanup(void);
uint8_t FASTCALL Joystick_Read(uint8_t num);
void FASTCALL Joystick_Write(uint8_t num, uint8_t data);

void FASTCALL Joystick_Update(int is_menu, int, int port);

uint8_t get_joy_downstate(void);
void reset_joy_downstate(void);
uint8_t get_joy_upstate(void);
void reset_joy_upstate(void);

extern uint8_t JoyKeyState;

#endif /* _X68K_JOY_H */
