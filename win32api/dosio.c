/*	$Id: dosio.c,v 1.2 2003/12/05 18:07:15 nonaka Exp $	*/

/* 
 * Copyright (c) 2003 NONAKA Kimihiro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgment:
 *      This product includes software developed by NONAKA Kimihiro.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <sys/param.h>
#include <time.h>

#include "dosio.h"

extern char slash;

static char	curpath[MAX_PATH+32] = "";
static char	*curfilep = curpath;

/* ファイル操作 */
FILEH file_open(char *filename)
{
	FILEH	ret;

	ret = CreateFile(filename, GENERIC_READ | GENERIC_WRITE,
	    0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ret == (FILEH)INVALID_HANDLE_VALUE) {
		ret = CreateFile(filename, GENERIC_READ,
		    0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (ret == (FILEH)INVALID_HANDLE_VALUE)
			return (FILEH)FALSE;
	}
	return ret;
}

FILEH file_create(char *filename, int32_t ftype)
{
	FILEH	ret;

	(void)ftype;

	ret = CreateFile(filename, GENERIC_READ | GENERIC_WRITE,
	    0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ret == (FILEH)INVALID_HANDLE_VALUE)
		return (FILEH)FALSE;
	return ret;
}

uint32_t file_seek(FILEH handle, long pointer, int16_t mode)
{
	return SetFilePointer(handle, pointer, 0, mode);
}

uint32_t file_lread(FILEH handle, void *data, uint32_t length)
{
	uint32_t	readsize;

	if (ReadFile(handle, data, length, &readsize, NULL) == 0)
		return 0;
	return readsize;
}

uint32_t file_lwrite(FILEH handle, void *data, uint32_t length)
{
	uint32_t	writesize;

	if (WriteFile(handle, data, length, &writesize, NULL) == 0)
		return 0;
	return writesize;
}

uint16_t file_read(FILEH handle, void *data, uint16_t length)
{
	uint32_t	readsize;

	if (ReadFile(handle, data, length, &readsize, NULL) == 0)
		return 0;
	return (uint16_t)readsize;
}

uint16_t file_write(FILEH handle, void *data, uint16_t length)
{
	uint32_t	writesize;

	if (WriteFile(handle, data, length, &writesize, NULL) == 0)
		return 0;
	return (uint16_t)writesize;
}

int16_t file_close(FILEH handle)
{
	FAKE_CloseHandle(handle);
	return 0;
}

void file_setcd(char *exename)
{
	strncpy(curpath, exename, sizeof(curpath));
	plusyen(curpath, sizeof(curpath));
	curfilep = curpath + strlen(exename) + 1;
	*curfilep = '\0';
}

FILEH file_open_c(char *filename)
{

	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_open(curpath);
}

FILEH file_create_c(char *filename, int32_t ftype)
{

	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_create(curpath, ftype);
}

char *getFileName(char *filename)
{
	char *p, *q;

	for (p = q = filename; *p != '\0'; p++)
		if (*p == slash)
			q = p + 1;
	return q;
}

void plusyen(char *str, int32_t len)
{
	int32_t 	pos = strlen(str);

	if (pos) {
		if (str[pos-1] == slash)
			return;
	}
	if ((pos + 2) >= len)
		return;
	str[pos++] = slash;
	str[pos] = '\0';
}
