#ifndef _X68K_COMMON_H
#define _X68K_COMMON_H

#include "compiler.h"

void Error(const char *s);
void p6logd(const char *fmt, ...);

#define LOG_WR(a, d) p6logd(" %s: %06x %02x\n", __func__, a, d);
#define LOG_RD(a) p6logd(" %s: %06x\n", __func__, a);

#endif /* _X68K_COMMON_H */
