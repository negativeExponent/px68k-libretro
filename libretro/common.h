#ifndef _WINX68K_COMMON_H
#define _WINX68K_COMMON_H

#include "../win32api/windows.h"

#ifndef FASTCALL
#define FASTCALL
#endif

void Error(const char *s);
void p6logd(const char *fmt, ...);

#endif /* _WINX68K_COMMON_H */
