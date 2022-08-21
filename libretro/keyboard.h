#ifndef _winx68k_keyboard
#define _winx68k_keyboard

#include <stdint.h>
#include "common.h"

#define KeyBufSize 128

extern	uint8_t	KeyBuf[KeyBufSize];
extern	uint8_t	KeyBufWP;
extern	uint8_t	KeyBufRP;
extern	uint8_t	KeyTable[512];
extern	uint8_t	KeyTableMaster[512];
extern	uint8_t	KeyEnable;
extern	uint8_t	KeyIntFlag;

struct keyboard_key {
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
	char *s;
	unsigned char c;
};

extern struct keyboard_key kbd_key[];
extern int32_t kbd_kx, kbd_ky;
extern int32_t kbd_x, kbd_y, kbd_w, kbd_h;

void Keyboard_Init(void);
void Keyboard_KeyDown(uint32_t vkcode);
void Keyboard_KeyUp(uint32_t vkcode);
void Keyboard_Int(void);
void send_keycode(uint8_t code, int32_t flag);
int32_t Keyboard_get_key_ptr(int32_t x, int32_t y);
void Keyboard_skbd(void);
int32_t Keyboard_IsSwKeyboard(void);
void Keyboard_ToggleSkbd(void);

#define	RETROK_XFX	333
/* https://gamesx.com/wiki/doku.php?id=x68000:keycodes */
#define	KBD_XF1		0x55
#define	KBD_XF2		0x56
#define	KBD_XF3		0x57
#define	KBD_XF4		0x58
#define	KBD_XF5		0x59
#define	KBD_F1		0x63
#define	KBD_F2		0x64
#define	KBD_OPT1	0x72
#define	KBD_OPT2	0x73

#endif //_winx68k_keyboard
