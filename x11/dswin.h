#ifndef _X68K_DSWIN_H
#define _X68K_DSWIN_H

void DSound_Init(uint32_t rate);
void DSound_Cleanup(void);

void DSound_Play(void);
void DSound_Stop(void);
void FASTCALL DSound_Send0(int32_t clock);

int audio_samples_avail(void);
void audio_samples_discard(int32_t discard);

void raudio_callback(void *userdata, int32_t len);

#endif /* _X68K_DSWIN_H */
