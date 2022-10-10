#ifndef _CONFIG_H
#define _CONFIG_H

uint32_t	GetPrivateProfileString(const char *, const char *, const char *, char *, uint32_t, const char *);
uint32_t	GetPrivateProfileInt(const char *, const char *, int, const char *);
BOOL		WritePrivateProfileString(const char *, const char *, const char *, const char *);

#endif /* _CONFIG_H */