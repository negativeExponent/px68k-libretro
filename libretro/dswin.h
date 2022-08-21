#ifndef dswin_h__
#define dswin_h__

#include "common.h"

int32_t DSound_Init(unsigned long rate, unsigned long length);
int32_t DSound_Cleanup(void);

void DSound_Play(void);
void DSound_Stop(void);
void FASTCALL DSound_Send0(long clock);

void DS_SetVolumeOPM(long vol);
void DS_SetVolumeADPCM(long vol);
void DS_SetVolumeMercury(long vol);

int32_t audio_samples_avail();
void audio_samples_discard(int32_t discard);
void raudio_callback(void *userdata, unsigned char *stream, int32_t len);

#endif /* dswin_h__ */
