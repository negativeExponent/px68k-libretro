#ifndef _X68K_CONFIG_H
#define _X68K_CONFIG_H

typedef struct
{
	int SampleRate;
	int BufferSize;
	int OPM_VOL;
	int PCM_VOL;
	int MCR_VOL;
	int MouseSpeed;
	int WindowFDDStat;
	int FullScrFDDStat;
	int MIDI_SW;
	int MIDI_Type;
	int MIDI_Reset;
	int JoyKey;
	int JoyKeyReverse;
	int JoyKeyJoy2;
	char HDImage[16][MAX_PATH];
	int ToneMap;
	char ToneMapFile[MAX_PATH];
	int XVIMode;
	int JoySwap;
	int Sound_LPF;
	int SoundROMEO;
	int MIDIDelay;
	int MIDIAutoDelay;
	char FDDImage[2][MAX_PATH];
	int VkeyScale;
	int VbtnSwap;
	int JoyOrMouse;
	int NoWaitMode;
	int FrameRate;
	int AdjustFrameRates;
	int AudioDesyncHack;
	int menuSize;    /* 0 = normal, 1 = large */
	int P1SelectMap; /* assigne a keyboard map to Player 1's Select button */
	int saveFDDPath;
	int saveHDDPath;
	int ramSize; /* ram size in MB */
	int cpuClock; /* Cpu clock in MHz */
	/* Set controller type for each player to use
	 * 0 = Standard 2-buttons gamepad
	 * 1 = CPSF-MD (8 Buttons
	 * 2 = CPSF-SFC (8 Buttons) */
	int joyType[2];
} Win68Conf;

extern Win68Conf Config;

/* Load this before pmain */
void SetConfigDefaults(void);
void LoadConfig(void);
void SaveConfig(void);

int set_modulepath(char *path);

#endif /*_X68K_CONFIG_H */
