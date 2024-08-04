#ifndef _X68K_SASI_H
#define _X68K_SASI_H

void SASI_Init(void);
uint8_t FASTCALL SASI_Read(uint32_t adr);
void FASTCALL SASI_Write(uint32_t adr, uint8_t data);
int SASI_IsReady(void);

#endif /*_X68K_SASI_H */
