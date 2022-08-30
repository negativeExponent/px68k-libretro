/*	$Id: mmsystem.h,v 1.1.1.1 2003/04/28 18:06:55 nonaka Exp $	*/

#ifndef MMSYSTEM_H__
#define MMSYSTEM_H__

#include "windows.h"

typedef struct midihdr
{
	uint8_t *lpData;
	uint32_t dwBufferLength;
	uint32_t dwBytesRecorded;
	uint32_t dwUser;
	uint32_t dwFlags;
	struct midihdr *lpNext;
	uint32_t reserved;
	uint32_t dwOffset;
	uint32_t dwReserved[8];
} MIDIHDR;

#define MMSYSERR_NOERROR     0
#define MIDIERR_STILLPLAYING 2

#define MIDI_MAPPER -1

#define CALLBACK_NULL 0x00000000L

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t midiOutPrepareHeader(void *hmo, MIDIHDR *pmh, uint32_t cbmh);
uint32_t midiOutUnprepareHeader(void *hmo, MIDIHDR *pmh, uint32_t cbmh);
uint32_t midiOutShortMsg(void *hmo, uint32_t dwMsg);
uint32_t midiOutLongMsg(void *hmo, MIDIHDR *pmh, uint32_t cbmh);
uint32_t midiOutOpen(void **phmo, uint32_t uDeviceID, uint32_t dwCallback, uint32_t dwInstance, uint32_t fdwOpen);
uint32_t midiOutClose(void *hmo);
uint32_t midiOutReset(void *hmo);

#ifdef __cplusplus
};
#endif

#endif /* MMSYSTEM_H__ */
