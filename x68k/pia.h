#ifndef _WINX68K_PIA_H
#define _WINX68K_PIA_H

void PIA_Init(void);
uint8_t FASTCALL PIA_Read(uint32_t adr);
void FASTCALL PIA_Write(uint32_t adr, uint8_t data);

#endif /* _WINX68K_PIA_H */
