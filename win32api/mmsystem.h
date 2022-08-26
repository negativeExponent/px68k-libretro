/*	$Id: mmsystem.h,v 1.1.1.1 2003/04/28 18:06:55 nonaka Exp $	*/

#ifndef	MMSYSTEM_H__
#define	MMSYSTEM_H__

#include "windows.h"

#define	WINMMAPI
typedef	uint32_t	MMRESULT;
typedef	HANDLE		HMIDIOUT;
typedef	HMIDIOUT 	*LPHMIDIOUT;

typedef struct midihdr {
	uint8_t 		*lpData;
	uint32_t		dwBufferLength;
	uint32_t		dwBytesRecorded;
	uint32_t		dwUser;
	uint32_t		dwFlags;
	struct midihdr	*lpNext;
	uint32_t		reserved;
	uint32_t		dwOffset;
	uint32_t		dwReserved[8];
} MIDIHDR, *PMIDIHDR, *NPMIDIHDR, *LPMIDIHDR;


#define	MMSYSERR_NOERROR	0
#define	MIDIERR_STILLPLAYING	2

#define	MIDI_MAPPER		-1

#define	CALLBACK_NULL		0x00000000L


#ifdef __cplusplus
extern "C" {
#endif

WINMMAPI MMRESULT WINAPI midiOutPrepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, uint32_t cbmh);
WINMMAPI MMRESULT WINAPI midiOutUnprepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, uint32_t cbmh);
WINMMAPI MMRESULT WINAPI midiOutShortMsg(HMIDIOUT hmo, uint32_t dwMsg);
WINMMAPI MMRESULT WINAPI midiOutLongMsg(HMIDIOUT hmo, LPMIDIHDR pmh, uint32_t cbmh);
WINMMAPI MMRESULT WINAPI midiOutOpen(LPHMIDIOUT phmo, uint32_t uDeviceID, uint32_t dwCallback, uint32_t dwInstance, uint32_t fdwOpen);
WINMMAPI MMRESULT WINAPI midiOutClose(HMIDIOUT hmo);
WINMMAPI MMRESULT WINAPI midiOutReset(HMIDIOUT hmo);

#ifdef __cplusplus
};
#endif

#endif	/* MMSYSTEM_H__ */
