#ifndef _X68K_WINUI_H
#define _X68K_WINUI_H

extern uint8_t Debug_Text, Debug_Grp, Debug_Sp;

extern char cur_dir_str[];
extern int cur_dir_slen;

void WinUI_Init(void);
int WinUI_Menu(int first);
float WinUI_get_vkscale(void);

#define WUM_MENU_END 1
#define WUM_EMU_QUIT 2

typedef enum
{
	ms_key,
	ms_value,
	ms_file,
	ms_hwjoy_set
} MenuState;

#define MFL_MAX 4000

struct menu_flist
{
	char name[MFL_MAX][MAX_PATH];
	char type[MFL_MAX];
	char dir[4][MAX_PATH];
	int ptr;
	int num;
	int y;
	int stack[2][MFL_MAX];
	int stackptr;
};

extern char menu_item_key[][15];
extern char menu_items[][15][30];

int WinUI_get_drv_num(int key);

#endif /* _X68K_WINUI_H */
