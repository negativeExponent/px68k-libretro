#ifndef _WINX68K_RTC_H
#define _WINX68K_RTC_H

void RTC_Init(void);
uint8_t FASTCALL RTC_Read(uint32_t adr);
void FASTCALL RTC_Write(uint32_t adr, uint8_t data);
void RTC_Timer(int clock);

#endif /* _WINX68K_RTC_H */
