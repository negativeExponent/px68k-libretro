#ifndef _X68K_WINDRAW_H
#define _X68K_WINDRAW_H

#include "winui.h"

extern uint16_t WinDraw_Pal16B, WinDraw_Pal16R, WinDraw_Pal16G;

int WinDraw_Init(void);
void WinDraw_Cleanup(void);
void FASTCALL WinDraw_Draw(void);
void WinDraw_DrawLine(void);
void WinDraw_ChangeSize(void);

int WinDraw_MenuInit(void);
void WinDraw_DrawMenu(MenuState menu_state, int mkey_pos, int mkey_y, int *mval_y);

extern struct menu_flist mfl;

void WinDraw_DrawMenufile(struct menu_flist *mfl);
void WinDraw_ClearMenuBuffer(void);

#endif /* _X68K_WINDRAW_H */
