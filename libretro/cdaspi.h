#ifndef CDASPI_H_
#define	CDASPI_H_

#include <stdint.h>

int32_t CDASPI_Open(void);
void CDASPI_Close(void);
int32_t CDASPI_Wait(void);
int32_t CDASPI_ReadTOC(void* buf);
int32_t CDASPI_Read(long block, uint8_t* buf);
int32_t CDASPI_ExecCmd(uint8_t *cdb, int32_t cdb_size, uint8_t *out_buff, int32_t out_size);
int32_t CDASPI_IsOpen(void);

void CDASPI_EnumCD(void);

void CDASPI_Init(void);
void CDASPI_Cleanup(void);

extern uint8_t CDASPI_CDName[8][4];
extern int32_t CDASPI_CDNum;

extern HINSTANCE ASPIDLL;
uint32_t (*pSendASPI32Command)(LPSRB);
uint32_t (*pGetASPI32SupportInfo)(void);

#endif // CDASPI_H_
