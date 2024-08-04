#ifndef _X68K_TIMER_H
#define _X68K_TIMER_H

extern uint32_t timercnt;
extern uint32_t tick;

void Timer_Init(void);
void Timer_Reset(void);
int Timer_GetCount(void);

#endif /* _X68K_TIMER_H */
