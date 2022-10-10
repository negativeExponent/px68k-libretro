#ifndef __NP2_WIN32EMUL_H__
#define __NP2_WIN32EMUL_H__

#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/param.h>

/* for INLINE */
#include <retro_inline.h>

typedef int BOOL;

#ifndef FASTCALL
#define FASTCALL
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef MAX_PATH
#define MAX_PATH MAXPATHLEN
#endif

#ifdef __GNUC__
#ifndef UNUSED
#define UNUSED __attribute((unused))
#endif
#else
#define UNUSED
#endif

/*
 * replace
 */
#define timeGetTime() FAKE_GetTickCount()

#include "peace.h"

#endif /* __NP2_WIN32EMUL_H__ */
