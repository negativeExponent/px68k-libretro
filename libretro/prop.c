/* 
 * Copyright (c) 2003 NONAKA Kimihiro
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
 *  PROP.C - 各種設定用プロパティシートと設定値管理                           *
 * -------------------------------------------------------------------------- */

#include <sys/stat.h>

#include "common.h"
#include "winx68k.h"
#include "keyboard.h"
#include "fileio.h"
#include "prop.h"

BYTE	LastCode = 0;
BYTE	KEYCONFFILE[] = "xkeyconf.dat";

int	CurrentHDDNo = 0;

BYTE ini_title[] = "WinX68k";

BYTE initialized = 0;

static const char MIDI_TYPE_NAME[4][3] = {
	"LA", "GM", "GS", "XG"
};

BYTE KeyTableBk[512];

Win68Conf Config;
Win68Conf ConfBk;

#ifndef MAX_BUTTON
#define MAX_BUTTON 32
#endif

extern char filepath[MAX_PATH];
extern char winx68k_ini[MAX_PATH];
extern int winx, winy;
extern char joyname[2][MAX_PATH];
extern char joybtnname[2][MAX_BUTTON][MAX_PATH];
extern BYTE joybtnnum[2];

#define CFGLEN MAX_PATH

static char *makeBOOL(BYTE value) {

	if (value) {
		return("true");
	}
	return("false");
}

static BYTE Aacmp(char *cmp, char *str) {

	char	p;

	while(*str) {
		p = *cmp++;
		if (!p) {
			break;
		}
		if (p >= 'a' && p <= 'z') {
			p -= 0x20;
		}
		if (p != *str++) {
			return(-1);
		}
	}
	return(0);
}

static BYTE solveBOOL(char *str) {

	if ((!Aacmp(str, "TRUE")) || (!Aacmp(str, "ON")) ||
		(!Aacmp(str, "+")) || (!Aacmp(str, "1")) ||
		(!Aacmp(str, "ENABLE"))) {
		return(1);
	}
	return(0);
}

#ifdef __LIBRETRO__
extern char retro_system_conf[512];
extern char slash;

#endif

int
set_modulepath(char *path, size_t len)
{
	struct stat sb;
	char *homepath;

#ifdef __LIBRETRO__
        p6logd("Libretro...\n");
        strcpy(path,retro_system_conf);
        sprintf(winx68k_ini, "%s%cconfig",retro_system_conf,slash);
        return 0;
#endif
	homepath = getenv("HOME");
	if (homepath == 0)
		homepath = ".";

	snprintf(path, len, "%s/%s", homepath, ".keropi");
	if (stat(path, &sb) < 0) {
#ifdef _WIN32
		if (mkdir(path) < 0) {
#else
		if (mkdir(path, 0700) < 0) {
#endif
			perror(path);
			return 1;
		}
	} else {
		if ((sb.st_mode & S_IFDIR) == 0) {
			fprintf(stderr, "%s isn't directory.\n", path);
			return 1;
		}
	}
	snprintf(winx68k_ini, sizeof(winx68k_ini), "%s/%s", path, "config");
	if (stat(winx68k_ini, &sb) >= 0) {
		if (sb.st_mode & S_IFDIR) {
			fprintf(stderr, "%s is directory.\n", winx68k_ini);
			return 1;
		}
	}

	return 0;
}

static void LoadDefaults(void)
{
	int i;
	int j;

	Config.MenuFontSize = 0; // start with default normal menu size
	winx = 0;
	winy = 0;
	Config.FrameRate = 1;
	filepath[0] = 0;
	Config.OPM_VOL = 12;
	Config.PCM_VOL = 15;
	Config.MCR_VOL = 13;
	Config.SampleRate = 44100;
	Config.BufferSize = 50;
	Config.MouseSpeed = 10;
	Config.WindowFDDStat = 1;
	Config.FullScrFDDStat = 1;
	Config.DSAlert = 1;
	Config.Sound_LPF = 1;
	Config.SoundROMEO = 1;
	Config.MIDI_SW = 1;
	Config.MIDI_Reset = 1;
	Config.MIDI_Type = 1;
	Config.JoySwap = 0;
	Config.JoyKey = 0;
	Config.JoyKeyReverse = 0;
	Config.JoyKeyJoy2 = 0;
	Config.SRAMWarning = 1;
	Config.LongFileName = 1;
	Config.WinDrvFD = 1;
	Config.WinStrech = 1;
	Config.DSMixing = 0;
	Config.XVIMode = 0;
	Config.CDROM_ASPI = 1;
	Config.CDROM_SCSIID = 6;
	Config.CDROM_ASPI_Drive = 0;
	Config.CDROM_IOCTRL_Drive = 16;
	Config.CDROM_Enable = 1;
	Config.SSTP_Enable = 0;
	Config.SSTP_Port = 11000;
	Config.ToneMap = 0;
	Config.ToneMapFile[0] = 0;
	Config.MIDIDelay = Config.BufferSize*5;
	Config.MIDIAutoDelay = 1;
	Config.VkeyScale = 4;
	Config.VbtnSwap = 0;
	Config.JoyOrMouse = 1;
	Config.HwJoyAxis[0] = 0;
	Config.HwJoyAxis[1] = 1;
	Config.HwJoyHat = 0;

	for (i = 0; i < 8; i++)
		Config.HwJoyBtn[i] = i;

	Config.NoWaitMode = 0;
	Config.AdjustFrameRates = 1;
	Config.AudioDesyncHack = 0;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 8; j++)
			Config.JOY_BTN[i][j] = j;

	for (i = 0; i < 2; i++)
		Config.FDDImage[i][0] = '\0';

	for (i = 0; i < 16; i++)
		Config.HDImage[i][0] = '\0';

	initialized = 1;
}

void LoadConfig(void)
{
	int	i, j;
	char	buf[CFGLEN];
	FILEH fp;

	/* Because we are not loading defauts for most items from a config file,
	 * irectly set default config at first call
	 */
	if (!initialized)
		LoadDefaults();

	// Config.MenuFontSize = 0; // start with default normal menu size
	// winx = GetPrivateProfileInt(ini_title, "WinPosX", 0, winx68k_ini);
	// winy = GetPrivateProfileInt(ini_title, "WinPosY", 0, winx68k_ini);

	// Config.FrameRate = (BYTE)GetPrivateProfileInt(ini_title, "FrameRate", 1, winx68k_ini);

	// if (!Config.FrameRate) Config.FrameRate = 1;
	GetPrivateProfileString(ini_title, "StartDir", "", buf, MAX_PATH, winx68k_ini);
	if (buf[0] != 0)
		strncpy(filepath, buf, sizeof(filepath));
	else
		filepath[0] = 0;

	// Config.OPM_VOL = GetPrivateProfileInt(ini_title, "OPM_Volume", 12, winx68k_ini);
	// Config.PCM_VOL = GetPrivateProfileInt(ini_title, "PCM_Volume", 15, winx68k_ini);
	// Config.MCR_VOL = GetPrivateProfileInt(ini_title, "MCR_Volume", 13, winx68k_ini);

	// Config.SampleRate = GetPrivateProfileInt(ini_title, "SampleRate", 44100, winx68k_ini);

	// Config.BufferSize = GetPrivateProfileInt(ini_title, "BufferSize", 50, winx68k_ini);

	// Config.MouseSpeed = GetPrivateProfileInt(ini_title, "MouseSpeed", 10, winx68k_ini);

	/* GetPrivateProfileString(ini_title, "FDDStatWin", "1", buf, CFGLEN, winx68k_ini);
	Config.WindowFDDStat = solveBOOL(buf);*/
	/* GetPrivateProfileString(ini_title, "FDDStatFullScr", "1", buf, CFGLEN, winx68k_ini);
	Config.FullScrFDDStat = solveBOOL(buf); */

	/* GetPrivateProfileString(ini_title, "DSAlert", "1", buf, CFGLEN, winx68k_ini);
	Config.DSAlert = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "SoundLPF", "1", buf, CFGLEN, winx68k_ini);
	Config.Sound_LPF = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "UseRomeo", "0", buf, CFGLEN, winx68k_ini);
	Config.SoundROMEO = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "MIDI_SW", "1", buf, CFGLEN, winx68k_ini);
	Config.MIDI_SW = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "MIDI_Reset", "0", buf, CFGLEN, winx68k_ini);
	Config.MIDI_Reset = solveBOOL(buf); */
	// Config.MIDI_Type = GetPrivateProfileInt(ini_title, "MIDI_Type", 1, winx68k_ini);

	/* GetPrivateProfileString(ini_title, "JoySwap", "0", buf, CFGLEN, winx68k_ini);
	Config.JoySwap = solveBOOL(buf); */

	/* GetPrivateProfileString(ini_title, "JoyKey", "0", buf, CFGLEN, winx68k_ini);
	Config.JoyKey = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "JoyKeyReverse", "0", buf, CFGLEN, winx68k_ini);
	Config.JoyKeyReverse = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "JoyKeyJoy2", "0", buf, CFGLEN, winx68k_ini);
	Config.JoyKeyJoy2 = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "SRAMBootWarning", "1", buf, CFGLEN, winx68k_ini);
	Config.SRAMWarning = solveBOOL(buf); */

	/* GetPrivateProfileString(ini_title, "WinDrvLFN", "1", buf, CFGLEN, winx68k_ini);
	Config.LongFileName = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "WinDrvFDD", "1", buf, CFGLEN, winx68k_ini);
	Config.WinDrvFD = solveBOOL(buf); */

	// Config.WinStrech = GetPrivateProfileInt(ini_title, "WinStretch", 1, winx68k_ini);

	/* GetPrivateProfileString(ini_title, "DSMixing", "0", buf, CFGLEN, winx68k_ini);
	Config.DSMixing = solveBOOL(buf); */

	//Config.XVIMode = (BYTE)GetPrivateProfileInt(ini_title, "XVIMode", 0, winx68k_ini);

	/* GetPrivateProfileString(ini_title, "CDROM_ASPI", "1", buf, CFGLEN, winx68k_ini);
	Config.CDROM_ASPI = solveBOOL(buf); */
	// Config.CDROM_SCSIID = (BYTE)GetPrivateProfileInt(ini_title, "CDROM_SCSIID", 6, winx68k_ini);
	// Config.CDROM_ASPI_Drive = (BYTE)GetPrivateProfileInt(ini_title, "CDROM_ASPIDrv", 0, winx68k_ini);
	// Config.CDROM_IOCTRL_Drive = (BYTE)GetPrivateProfileInt(ini_title, "CDROM_CTRLDrv", 16, winx68k_ini);
	/* GetPrivateProfileString(ini_title, "CDROM_Enable", "1", buf, CFGLEN, winx68k_ini);
	Config.CDROM_Enable = solveBOOL(buf); */

	/* GetPrivateProfileString(ini_title, "SSTP_Enable", "0", buf, CFGLEN, winx68k_ini);
	Config.SSTP_Enable = solveBOOL(buf); */
	// Config.SSTP_Port = GetPrivateProfileInt(ini_title, "SSTP_Port", 11000, winx68k_ini);

	/* GetPrivateProfileString(ini_title, "ToneMapping", "0", buf, CFGLEN, winx68k_ini);
	Config.ToneMap = solveBOOL(buf); */
	/* GetPrivateProfileString(ini_title, "ToneMapFile", "", buf, MAX_PATH, winx68k_ini);
	if (buf[0] != 0)
		strcpy(Config.ToneMapFile, buf);
	else
		Config.ToneMapFile[0] = 0; */

	// Config.MIDIDelay = GetPrivateProfileInt(ini_title, "MIDIDelay", Config.BufferSize*5, winx68k_ini);
	// Config.MIDIAutoDelay = GetPrivateProfileInt(ini_title, "MIDIAutoDelay", 1, winx68k_ini);

	// Config.VkeyScale = GetPrivateProfileInt(ini_title, "VkeyScale", 4, winx68k_ini);

	// Config.VbtnSwap = GetPrivateProfileInt(ini_title, "VbtnSwap", 0, winx68k_ini);

	// Config.JoyOrMouse = GetPrivateProfileInt(ini_title, "JoyOrMouse", 1, winx68k_ini);

	// Config.HwJoyAxis[0] = GetPrivateProfileInt(ini_title, "HwJoyAxis0", 0, winx68k_ini);

	// Config.HwJoyAxis[1] = GetPrivateProfileInt(ini_title, "HwJoyAxis1", 1, winx68k_ini);

	// Config.HwJoyHat = GetPrivateProfileInt(ini_title, "HwJoyHat", 0, winx68k_ini);

	/* for (i = 0; i < 8; i++) {
		sprintf(buf, "HwJoyBtn%d", i);
		Config.HwJoyBtn[i] = GetPrivateProfileInt(ini_title, buf, i, winx68k_ini);
	} */

	// Config.NoWaitMode = GetPrivateProfileInt(ini_title, "NoWaitMode", 0, winx68k_ini);

	/* for (i=0; i<2; i++)
	{
		for (j=0; j<8; j++)
		{
			sprintf(buf, "Joy%dButton%d", i+1, j+1);
			Config.JOY_BTN[i][j] = GetPrivateProfileInt(ini_title, buf, j, winx68k_ini);
		}
	} */

	if (Config.save_fdd_path) {
		for (i = 0; i < 2; i++) {
			sprintf(buf, "FDD%d", i);
			GetPrivateProfileString(ini_title, buf, "", Config.FDDImage[i], MAX_PATH, winx68k_ini);
		}
	}

	if (Config.save_hdd_path) {
		for (i=0; i<16; i++)
		{
			sprintf(buf, "HDD%d", i);
			GetPrivateProfileString(ini_title, buf, "", Config.HDImage[i], MAX_PATH, winx68k_ini);
		}
	}
}


void SaveConfig(void)
{
	int	i, j;
	char	buf[CFGLEN], buf2[CFGLEN];
	FILEH fp;

	WritePrivateProfileString(ini_title, "StartDir", filepath, winx68k_ini);

	if (Config.save_fdd_path)
		for (i = 0; i < 2; i++)
		{
			/* printf("i: %d", i); */
			sprintf(buf, "FDD%d", i);
			WritePrivateProfileString(ini_title, buf, Config.FDDImage[i], winx68k_ini);
		}

	if (Config.save_hdd_path)
		for (i=0; i<16; i++)
		{
			sprintf(buf, "HDD%d", i);
			WritePrivateProfileString(ini_title, buf, Config.HDImage[i], winx68k_ini);
		}
}
