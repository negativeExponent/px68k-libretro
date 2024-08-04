#ifndef _X68K_MERCURY_H
#define _X68K_MERCURY_H

extern uint8_t Mcry_LRTiming;

void FASTCALL Mcry_Update(int16_t *buffer, uint32_t length);
void FASTCALL Mcry_PreUpdate(uint32_t clock);

void FASTCALL Mcry_Write(uint32_t adr, uint8_t data);
uint8_t FASTCALL Mcry_Read(uint32_t adr);

void Mcry_SetVolume(uint8_t vol);

void Mcry_Init(uint32_t samplerate, const char* path);
void Mcry_Cleanup(void);
int Mcry_IsReady(void);

void FASTCALL Mcry_Int(void);

#endif /* _X68K_MERCURY_H */
