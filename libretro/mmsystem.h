/*	$Id: mmsystem.h,v 1.1.1.1 2003/04/28 18:06:55 nonaka Exp $	*/

#ifndef MMSYSTEM_H__
#define MMSYSTEM_H__

typedef struct midi_interface_t {
	int (*Open)(void);
	void (*Close)(void);
	void (*SendShort)(uint32_t dwMsg);
	void (*SendLong)(uint8_t *lpMsg, size_t length);
} midi_interface_t;

extern midi_interface_t *midi_interface;

#endif /* MMSYSTEM_H__ */
