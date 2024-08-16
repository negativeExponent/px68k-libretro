#ifndef _X68K_MEMORY_H
#define _X68K_MEMORY_H

#define MEM_SIZE  0xC00000 /* main memory */
#define IPL_SIZE  0x40000
#define FONT_SIZE 0xC0000
#define SRAM_SIZE 0x4000
#define GVRAM_SIZE 0x80000
#define TVRAM_SIZE 0x80000

extern uint8_t *OP_ROM;

extern uint8_t IPL[IPL_SIZE];
extern uint8_t FONT[FONT_SIZE];
extern uint8_t SCSIIPL[0x2000];

/* states */
extern uint8_t MEM[MEM_SIZE];
extern uint8_t SRAM[SRAM_SIZE];
extern uint8_t GVRAM[GVRAM_SIZE];
extern uint8_t TVRAM[TVRAM_SIZE];

extern uint32_t BusErrFlag;
extern uint32_t BusErrAdr;

void Memory_Init(void);

void cpu_buserr(uint32_t adr, int read);

uint32_t cpu_readmem24(uint32_t adr);
uint32_t cpu_readmem24_word(uint32_t adr);

uint8_t dma_readmem24(uint32_t adr);
uint16_t dma_readmem24_word(uint32_t adr);

void cpu_writemem24(uint32_t adr, uint32_t data);
void cpu_writemem24_word(uint32_t adr, uint32_t data);

void dma_writemem24(uint32_t adr, uint8_t data);
void dma_writemem24_word(uint32_t adr, uint16_t data);

void Memory_SetSCSIMode(void);

#endif
