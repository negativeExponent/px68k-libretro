#ifndef _X68K_SYSPORT_H
#define _X68K_SYSPORT_H

extern uint8_t SysPort[8];

void SysPort_Init(void);
uint8_t FASTCALL SysPort_Read(uint32_t adr);
void FASTCALL SysPort_Write(uint32_t adr, uint8_t data);

#endif /* _X68K_SYSPORT_H */
