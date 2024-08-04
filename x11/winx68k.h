#ifndef _X68K_CORE_H
#define _X68K_CORE_H

#include "common.h"

#ifdef RFMDRV
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

extern int rfd_sock;
#endif

#define FULLSCREEN_WIDTH  800
#define FULLSCREEN_HEIGHT 600

#define PX68K_VERSION "0.15+"

extern uint16_t VLINE_TOTAL;
extern uint32_t VLINE;
extern uint32_t vline;

extern char winx68k_dir[2048];
extern char winx68k_ini[2048];

void WinX68k_Reset(int softReset);

int pmain(int argc, char *argv[]);
void end_loop_retro(void);
void exec_app_retro(void);
void shutdown_app_retro(void);

int PX68KSS_Save_Mem(void);
int PX68KSS_Load_Mem(void);

#define NELEMENTS(array) ((int)(sizeof(array) / sizeof(array[0])))

#endif /* _X68K_CORE_H */
