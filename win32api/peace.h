/*	$Id: peace.h,v 1.1.1.1 2003/04/28 18:06:55 nonaka Exp $	*/

#ifndef	__NP2_PEACE_H__
#define	__NP2_PEACE_H__

#ifdef __cplusplus
extern "C" {
#endif

uint32_t	WINAPI FAKE_GetTickCount(void);

BOOL	WINAPI ReadFile(HANDLE, void *, uint32_t, uint32_t *, LPOVERLAPPED);
BOOL	WINAPI WriteFile(HANDLE, const void *, uint32_t, uint32_t *, LPOVERLAPPED);
HANDLE	WINAPI CreateFile(const char *, uint32_t, uint32_t, LPSECURITY_ATTRIBUTES,
		uint32_t, uint32_t, HANDLE);
uint32_t	WINAPI SetFilePointer(HANDLE, long, long *, uint32_t);
BOOL	WINAPI FAKE_CloseHandle(HANDLE);
uint32_t	WINAPI GetFileAttributes(const char *);

HLOCAL	WINAPI LocalAlloc(uint32_t, uint32_t);
HLOCAL	WINAPI LocalFree(HLOCAL);
void 	*WINAPI LocalLock(HLOCAL);
BOOL	WINAPI LocalUnlock(HLOCAL);

HGLOBAL WINAPI GlobalAlloc(uint32_t, uint32_t);
HGLOBAL	WINAPI GlobalFree(HGLOBAL);
void 	*WINAPI GlobalLock(HGLOBAL);
BOOL	WINAPI GlobalUnlock(HGLOBAL);
HGLOBAL	WINAPI GlobalHandle(const void *);

uint32_t	WINAPI GetPrivateProfileString(const char *, const char *, const char *, char *,
		uint32_t, const char *);
uint32_t	WINAPI GetPrivateProfileInt(const char *, const char *, int, const char *);

#ifdef __cplusplus
};
#endif

#endif	/* __NP2_PEACE_H__ */
