#ifndef winx68k_fileio_h
#define winx68k_fileio_h

#include "common.h"
#include "dosio.h"

#define	FILEH		HANDLE

#define	FSEEK_SET	0
#define	FSEEK_CUR	1
#define	FSEEK_END	2

char *getFileName(char *filename);
//#define	getFileName	GetFileName

FILEH	File_Open(char *filename);
FILEH	File_Create(char *filename);
uint32_t	File_Seek(FILEH handle, long pointer, short mode);
uint32_t	File_Read(FILEH handle, void *data, uint32_t length);
uint32_t	File_Write(FILEH handle, void *data, uint32_t length);
int16_t	File_Close(FILEH handle);
int16_t	File_Attr(char *filename);
#define	File_Open	file_open
#define	File_Create	file_create
#define	File_Seek	file_seek
#define	File_Read	file_lread
#define	File_Write	file_lwrite
#define	File_Close	file_close
#define	File_Attr	file_attr

void	File_SetCurDir(char *exename);
FILEH	File_OpenCurDir(char *filename);
FILEH	File_CreateCurDir(char *filename);
int16_t	File_AttrCurDir(char *filename);
#define	File_SetCurDir		file_setcd
#define	File_OpenCurDir		file_open_c
#define	File_CreateCurDir	file_create_c
#define	File_AttrCurDir		file_attr_c

#endif
