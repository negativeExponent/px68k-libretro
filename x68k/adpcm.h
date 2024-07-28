#ifndef _WINX68K_ADPCM_H
#define _WINX68K_ADPCM_H

#include <stdint.h>

void FASTCALL ADPCM_PreUpdate(uint32_t clock);
void ADPCM_Update(int16_t *buffer, size_t length, int16_t *pbsp, int16_t *pbep);

void FASTCALL ADPCM_Write(uint32_t adr, uint8_t data);
uint8_t FASTCALL ADPCM_Read(uint32_t adr);

void ADPCM_SetVolume(uint8_t vol);
void ADPCM_SetPan(int n);
void ADPCM_SetClock(int n);

void ADPCM_Init(void);

#endif /* _WINX68K_ADPCM_H */
