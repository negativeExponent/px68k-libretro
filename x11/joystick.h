#ifndef _X68K_JOY_H
#define _X68K_JOY_H

#define PAD_2BUTTON  0
#define PAD_CPSF_MD  1
#define PAD_CPSF_SFC 2

#define JOY_UP    0x01
#define JOY_DOWN  0x02
#define JOY_LEFT  0x04
#define JOY_RIGHT 0x08
#define JOY_TRG2  0x20
#define JOY_TRG1  0x40

#define JOY_TRG5 0x01
#define JOY_TRG4 0x02
#define JOY_TRG3 0x04
#define JOY_TRG7 0x08
#define JOY_TRG8 0x20
#define JOY_TRG6 0x40

#define JOY_SELECT (JOY_UP | JOY_DOWN)
#define JOY_START  (JOY_LEFT | JOY_RIGHT)

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
