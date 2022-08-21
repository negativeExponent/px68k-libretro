#ifndef _winx68k_mouse
#define _winx68k_mouse

#include <stdint.h>
#include "common.h"

extern	int32_t	MousePosX;
extern	int32_t	MousePosY;
extern	uint8_t	MouseStat;
extern	uint8_t	MouseSW;

void Mouse_Init(void);
void Mouse_Event(int32_t wparam, float dx, float dy);
void Mouse_SetData(void);
void Mouse_StartCapture(int32_t flag);
void Mouse_ChangePos(void);

#endif //_winx68k_mouse
