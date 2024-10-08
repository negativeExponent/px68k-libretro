#ifndef _X68K_SRAM_H
#define _X68K_SRAM_H

extern uint8_t SRAM[0x4000];

void SRAM_Init(void);
void SRAM_Cleanup(void);

void SRAM_Clear(void);

void SRAM_SetMem(uint16_t adr, uint8_t val);

/* Sets the system RAM size (MiB) */
void SRAM_SetRAMSize(int);
void SRAM_UpdateBoot(void);
void SRAM_WriteEnable(int enable);

uint8_t FASTCALL SRAM_Read(uint32_t adr);
void FASTCALL SRAM_Write(uint32_t adr, uint8_t data);

int SRAM_StateContext(void *f, int writing);

#endif /* _X68K_SRAM_H */
