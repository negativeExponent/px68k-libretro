#ifndef _DSWIN_H
#define _DSWIN_H

#include "common.h"

void DSound_Play(void);
void DSound_Stop(void);
void DSound_Send0(int32_t clock);

int audio_samples_avail(void);
void audio_samples_discard(int discard);
void raudio_callback(void *userdata, int len);

#endif /* _DSWIN_H */
