#ifndef _X68K_SCC_H
#define _X68K_SCC_H

void SCC_IntCheck(void);
void SCC_Init(void);
uint8_t FASTCALL SCC_Read(uint32_t adr);
void FASTCALL SCC_Write(uint32_t adr, uint8_t data);

extern int8_t MouseX;
extern int8_t MouseY;
extern uint8_t MouseSt;

#endif /* _X68K_SCC_H */
