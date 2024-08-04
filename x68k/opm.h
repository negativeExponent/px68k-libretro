#ifndef _X68K_OPM_H
#define _X68K_OPM_H

int OPM_Init(int32_t clock, int32_t rate);
void OPM_Cleanup(void);
void OPM_SetRate(int32_t clock, int32_t rate);
void OPM_Reset(void);
uint8_t FASTCALL OPM_Read(uint32_t adr);
void FASTCALL OPM_Write(uint32_t adr, uint8_t data);
void OPM_Update(int16_t *buffer, int32_t length, int16_t *pbsp, int16_t *pbep);
void FASTCALL OPM_Timer(uint32_t step);
void OPM_SetVolume(uint8_t vol);
void OPM_SetChannelMask(uint32_t mask);
void OPM_RomeoOut(uint32_t delay);
int OPM_StateContext(void *f, int writing);

#endif
