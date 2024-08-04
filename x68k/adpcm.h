#ifndef _X68K_ADPCM_H
#define _X68K_ADPCM_H

void FASTCALL ADPCM_PreUpdate(int32_t clock);
void FASTCALL ADPCM_Update(int16_t *buffer, int32_t length, int16_t *pbsp, int16_t *pbep);
void ADPCM_SetVolume(uint8_t vol);
void ADPCM_SetPan(int n);
void ADPCM_SetClock(int n);
void ADPCM_Init(uint32_t samplerate);
int  ADPCM_IsReady(void);

void    FASTCALL ADPCM_Write(uint32_t adr, uint8_t data);
uint8_t FASTCALL ADPCM_Read(uint32_t adr);

#endif /* _X68K_ADPCM_H */
