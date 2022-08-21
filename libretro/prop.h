#ifndef _winx68k_config
#define _winx68k_config

#include <stdint.h>
#include "common.h"

typedef struct
{
	uint32_t SampleRate;
	uint32_t BufferSize;
	int32_t WinPosX;
	int32_t WinPosY;
	int32_t OPM_VOL;
	int32_t PCM_VOL;
	int32_t MCR_VOL;
	int32_t JOY_BTN[2][8];
	int32_t MouseSpeed;
	int32_t WindowFDDStat;
	int32_t FullScrFDDStat;
	int32_t DSAlert;
	int32_t MIDI_SW;
	int32_t MIDI_Type;
	int32_t MIDI_Reset;
	int32_t JoyKey;
	int32_t JoyKeyReverse;
	int32_t JoyKeyJoy2;
	int32_t SRAMWarning;
	char HDImage[16][MAX_PATH];
	int32_t ToneMap;
	char ToneMapFile[MAX_PATH];
	int32_t XVIMode;
	int32_t JoySwap;
	int32_t LongFileName;
	int32_t WinDrvFD;
	int32_t WinStrech;
	int32_t DSMixing;
	int32_t CDROM_ASPI;
	int32_t CDROM_ASPI_Drive;
	int32_t CDROM_IOCTRL_Drive;
	int32_t CDROM_SCSIID;
	int32_t CDROM_Enable;
	int32_t SSTP_Enable;
	int32_t SSTP_Port;
	int32_t Sound_LPF;
	int32_t SoundROMEO;
	int32_t MIDIDelay;
	int32_t MIDIAutoDelay;
	char FDDImage[2][MAX_PATH];
	int32_t VkeyScale;
	int32_t VbtnSwap;
	int32_t JoyOrMouse;
	int32_t HwJoyAxis[2];
	int32_t HwJoyHat;
	int32_t HwJoyBtn[8];
	int32_t NoWaitMode;
	uint8_t FrameRate;
	int32_t AdjustFrameRates;
	int32_t AudioDesyncHack;
	int32_t MenuFontSize; // font size of menu, 0 = normal, 1 = large
	int32_t joy1_select_mapping; /* used for keyboard to joypad map for P1 Select */
	int32_t save_fdd_path;
	int32_t save_hdd_path;
	/* Cpu clock in MHz */
	int32_t clockmhz;
	/* RAM Size = size * 1024 * 1024 */
	int32_t ram_size;
	/* Set controller type for each player to use
	 * 0 = Standard 2-buttons gamepad
	 * 1 = CPSF-MD (8 Buttons
	 * 2 = CPSF-SFC (8 Buttons) */
	int32_t JOY_TYPE[2];
} Win68Conf;

extern Win68Conf Config;

void LoadConfig(void);
void SaveConfig(void);
void PropPage_Init(void);

int32_t set_modulepath(char *path, size_t len);

#endif //_winx68k_config
