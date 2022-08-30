/*	$Id: peace.h,v 1.1.1.1 2003/04/28 18:06:55 nonaka Exp $	*/

#ifndef	__NP2_PEACE_H__
#define	__NP2_PEACE_H__

#ifdef __cplusplus
extern "C" {
#endif

uint32_t	FAKE_GetTickCount(void);

BOOL	ReadFile(HANDLE, void *, uint32_t, uint32_t *, LPOVERLAPPED);
BOOL	WriteFile(HANDLE, const void *, uint32_t, uint32_t *, LPOVERLAPPED);
HANDLE	CreateFile(const char *, uint32_t, uint32_t, LPSECURITY_ATTRIBUTES,
		uint32_t, uint32_t, HANDLE);
uint32_t	SetFilePointer(HANDLE, long, long *, uint32_t);
BOOL	FAKE_CloseHandle(HANDLE);
uint32_t	GetFileAttributes(const char *);

HLOCAL	LocalAlloc(uint32_t, uint32_t);
HLOCAL	LocalFree(HLOCAL);
void 	*LocalLock(HLOCAL);
BOOL	LocalUnlock(HLOCAL);

HGLOBAL GlobalAlloc(uint32_t, uint32_t);
HGLOBAL	GlobalFree(HGLOBAL);
void 	*GlobalLock(HGLOBAL);
BOOL	GlobalUnlock(HGLOBAL);
HGLOBAL	GlobalHandle(const void *);

uint32_t	GetPrivateProfileString(const char *, const char *, const char *, char *,
		uint32_t, const char *);
uint32_t	GetPrivateProfileInt(const char *, const char *, int, const char *);

#ifdef __cplusplus
};
#endif

#endif	/* __NP2_PEACE_H__ */
