#ifndef _WINX68K_TVRAM_H
#define _WINX68K_TVRAM_H

#include "common.h"

extern uint8_t TVRAM[0x80000];
extern uint8_t TextDirtyLine[1024];
extern uint8_t Text_TrFlag[1024];

void TVRAM_SetAllDirty(void);

void TVRAM_Init(void);
void TVRAM_Cleanup(void);

uint8_t FASTCALL TVRAM_Read(uint32_t adr);
void FASTCALL TVRAM_Write(uint32_t adr, uint8_t data);
void FASTCALL TVRAM_RCUpdate(void);
void FASTCALL Text_DrawLine(int opaq);

#endif /* _WINX68K_TVRAM_H */
