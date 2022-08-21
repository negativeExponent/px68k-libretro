#ifndef _winx68k_windraw_h
#define _winx68k_windraw_h

#include <stdint.h>

extern int32_t winx, winy;
extern int32_t winh, winw;
extern uint8_t Draw_ClrMenu;
extern uint16_t FrameCount;
extern uint16_t WinDraw_Pal16B, WinDraw_Pal16R, WinDraw_Pal16G;

extern	uint8_t	Draw_BitMask[800];
extern	uint8_t	Draw_TextBitMask[800];

extern	int32_t	WindowX;
extern	int32_t	WindowY;
extern	int32_t	kbd_x, kbd_y, kbd_w, kbd_h;

void WinDraw_InitWindowSize(uint16_t width, uint16_t height);
int32_t WinDraw_Init(void);
void WinDraw_Cleanup(void);
void WinDraw_Redraw(void);
void FASTCALL WinDraw_Draw(void);
void WinDraw_ShowMenu(int32_t flag);
void WinDraw_DrawLine(void);
void WinDraw_ChangeSize(void);

void WinDraw_StartupScreen(void);
void WinDraw_CleanupScreen(void);

int32_t WinDraw_MenuInit(void);
void WinDraw_DrawMenu(int32_t menu_state, int32_t mkey_pos, int32_t mkey_y, int32_t *mval_y);

extern struct menu_flist mfl;

void WinDraw_DrawMenufile(struct menu_flist *mfl);
void WinDraw_ClearMenuBuffer(void);
void WinDraw_reverse_key(int32_t x, int32_t y);

#endif //winx68k_windraw_h


