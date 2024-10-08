#ifndef _X68K_FDC_H
#define _X68K_FDC_H

void FDC_Init(void);
uint8_t FASTCALL FDC_Read(uint32_t adr);
void FASTCALL FDC_Write(uint32_t adr, uint8_t data);
void FDC_SetForceReady(int n);
int FDC_IsDataReady(void);

#endif /* _X68K_FDC_H */
