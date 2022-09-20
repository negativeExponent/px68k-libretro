#ifndef _WINX68K_BG_H
#define _WINX68K_BG_H

extern uint8_t  BG_Regs[0x12];
extern uint32_t VLINEBG;
extern uint16_t BG_LineBuf[1600];

extern long BG_HAdjust;
extern long BG_VLINE;

void    BG_Init(void);
uint8_t FASTCALL BG_Read(uint32_t adr);
void    FASTCALL BG_Write(uint32_t adr, uint8_t data);
void    FASTCALL BG_DrawLine(int opaq, int gd);

#endif /* _WINX68K_BG_H */
