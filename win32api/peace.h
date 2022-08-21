/*	$Id: peace.h,v 1.1.1.1 2003/04/28 18:06:55 nonaka Exp $	*/

#ifndef	__NP2_PEACE_H__
#define	__NP2_PEACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t	FAKE_GetTickCount(void);

BOOL	ReadFile(void *, void *, uint32_t, uint32_t *, LPOVERLAPPED);
BOOL	WriteFile(void *, const void *, uint32_t, uint32_t *, LPOVERLAPPED);
void *	CreateFile(const char *, uint32_t, uint32_t, LPSECURITY_ATTRIBUTES,
		uint32_t, uint32_t, void *);
uint32_t	SetFilePointer(void *, long, long *, uint32_t);
BOOL	FAKE_CloseHandle(void *);
uint32_t	GetFileAttributes(const char *);

HLOCAL	LocalAlloc(uint32_t, uint32_t);
HLOCAL	LocalFree(HLOCAL);
void	*LocalLock(HLOCAL);
BOOL	LocalUnlock(HLOCAL);

HGLOBAL GlobalAlloc(uint32_t, uint32_t);
HGLOBAL	GlobalFree(HGLOBAL);
void	*GlobalLock(HGLOBAL);
BOOL	GlobalUnlock(HGLOBAL);
HGLOBAL	GlobalHandle(const void *);

uint32_t	GetPrivateProfileString(const char *, const char *, const char *, char *,
		uint32_t, const char *);
uint32_t	GetPrivateProfileInt(const char *, const char *, int32_t, const char *);

#ifdef __cplusplus
};
#endif

#endif	/* __NP2_PEACE_H__ */
