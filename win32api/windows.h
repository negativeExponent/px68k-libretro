#ifndef	__NP2_WIN32EMUL_H__
#define	__NP2_WIN32EMUL_H__

#include <assert.h>
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

typedef	int		BOOL;

typedef	void *		LPSECURITY_ATTRIBUTES;
typedef	void *		LPOVERLAPPED;

typedef void *		HANDLE;
typedef	HANDLE		HLOCAL;
typedef	HANDLE		HGLOBAL;

typedef	void *		DRAWITEMSTRUCT;

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

/*
 * WIN32 structure
 */
typedef struct {
	uint16_t	bfType;
	uint32_t	bfSize;
	uint16_t	bfReserved1;
	uint16_t	bfReserved2;
	uint32_t	bfOffBits;
} __attribute__ ((packed)) BITMAPFILEHEADER;

typedef struct {
	uint32_t	biSize;
	long	biWidth;
	long	biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	long	biXPelsPerMeter;
	long	biYPelsPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;
} __attribute__ ((packed)) BITMAPINFOHEADER;

typedef struct {
	uint8_t	rgbBlue;
	uint8_t	rgbGreen;
	uint8_t	rgbRed;
	uint8_t	rgbReserved;
} __attribute__ ((packed)) RGBQUAD;

typedef struct {
	BITMAPINFOHEADER	bmiHeader;
	RGBQUAD			bmiColors[1];
} __attribute__ ((packed)) BITMAPINFO;

typedef struct {
	uint32_t	top;
	uint32_t	left;
	uint32_t	bottom;
	uint32_t	right;
} RECT;

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
BOOL	SetEndOfFile(HANDLE hFile);
#ifdef __cplusplus
};
#endif

#include "peace.h"

#endif /* __NP2_WIN32EMUL_H__ */
