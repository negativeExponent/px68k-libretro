/*	$Id: mmsystem.h,v 1.1.1.1 2003/04/28 18:06:55 nonaka Exp $	*/

#ifndef	MMSYSTEM_H__
#define	MMSYSTEM_H__

#include "windows.h"

typedef	HANDLE		HMIDIOUT;
typedef	HMIDIOUT *	LPHMIDIOUT;

typedef struct midihdr {
	char				*lpData;
	uint32_t			dwBufferLength;
	uint32_t			dwBytesRecorded;
	uint32_t			dwUser;
	uint32_t			dwFlags;
	struct midihdr *	lpNext;
	uint32_t			reserved;
	uint32_t			dwOffset;
	uint32_t			dwReserved[8];
} MIDIHDR, *PMIDIHDR, *NPMIDIHDR, *LPMIDIHDR;


#define	MMSYSERR_NOERROR	0
#define	MIDIERR_STILLPLAYING	2

#define	MIDI_MAPPER		-1

#define	CALLBACK_NULL		0x00000000L


#ifdef __cplusplus
extern "C" {
#endif

uint32_t midiOutPrepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, uint32_t cbmh);
uint32_t midiOutUnprepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, uint32_t cbmh);
uint32_t midiOutShortMsg(HMIDIOUT hmo, uint32_t dwMsg);
uint32_t midiOutLongMsg(HMIDIOUT hmo, LPMIDIHDR pmh, uint32_t cbmh);
uint32_t midiOutOpen(LPHMIDIOUT phmo, uint32_t uDeviceID, uint32_t dwCallback, uint32_t dwInstance, uint32_t fdwOpen);
uint32_t midiOutClose(HMIDIOUT hmo);
uint32_t midiOutReset(HMIDIOUT hmo);

#ifdef __cplusplus
};
#endif

#endif	/* MMSYSTEM_H__ */
