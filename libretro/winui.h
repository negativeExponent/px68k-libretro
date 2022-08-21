#ifndef _winx68k_winui_h
#define _winx68k_winui_h

#include <stdint.h>
#include "common.h"

extern	uint8_t	Debug_Text, Debug_Grp, Debug_Sp;
extern	uint32_t	LastClock[4];

extern char cur_dir_str[];
extern int32_t cur_dir_slen;
extern int32_t speedup_joy[0xff];

void WinUI_Init(void);
int32_t WinUI_Menu(int32_t first);
float WinUI_get_vkscale(void);
void send_key(void);

#define WUM_MENU_END 1
#define WUM_EMU_QUIT 2

enum MenuState {ms_key, ms_value, ms_file, ms_hwjoy_set};

#define MFL_MAX 4000

struct menu_flist {
	char name[MFL_MAX][MAX_PATH];
	char type[MFL_MAX];
	char dir[4][MAX_PATH];
	int32_t ptr;
	int32_t num;
	int32_t y;
	int32_t stack[2][MFL_MAX];
	int32_t stackptr;
};

extern char menu_item_key[][15];
extern char menu_items[][15][30];

int32_t WinUI_get_drv_num(int32_t key);

#ifndef _winx68k_gtkui_h
#define _winx68k_gtkui_h
#endif //winx68k_gtkui_h
#endif //winx68k_winui_h
