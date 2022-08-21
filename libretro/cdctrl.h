#ifndef CDCTRL_H_
#define	CDCTRL_H_

#include <stdint.h>

int32_t CDCTRL_Open(void);
void CDCTRL_Close(void);
int32_t CDCTRL_Wait(void);
int32_t CDCTRL_ReadTOC(void* buf);
int32_t CDCTRL_Read(long block, uint8_t* buf);
int32_t CDCTRL_IsOpen(void);

#endif // CDCTRL_H_
