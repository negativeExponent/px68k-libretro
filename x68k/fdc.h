#ifndef _WINX68K_FDC_H
#define _WINX68K_FDC_H

void FDC_Init(void);
uint8_t FASTCALL FDC_Read(uint32_t adr);
void FASTCALL FDC_Write(uint32_t adr, uint8_t data);
int16_t FDC_Flush(void);
void FDC_SetForceReady(int n);
int FDC_IsDataReady(void);

#endif /* _WINX68K_FDC_H */
