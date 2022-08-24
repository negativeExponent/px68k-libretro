#ifndef _win68_opm_fmgen
#define _win68_opm_fmgen

#include <stdint.h>

int OPM_Init(int clock, int rate);
void OPM_Cleanup(void);
void OPM_Reset(void);
void OPM_Update(int16_t *buffer, int length, int rate, BYTE *pbsp, BYTE *pbep);
void FASTCALL OPM_Write(DWORD r, BYTE v);
BYTE FASTCALL OPM_Read(WORD a);
void FASTCALL OPM_Timer(DWORD step);
void OPM_SetVolume(BYTE vol);
void OPM_SetRate(int clock, int rate);
void OPM_RomeoOut(uint32_t delay);

int M288_Init(int clock, int rate, const char* path);
void M288_Cleanup(void);
void M288_Reset(void);
void M288_Update(int16_t *buffer, int length);
void FASTCALL M288_Write(DWORD r, BYTE v);
BYTE FASTCALL M288_Read(WORD a);
void FASTCALL M288_Timer(DWORD step);
void M288_SetVolume(BYTE vol);
void M288_SetRate(int clock, int rate);
void M288_RomeoOut(uint32_t delay);

#endif //_win68_opm_fmgen
