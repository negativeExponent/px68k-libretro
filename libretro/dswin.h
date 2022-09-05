#ifndef _WINX68K_DSWIN_H
#define _WINX68K_DSWIN_H

int DSound_Init(uint32_t rate, uint32_t length);
int DSound_Cleanup(void);

void DSound_Play(void);
void DSound_Stop(void);
void FASTCALL DSound_Send0(long clock);

int audio_samples_avail();
void audio_samples_discard(int discard);
void raudio_callback(void *userdata, unsigned char *stream, int len);

#endif /* _WINX68K_DSWIN_H */
