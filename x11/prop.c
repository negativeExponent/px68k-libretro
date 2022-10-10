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
#include <stdio.h>

#include "common.h"
#include "prop.h"

static char ini_title[] = "WinX68k";
static int initialized = 0;
Win68Conf Config;

extern char filepath[MAX_PATH];
extern char winx68k_ini[MAX_PATH];

extern char retro_system_conf[512];
extern char slash;

#define CFGLEN MAX_PATH

#if 0
static char *makeBOOL(uint8_t value)
{
	if (value)
	{
		return ("true");
	}
	return ("false");
}

static uint8_t Aacmp(char *cmp, char *str)
{
	char p;

	while (*str)
	{
		p = *cmp++;
		if (!p)
		{
			break;
		}
		if (p >= 'a' && p <= 'z')
		{
			p -= 0x20;
		}
		if (p != *str++)
		{
			return (-1);
		}
	}
	return (0);
}

static uint8_t solveBOOL(char *str)
{
	if ((!Aacmp(str, "TRUE")) || (!Aacmp(str, "ON")) || (!Aacmp(str, "+")) || (!Aacmp(str, "1")) ||
	    (!Aacmp(str, "ENABLE")))
	{
		return (1);
	}
	return (0);
}
#endif

int set_modulepath(char *path, size_t len)
{
	strcpy(path, retro_system_conf);
	sprintf(winx68k_ini, "%s%cconfig", retro_system_conf, slash);
	return 0;
}

void SetConfigDefaults(void)
{
	int i;

	Config.menuSize = 0;
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
	Config.Sound_LPF = 1;
	Config.SoundROMEO = 1;
	Config.MIDI_SW = 1;
	Config.MIDI_Reset = 1;
	Config.MIDI_Type = 1;
	Config.JoySwap = 0;
	Config.JoyKey = 0;
	Config.JoyKeyReverse = 0;
	Config.JoyKeyJoy2 = 0;
	Config.XVIMode = 0;
	Config.ToneMap = 0;
	Config.ToneMapFile[0] = 0;
	Config.MIDIDelay = Config.BufferSize * 5;
	Config.MIDIAutoDelay = 1;
	Config.VkeyScale = 4;
	Config.VbtnSwap = 0;
	Config.JoyOrMouse = 1;
	Config.NoWaitMode = 0;
	Config.AdjustFrameRates = 1;
	Config.AudioDesyncHack = 0;
	Config.cpuClock = 10;
	Config.ramSize = 2;

	for (i = 0; i < 2; i++)
		Config.FDDImage[i][0] = '\0';

	for (i = 0; i < 16; i++)
		Config.HDImage[i][0] = '\0';

	initialized = 1;
}

void LoadConfig(void)
{
	int i;
	char buf[CFGLEN];

	GetPrivateProfileString(ini_title, "StartDir", "", buf, MAX_PATH, winx68k_ini);
	if (buf[0] != 0)
		strncpy(filepath, buf, sizeof(filepath));
	else
		filepath[0] = 0;

	if (Config.saveFDDPath)
	{
		for (i = 0; i < 2; i++)
		{
			sprintf(buf, "FDD%d", i);
			GetPrivateProfileString(ini_title, buf, "", Config.FDDImage[i], MAX_PATH, winx68k_ini);
		}
	}

	if (Config.saveHDDPath)
	{
		for (i = 0; i < 16; i++)
		{
			sprintf(buf, "HDD%d", i);
			GetPrivateProfileString(ini_title, buf, "", Config.HDImage[i], MAX_PATH, winx68k_ini);
		}
	}
}

void SaveConfig(void)
{
	int i;
	char buf[CFGLEN];

	WritePrivateProfileString(ini_title, "StartDir", filepath, winx68k_ini);

	if (Config.saveFDDPath)
	{
		for (i = 0; i < 2; i++)
		{
			sprintf(buf, "FDD%d", i);
			WritePrivateProfileString(ini_title, buf, Config.FDDImage[i], winx68k_ini);
		}
	}

	if (Config.saveHDDPath)
	{
		for (i = 0; i < 16; i++)
		{
			sprintf(buf, "HDD%d", i);
			WritePrivateProfileString(ini_title, buf, Config.HDImage[i], winx68k_ini);
		}
	}
}
