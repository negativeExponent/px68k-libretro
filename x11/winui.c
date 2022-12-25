/*
 * Copyright (c) 2003,2008 NONAKA Kimihiro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* -------------------------------------------------------------------------- *
 *  WINUI.C - UI                                                              *
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#include "common.h"

#include "../x68k/fdd.h"
#include "../x68k/irqh.h"
#include "../x68k/sram.h"

#include "dosio.h"
#include "joystick.h"
#include "prop.h"
#include "status.h"
#include "windraw.h"
#include "winui.h"
#include "winx68k.h"

uint8_t Debug_Text = 1, Debug_Grp = 1, Debug_Sp = 1;

char filepath[MAX_PATH] = ".";

char cur_dir_str[MAX_PATH];
int cur_dir_slen;

struct menu_flist mfl;

/***** menu items *****/

#define MENU_NUM    5
#define MENU_WINDOW 7

int mval_y[] = { 0, 0, 0, 0, 0 };

extern void plusyen(char *str, int len);

enum menu_id
{
	M_SYS,
	M_FD0,
	M_FD1,
	M_HD0,
	M_HD1
};

char menu_item_key[][15] = {
	"SYSTEM",
	"FDD0",
	"FDD1",
	"HDD0",
	"HDD1",
	"",
	"",
	"uhyo",
	""
};

/* Max # of characters is 30. */
/* Max # of items including terminater `""' in each line is 15. */
char menu_items[][15][30] = {
	{ "RESET", "NMI RESET", "CLEAR SRAM", "QUIT", "" },
	{ "dummy", "EJECT", "" },
	{ "dummy", "EJECT", "" },
	{ "dummy", "EJECT", "" },
	{ "dummy", "EJECT", "" }
};

static void menu_system(int v);
static void menu_create_flist(int v);

struct _menu_func
{
	void (*func)(int v);
	int imm;
};

struct _menu_func menu_func[] = {
	{menu_system, 0},
	{menu_create_flist, 0},
	{menu_create_flist, 0},
	{menu_create_flist, 0},
	{menu_create_flist, 0}
};

int WinUI_get_drv_num(int key)
{
	char *s = menu_item_key[key];

	if (!strncmp("FDD", s, 3))
	{
		return strcmp("FDD0", s) ? (strcmp("FDD1", s) ? -1 : 1) : 0;
	}
	else
	{
		return strcmp("HDD0", s) ? (strcmp("HDD1", s) ? -1 : 3) : 2;
	}
}

/******************************************************************************
 * init
 ******************************************************************************/
void WinUI_Init(void)
{
	int i;

#ifdef _WIN32
#define CUR_DIR_STR "c:\\"
#else
#define CUR_DIR_STR "/"
#endif

	if (filepath[0] != 0)
		strcpy(cur_dir_str, filepath);
	else
		strcpy(cur_dir_str, CUR_DIR_STR);

	plusyen(cur_dir_str, sizeof(cur_dir_str));
	cur_dir_slen = strlen(cur_dir_str);

#ifdef DEBUG
	p6logd("cur_dir_str %s %d\n", cur_dir_str, cur_dir_slen);
#endif

	for (i = 0; i < 4; i++)
	{
		strcpy(mfl.dir[i], cur_dir_str);
	}
}

float VKey_scale[] = { 3.0, 2.5, 2.0, 1.5, 1.25, 1.0 };

float WinUI_get_vkscale(void)
{
	int n = Config.VkeyScale;

	/* failsafe against invalid values */
	if (n < 0 || (unsigned long)n >= sizeof(VKey_scale) / sizeof(float))
	{
		return 1.0;
	}
	return VKey_scale[n];
}

static MenuState menu_state = ms_key;
int mkey_y     = 0;
int mkey_pos   = 0;

static void menu_system(int v)
{
	switch (v)
	{
	case 1:
		IRQH_Int(7, NULL);
		break;
	case 2:
		SRAM_Clear();
		/* fall through */
	case 0:
		WinX68k_Reset(1);
		break;
	case 3: /* QUIT */
		return;
	}
	mval_y[M_SYS] = 0;
}

static void upper(char *s)
{
	while (*s != '\0')
	{
		if (*s >= 'a' && *s <= 'z')
		{
			*s = 'A' + *s - 'a';
		}
		s++;
	}
}

/* exchange 2 values in mfl list */
static void switch_mfl(int a, int b)
{
	char name_tmp[MAX_PATH];
	char type_tmp;

	strcpy(name_tmp, mfl.name[a]);
	type_tmp = mfl.type[a];

	strcpy(mfl.name[a], mfl.name[b]);
	mfl.type[a] = mfl.type[b];

	strcpy(mfl.name[b], name_tmp);
	mfl.type[b] = type_tmp;
}

#ifdef __LIBRETRO__
extern char slash;
extern char base_dir[2048];
#endif

static void menu_create_flist(int v)
{
	int drv;
	int i, a;
	DIRH *dp;

	/* file extension of FD image */
	char support[] = "D8888DHDMDUP2HDDIMXDFIMG";

	drv = WinUI_get_drv_num(mkey_y);

	if (drv < 0)
	{
		return;
	}

	/* set current directory when FDD is ejected */
	if (v == 1)
	{
		if (drv < 2)
		{
			FDD_EjectFD(drv);
			Config.FDDImage[drv][0] = '\0';
		}
		else
		{
			Config.HDImage[drv - 2][0] = '\0';
		}
		strcpy(mfl.dir[drv], cur_dir_str);
		return;
	}

	if (drv >= 2)
	{
		strcpy(support, "HDF");
	}

	/* This routine gets file lists. */
	dp = wrap_vfs_opendir(mfl.dir[drv]);

	/* xxx check if dp is null... */
	if (!dp)
	{
		char tmp[PATH_MAX];
		/* failed to open StartDir, use rom folder as default */
		/* TODO: check for path more early */
		p6logd("Error opening StartDir, using rom path instead...\n");
		sprintf(tmp, "%s%c", base_dir, slash);
		strcpy(mfl.dir[drv], tmp);
		/* re-open folder */
		dp = wrap_vfs_opendir(mfl.dir[drv]);
	}

#ifdef DEBUG
	p6logd("*** drv:%d ***** %s \n", drv, mfl.dir[drv]);
#endif

	/* xxx You can get only MFL_MAX files. */
	for (i = 0; i < MFL_MAX; i++)
	{
		char ent_name[MAX_PATH];
		const char *n;
		int st_mode = 0;
		int st_size = 0;

		if (!(wrap_vfs_readdir(dp)))
			break;

		n = dp->d_name;
		strcpy(ent_name, mfl.dir[drv]);
		strcat(ent_name, n);
		st_mode = wrap_vfs_stat(ent_name, &st_size);

		if (!(st_mode & STAT_IS_DIRECTORY))
		{
			char *p;
			char ext[4];
			int len = strlen(n);

			/* Check extension if this is file. */
			if (len < 4 || *(n + len - 4) != '.')
			{
				i--;
				continue;
			}
			strcpy(ext, n + len - 3);
			upper(ext);
			p = strstr(support, ext);
			if (p == NULL || (p - support) % 3 != 0)
			{
				i--;
				continue;
			}
		}
		else
		{
			if (!strcmp(n, "."))
			{
				i--;
				continue;
			}

			/* You can't go up over current directory. */
			if (!strcmp(n, "..") && !strcmp(mfl.dir[drv], cur_dir_str))
			{
				i--;
				continue;
			}
		}

		strcpy(mfl.name[i], n);
		/* set 1 if this is directory */
		mfl.type[i] = (st_mode & STAT_IS_DIRECTORY) ? 1 : 0;
#ifdef DEBUG
		p6logd("%s 0x%x\n", n, buf.st_mode);
#endif
	}

	wrap_vfs_closedir(dp);

	strcpy(mfl.name[i], "");
	mfl.num = i;
	mfl.ptr = 0;

	/* Sorting mfl!
	 * Folder first, than files
	 * buble sort glory */
	for (a = 0; a < i - 1; a++)
	{
		int b;
		for (b = a + 1; b < i; b++)
		{
			if (mfl.type[a] < mfl.type[b])
				switch_mfl(a, b);
			if ((mfl.type[a] == mfl.type[b]) && (strcasecmp(mfl.name[a], mfl.name[b]) > 0))
				switch_mfl(a, b);
		}
	}
}

/* ex. ./hoge/.. -> ./
 * ( ./ ---down hoge dir--> ./hoge ---up hoge dir--> ./hoge/.. ) */
static void shortcut_dir(int drv)
{
	int i, len, found = 0;
	char *p;

	/* len is larger than 2 */
	len = strlen(mfl.dir[drv]);
	p   = mfl.dir[drv] + len - 2;
	for (i = len - 2; i >= 0; i--)
	{
		if (*p == slash)
		{
			found = 1;
			break;
		}
		p--;
	}
#ifdef _WIN32
	if (found && strcmp(p, "\\..\\"))
	{
#else
	if (found && strcmp(p, "/../"))
	{
#endif
		*(p + 1) = '\0';
	}
	else
	{
#ifdef _WIN32
		strcat(mfl.dir[drv], "..\\");
#else
		strcat(mfl.dir[drv], "../");
#endif
	}
}

int speedup_joy[0xff] = { 0 };

int WinUI_Menu(int first)
{
	int cursor0;
	uint8_t joy;
	int menu_redraw  = 0;
	int pad_changed  = 0;
	int mfile_redraw = 0;

	if (first)
	{
		menu_state  = ms_key;
		mkey_y      = 0;
		mkey_pos    = 0;
		menu_redraw = 1;
		first       = 0;
		/*  The screen is not rewritten without any key actions,
		 * so draw screen first. */
		WinDraw_ClearMenuBuffer();
		WinDraw_DrawMenu(menu_state, mkey_pos, mkey_y, mval_y);
	}

	cursor0 = mkey_y;
	joy     = get_joy_downstate();
	reset_joy_downstate();

	if (speedup_joy[JOY_RIGHT])
		joy &= ~JOY_RIGHT;
	if (speedup_joy[JOY_LEFT])
		joy &= ~JOY_LEFT;
	if (speedup_joy[JOY_UP])
		joy &= ~JOY_UP;
	if (speedup_joy[JOY_DOWN])
		joy &= ~JOY_DOWN;

	if (!(joy & JOY_UP))
	{
		switch (menu_state)
		{
		case ms_key:
			if (mkey_y > 0)
			{
				mkey_y--;
			}
			if (mkey_pos > mkey_y)
			{
				mkey_pos--;
			}
			break;
		case ms_value:
			if (mval_y[mkey_y] > 0)
			{
				mval_y[mkey_y]--;

				/* do something immediately */
				if (menu_func[mkey_y].imm)
				{
					menu_func[mkey_y].func(mval_y[mkey_y]);
				}

				menu_redraw = 1;
			}
			break;
		case ms_file:
			if (mfl.y == 0)
			{
				if (mfl.ptr > 0)
				{
					mfl.ptr--;
				}
			}
			else
			{
				mfl.y--;
			}
			mfile_redraw = 1;
			break;
		default:
			break;
		}
	}

	if (!(joy & JOY_DOWN))
	{
		switch (menu_state)
		{
		case ms_key:
			if (mkey_y < MENU_NUM - 1)
			{
				mkey_y++;
			}
			if (mkey_y > mkey_pos + MENU_WINDOW - 1)
			{
				mkey_pos++;
			}
			break;
		case ms_value:
			if (menu_items[mkey_y][mval_y[mkey_y] + 1][0] != '\0')
			{
				mval_y[mkey_y]++;

				if (menu_func[mkey_y].imm)
				{
					menu_func[mkey_y].func(mval_y[mkey_y]);
				}

				menu_redraw = 1;
			}
			break;
		case ms_file:
			if (mfl.y == 13)
			{
				if (mfl.ptr + 14 < mfl.num && mfl.ptr < MFL_MAX - 13)
				{
					mfl.ptr++;
				}
			}
			else if (mfl.y + 1 < mfl.num)
			{
				mfl.y++;
#ifdef DEBUG
				p6logd("mfl.y %d\n", mfl.y);
#endif
			}
			mfile_redraw = 1;
			break;
		default:
			break;
		}
	}

	if (!(joy & JOY_LEFT))
	{
		switch (menu_state)
		{
		case ms_key:
			break;
		case ms_value:
			if (mval_y[mkey_y] > 0)
			{
				mval_y[mkey_y] -= 10;
				if (mval_y[mkey_y] < 0)
					mval_y[mkey_y] = 0;

				/* do something immediately */
				if (menu_func[mkey_y].imm)
				{
					menu_func[mkey_y].func(mval_y[mkey_y]);
				}

				menu_redraw = 1;
			}
			break;
		case ms_file:
			if (mfl.y == 0)
			{
				if (mfl.ptr > 0)
				{
					mfl.ptr -= 10;
					if (mfl.ptr < 0)
						mfl.ptr = 0;
				}
			}
			else
			{
				mfl.y -= 10;
				if (mfl.y < 0)
				{
					if (mfl.ptr > 0)
						mfl.ptr += mfl.y;
					if (mfl.ptr < 0)
						mfl.ptr = 0;
					mfl.y = 0;
				}
			}
			mfile_redraw = 1;
			break;
		default:
			break;
		}
	}

	if (!(joy & JOY_RIGHT))
	{
		int ii;
		switch (menu_state)
		{
		case ms_key:
			break;
		case ms_value:
			for (ii = 0; ii < 10; ii++)
			{
				if (menu_items[mkey_y][mval_y[mkey_y] + 1][0] != '\0')
				{
					mval_y[mkey_y]++;

					if (menu_func[mkey_y].imm)
					{
						menu_func[mkey_y].func(mval_y[mkey_y]);
					}

					menu_redraw = 1;
				}
			}
			break;
		case ms_file:
			for (ii = 0; ii < 10; ii++)
			{
				if (mfl.y == 13)
				{
					if (mfl.ptr + 14 < mfl.num && mfl.ptr < MFL_MAX - 13)
					{
						mfl.ptr++;
					}
				}
				else if (mfl.y + 1 < mfl.num)
				{
					mfl.y++;
#ifdef DEBUG
					p6logd("mfl.y %d\n", mfl.y);
#endif
				}
				mfile_redraw = 1;
			}
			break;
		default:
			break;
		}
	}

	if (!(joy & JOY_TRG1))
	{
		int drv, y;
		switch (menu_state)
		{
		case ms_key:
			menu_state  = ms_value;
			menu_redraw = 1;
			break;
		case ms_value:
			menu_func[mkey_y].func(mval_y[mkey_y]);

			if (menu_state == ms_hwjoy_set)
			{
				menu_redraw = 1;
				break;
			}

			/* get back key_mode if value is set.
			 * go file_mode if value is filename. */
			menu_state  = ms_key;
			menu_redraw = 1;

			drv = WinUI_get_drv_num(mkey_y);
#ifdef DEBUG
			p6logd("**** drv:%d *****\n", drv);
#endif
			if (drv >= 0)
			{
				if (mval_y[mkey_y] == 0)
				{
					/* go file_mode */
#ifdef DEBUG
					p6logd("hoge:%d\n", mval_y[mkey_y]);
#endif
					menu_state   = ms_file;
					menu_redraw  = 0; /* reset */
					mfile_redraw = 1;
				}
				else
				{
#if 0
					mval_y[mkey_y] == 1
#endif
					/* FDD_EjectFD() is done, so set 0. */
					mval_y[mkey_y] = 0;
#ifdef DEBUG
					switch (drv)
					{
					case 0:
						p6logd("fdd0 ejected...\n", drv);
						break;
					case 1:
						p6logd("fdd1 ejected...\n", drv);
						break;
					case 2:
						p6logd("hdd0 ejected...\n", drv);
						break;
					case 3:
						p6logd("hdd1 ejected...\n", drv);
						break;
					}
#endif
				}
			}
			else if (!strcmp("SYSTEM", menu_item_key[mkey_y]))
			{
				if (mval_y[mkey_y] == 3)
				{
					return WUM_EMU_QUIT;
				}
				return WUM_MENU_END;
			}
			break;
		case ms_file:
			drv = WinUI_get_drv_num(mkey_y);
#ifdef DEBUG
			p6logd("***** drv:%d *****\n", drv);
#endif
			if (drv < 0)
			{
				break;
			}
			y = mfl.ptr + mfl.y;
#ifdef DEBUG
			p6logd("file selected: %s\n", mfl.name[y]);
#endif
			/* file loaded */
			if (mfl.type[y])
			{
				/* directory operation */
				if (!strcmp(mfl.name[y], ".."))
				{
					shortcut_dir(drv);
					mfl.stack[0][mfl.stackptr] = 0;
					mfl.stack[1][mfl.stackptr] = 0;
					mfl.stackptr               = (mfl.stackptr - 1) % 256;
					mfl.ptr                    = mfl.stack[0][mfl.stackptr];
					mfl.y                      = mfl.stack[1][mfl.stackptr];
				}
				else
				{
					strncat(mfl.dir[drv], mfl.name[y], sizeof(mfl.dir[drv]) - 1);
#ifdef _WIN32
					strcat(mfl.dir[drv], "\\");
#else
					strcat(mfl.dir[drv], "/");
#endif
					mfl.stack[0][mfl.stackptr] = mfl.ptr;
					mfl.stack[1][mfl.stackptr] = mfl.y;
					mfl.stackptr               = (mfl.stackptr + 1) % 256;
					mfl.ptr                    = 0;
					mfl.y                      = 0;
				}
#ifdef DEBUG
				p6logd("directory selected: %s\n", mfl.name[y]);
#endif
				menu_func[mkey_y].func(0);
				mfile_redraw = 1;
			}
			else
			{
				/* file operation */
#ifdef DEBUG
				p6logd("file selected: %s\n", mfl.name[y]);
#endif
				if (strlen(mfl.name[y]) != 0)
				{
					char tmpstr[MAX_PATH];
					strcpy(tmpstr, mfl.dir[drv]);
					strcat(tmpstr, mfl.name[y]);
					if (drv < 2)
					{
						FDD_SetFD(drv, tmpstr, 0);
						strcpy(Config.FDDImage[drv], tmpstr);
					}
					else
					{
						strcpy(Config.HDImage[drv - 2], tmpstr);
					}
				}
				menu_state  = ms_key;
				menu_redraw = 1;
			}
			mfl.ptr = mfl.stack[0][mfl.stackptr];
			mfl.y   = mfl.stack[1][mfl.stackptr];
			break;
		case ms_hwjoy_set:
			/* Go back keymode
			 * if TRG1 of v-pad or hw keyboard was pushed. */
			if (!pad_changed)
			{
				menu_state  = ms_key;
				menu_redraw = 1;
			}
			break;
		default:
			break;
		}
	}

	if (!(joy & JOY_TRG2))
	{
		switch (menu_state)
		{
		case ms_file:
			menu_state = ms_value;
			/* reset position of file cursor */
			mfl.y       = 0;
			mfl.ptr     = 0;
			menu_redraw = 1;
			break;
		case ms_value:
			menu_state  = ms_key;
			menu_redraw = 1;
			break;
		case ms_hwjoy_set:
			/* Go back keymode
			 * if TRG2 of v-pad or hw keyboard was pushed. */
			if (!pad_changed)
			{
				menu_state  = ms_key;
				menu_redraw = 1;
			}
			break;
		default:
			break;
		}
	}

	if (pad_changed)
	{
		menu_redraw = 1;
	}

	if (cursor0 != mkey_y)
	{
		menu_redraw = 1;
	}

	if (mfile_redraw)
	{
		WinDraw_DrawMenufile(&mfl);
		mfile_redraw = 0;
	}

	if (menu_redraw)
	{
		WinDraw_ClearMenuBuffer();
		WinDraw_DrawMenu(menu_state, mkey_pos, mkey_y, mval_y);
	}

	return 0;
}
