#ifndef _WINX68K_CORE_H
#define _WINX68K_CORE_H

#include "common.h"

#ifdef RFMDRV
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

extern int rfd_sock;
#endif

#define FULLSCREEN_WIDTH  800
#define FULLSCREEN_HEIGHT 600

#define TOSTR(s)    #s
#define _TOSTR(s)   TOSTR(s)
#define PX68KVERSTR _TOSTR(PX68K_VERSION)

extern uint8_t *FONT;

extern uint16_t VLINE_TOTAL;
extern uint32_t VLINE;
extern uint32_t vline;

extern char winx68k_dir[MAX_PATH];
extern char winx68k_ini[MAX_PATH];

int WinX68k_Reset(void);
int pmain(int argc, char *argv[]);
void end_loop_retro(void);
void exec_app_retro();

#define NELEMENTS(array) ((int)(sizeof(array) / sizeof(array[0])))

#endif /* _WINX68K_CORE_H */
