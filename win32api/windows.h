#ifndef	__NP2_WIN32EMUL_H__
#define	__NP2_WIN32EMUL_H__

#include <sys/param.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>

typedef	int		BOOL;

typedef	void *		LPSECURITY_ATTRIBUTES;
typedef	void *		LPOVERLAPPED;

typedef void *		HANDLE;
typedef	HANDLE		HLOCAL;
typedef	HANDLE		HGLOBAL;

#ifndef FASTCALL
#define FASTCALL
#endif

#ifndef	TRUE
#define	TRUE	1
#endif

#ifndef	FALSE
#define	FALSE	0
#endif

#ifndef	MAX_PATH
#define	MAX_PATH	MAXPATHLEN
#endif

#ifndef	AVE
#define	AVE(a, b)	(((a)+(b))/2)
#endif

#ifdef __GNUC__
#ifndef UNUSED
#define UNUSED __attribute ((unused))
#endif
#else
#define	UNUSED(v)	((void)(v))
#endif

#ifndef	INLINE
#define	INLINE	static inline
#endif

#define	RGB(r,g,b)	((uint32_t)((uint8_t)(r))|((uint16_t)((uint8_t)(g)))|((uint32_t)((uint8_t)(b))))

#define	MB_APPLMODAL		0

#define	MB_ICONSTOP		16
#define	MB_ICONINFORMATION	64

#define	MB_OK			0

#define	GPTR			64

/* for BITMAP */
#define BI_RGB			0
#define BI_RLE8			1
#define BI_RLE4			2
#define	BI_BITFIELDS		3

/* for dosio.c */
#define	GENERIC_READ			1
#define	GENERIC_WRITE			2

#define	OPEN_EXISTING			1
#define	CREATE_ALWAYS			2
#define	CREATE_NEW			3

#define	FILE_SHARE_READ			0x00000001  
#define	FILE_SHARE_WRITE		0x00000002  
#define	FILE_SHARE_DELETE		0x00000004  

#define	FILE_ATTRIBUTE_READONLY		0x01
#define	FILE_ATTRIBUTE_HIDDEN		0x02
#define	FILE_ATTRIBUTE_SYSTEM		0x04
#define	FILE_ATTRIBUTE_VOLUME		0x08
#define	FILE_ATTRIBUTE_DIRECTORY	0x10
#define	FILE_ATTRIBUTE_ARCHIVE		0x20
#define	FILE_ATTRIBUTE_NORMAL		0x40

#define	INVALID_HANDLE_VALUE		(HANDLE)-1

#define	NO_ERROR			0
#define	ERROR_FILE_NOT_FOUND		2
#define	ERROR_SHARING_VIOLATION		32

#define	FILE_BEGIN			0
#define	FILE_CURRENT			1
#define	FILE_END			2


/*
 * replace
 */
#define	timeGetTime()		FAKE_GetTickCount()

typedef struct {
	uint16_t	x;
	uint16_t	y;
} POINT;

/*
 * prototype
 */
#ifdef __cplusplus
extern "C" {
#endif
BOOL	WritePrivateProfileString(const char *, const char *, const char *, const char *);

uint32_t	FAKE_GetLastError(void);
#ifdef __cplusplus
};
#endif

#include "peace.h"

#endif /* __NP2_WIN32EMUL_H__ */
