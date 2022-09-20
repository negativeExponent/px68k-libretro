#ifndef _WINX68K_MEMORY_H
#define _WINX68K_MEMORY_H

extern uint8_t *IPL;
extern uint8_t *MEM;
extern uint8_t *OP_ROM;
extern uint8_t *FONT;
extern uint8_t SCSIIPL[0x2000];
extern uint8_t SRAM[0x4000];
extern uint8_t GVRAM[0x80000];
extern uint8_t TVRAM[0x80000];

extern uint32_t BusErrFlag;
extern uint32_t BusErrAdr;
extern uint32_t MemByteAccess;

void Memory_Init(void);

uint32_t cpu_readmem24(uint32_t adr);
uint32_t cpu_readmem24_word(uint32_t adr);
uint32_t cpu_readmem24_dword(uint32_t adr);

uint8_t  dma_readmem24(uint32_t adr);
uint16_t dma_readmem24_word(uint32_t adr);
uint32_t dma_readmem24_dword(uint32_t adr);

void cpu_writemem24(uint32_t adr, uint32_t data);
void cpu_writemem24_word(uint32_t adr, uint32_t data);
void cpu_writemem24_dword(uint32_t adr, uint32_t data);

void dma_writemem24(uint32_t adr, uint8_t data);
void dma_writemem24_word(uint32_t adr, uint16_t data);
void dma_writemem24_dword(uint32_t adr, uint32_t data);

void Memory_SetSCSIMode(void);

#endif
