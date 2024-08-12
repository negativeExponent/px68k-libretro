#ifndef _X68K_PAL_H
#define _X68K_PAL_H

extern uint8_t Pal_Regs[1024];
extern uint16_t TextPal[256];
extern uint16_t GrphPal[256];
extern uint16_t Pal16[65536];

void Pal_Init(void);
void Pal_ChangeContrast(int num);

extern uint16_t Ibit, Pal_HalfMask, Pal_Ix2;

#endif /* _X68K_PAL_H */
