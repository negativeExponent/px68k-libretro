#ifndef _X68K_VC_H
#define _X68K_VC_H

extern uint8_t VCReg0[2];
extern uint8_t VCReg1[2];
extern uint8_t VCReg2[2];

uint8_t FASTCALL VCtrl_Read(uint32_t adr);
void    FASTCALL VCtrl_Write(uint32_t adr, uint8_t data);

#endif /* _X68K_VC_H */
