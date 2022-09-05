#ifndef _WINX68K_JOY_H
#define _WINX68K_JOY_H

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

#endif /* _WINX68K_JOY_H */
