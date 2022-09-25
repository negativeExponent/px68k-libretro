#ifndef __NP2_WIN32EMUL_H__
#define __NP2_WIN32EMUL_H__

#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/param.h>

/* for INLINE */
#include "libretro-common/include/retro_inline.h"

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
#define UNUSED(v) ((void)(v))
#endif

/* for dosio.c */
#define GENERIC_READ  1
#define GENERIC_WRITE 2

#define OPEN_EXISTING 1
#define CREATE_ALWAYS 2
#define CREATE_NEW    3

#define FILE_SHARE_READ   0x00000001
#define FILE_SHARE_WRITE  0x00000002
#define FILE_SHARE_DELETE 0x00000004

#define FILE_ATTRIBUTE_READONLY  0x01
#define FILE_ATTRIBUTE_HIDDEN    0x02
#define FILE_ATTRIBUTE_SYSTEM    0x04
#define FILE_ATTRIBUTE_VOLUME    0x08
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_ARCHIVE   0x20
#define FILE_ATTRIBUTE_NORMAL    0x40

#define INVALID_HANDLE_VALUE     (void *)-1

#define NO_ERROR                0
#define ERROR_FILE_NOT_FOUND    2
#define ERROR_SHARING_VIOLATION 32

#define FILE_BEGIN   0
#define FILE_CURRENT 1
#define FILE_END     2

/*
 * replace
 */
#define timeGetTime() FAKE_GetTickCount()

/*
 * prototype
 */
#ifdef __cplusplus
extern "C"
{
#endif

BOOL WritePrivateProfileString(const char *, const char *, const char *, const char *);
uint32_t FAKE_GetLastError(void);
BOOL SetEndOfFile(void *hFile);

#ifdef __cplusplus
};
#endif

#include "peace.h"

#endif /* __NP2_WIN32EMUL_H__ */
