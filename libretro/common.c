// ---------------------------------------------------------------------------------------
//  COMMON - 標準ヘッダ群（COMMON.H）とエラーダイアログ表示とか
// ---------------------------------------------------------------------------------------
//#include	<windows.h>
#include <stdio.h>
#include <stdarg.h>

#include "libretro.h"
extern retro_log_printf_t log_cb;

//#include	"sstp.h"

//extern HWND hWndMain;

// P6L: PX68K_LOG
//      ~ ~   ~
#define P6L_LEN 256
char p6l_buf[P6L_LEN];

void Error(const char* s)
{
	printf("Error: %s\n", s);

//	SSTP_SendMes(SSTPMES_ERROR);

//	MessageBox(hWndMain, s, title, MB_ICONERROR | MB_OK);
}

// log for debug
void p6logd(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vsnprintf(p6l_buf, P6L_LEN, fmt, args);
	va_end(args);

   if (log_cb)
      log_cb(RETRO_LOG_INFO, "%s", p6l_buf);
}
