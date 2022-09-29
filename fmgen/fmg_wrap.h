#ifndef _win68_opm_fmgen
#define _win68_opm_fmgen

#include <stdint.h>

int OPM_Init(int clock, int rate);
void OPM_Cleanup(void);
void OPM_Reset(void);
void OPM_Update(int16_t *buffer, int length, int rate, uint8_t *pbsp, uint8_t *pbep);
void FASTCALL OPM_Write(uint32_t adr, uint8_t data);
uint8_t FASTCALL OPM_Read(uint32_t adr);
void FASTCALL OPM_Timer(uint32_t step);
void OPM_SetVolume(uint8_t vol);
void OPM_SetRate(int clock, int rate);
void OPM_RomeoOut(uint32_t delay);

#ifndef NO_MERCURY
int M288_Init(int clock, int rate, const char* path);
void M288_Cleanup(void);
void M288_Reset(void);
void M288_Update(int16_t *buffer, int length);
void FASTCALL M288_Write(uint32_t r, uint8_t v);
uint8_t FASTCALL M288_Read(uint16_t a);
void FASTCALL M288_Timer(uint32_t step);
void M288_SetVolume(uint8_t vol);
void M288_SetRate(int clock, int rate);
void M288_RomeoOut(uint32_t delay);
#endif /* !NO_MERCURY */

#endif //_win68_opm_fmgen
