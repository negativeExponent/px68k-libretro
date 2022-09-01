#ifndef _WINX68K_SASI_H
#define _WINX68K_SASI_H

#include "common.h"

void SASI_Init(void);
uint8_t FASTCALL SASI_Read(uint32_t adr);
void FASTCALL SASI_Write(uint32_t adr, uint8_t data);
int SASI_IsReady(void);

extern char SASI_Name[16][MAX_PATH];

#endif /*_WINX68K_SASI_H */
