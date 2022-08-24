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

#include <sys/param.h>
#include <time.h>

#include "dosio.h"

#ifdef __LIBRETRO__
extern char slash;
#endif

static char	curpath[MAX_PATH+32] = "";
static LPSTR	curfilep = curpath;

void dosio_init(void)
{

	/* Nothing to do. */
}

void dosio_term(void)
{

	/* Nothing to do. */
}

/* ファイル操作 */
FILEH file_open(LPSTR filename)
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

FILEH file_create(LPSTR filename, int ftype)
{
	FILEH	ret;

	(void)ftype;

	ret = CreateFile(filename, GENERIC_READ | GENERIC_WRITE,
	    0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ret == (FILEH)INVALID_HANDLE_VALUE)
		return (FILEH)FALSE;
	return ret;
}

DWORD file_seek(FILEH handle, long pointer, int16_t mode)
{

	return SetFilePointer(handle, pointer, 0, mode);
}

DWORD file_lread(FILEH handle, void *data, DWORD length)
{
	DWORD	readsize;

	if (ReadFile(handle, data, length, &readsize, NULL) == 0)
		return 0;
	return readsize;
}

DWORD file_lwrite(FILEH handle, void *data, DWORD length)
{
	DWORD	writesize;

	if (WriteFile(handle, data, length, &writesize, NULL) == 0)
		return 0;
	return writesize;
}

WORD file_read(FILEH handle, void *data, WORD length)
{
	DWORD	readsize;

	if (ReadFile(handle, data, length, &readsize, NULL) == 0)
		return 0;
	return (WORD)readsize;
}

DWORD file_zeroclr(FILEH handle, DWORD length)
{
	char	buf[256];
	DWORD	size;
	DWORD	wsize;
	DWORD	ret = 0;

	memset(buf, 0, sizeof(buf));
	while (length > 0) {
		wsize = (length >= sizeof(buf)) ? sizeof(buf) : length;

		size = file_lwrite(handle, buf, wsize);
		if (size == (DWORD)-1)
			return -1;

		ret += size;
		if (size != wsize)
			break;
		length -= wsize;
	}
	return ret;
}

WORD file_write(FILEH handle, void *data, WORD length)
{
	DWORD	writesize;

	if (WriteFile(handle, data, length, &writesize, NULL) == 0)
		return 0;
	return (WORD)writesize;
}

WORD file_lineread(FILEH handle, void *data, WORD length)
{
	LPSTR	p = (LPSTR)data;
	DWORD	readsize;
	DWORD	pos;
	WORD	ret = 0;

	if ((length == 0) || ((pos = file_seek(handle, 0, 1)) == (DWORD)-1))
		return 0;

	memset(data, 0, length);
	if (ReadFile(handle, data, length-1, &readsize, NULL) == 0)
		return 0;

	while (*p) {
		ret++;
		pos++;
		if ((*p == 0x0d) || (*p == 0x0a)) {
			break;
		}
		p++;
	}
	*p = '\0';

	file_seek(handle, pos, 0);

	return ret;
}

int16_t file_close(FILEH handle)
{
	FAKE_CloseHandle(handle);
	return 0;
}

int16_t file_attr(LPSTR filename)
{
	return (int16_t)GetFileAttributes(filename);
}

							// カレントファイル操作
void file_setcd(LPSTR exename)
{

	strncpy(curpath, exename, sizeof(curpath));
	plusyen(curpath, sizeof(curpath));
	curfilep = curpath + strlen(exename) + 1;
	*curfilep = '\0';
}

LPSTR file_getcd(LPSTR filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return curpath;
}

FILEH file_open_c(LPSTR filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_open(curpath);
}

FILEH file_create_c(LPSTR filename, int ftype)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_create(curpath, ftype);
}

int16_t file_attr_c(LPSTR filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_attr(curpath);
}

int file_getftype(LPSTR filename)
{
	(void)filename;
	return FTYPE_NONE;
}

LPSTR getFileName(LPSTR filename)
{
	LPSTR p, q;

	for (p = q = filename; *p != '\0'; p++)
		if (*p == slash/*'/'*/)
			q = p + 1;
	return q;
}

void
cutFileName(LPSTR filename)
{
	LPSTR p, q;

	for (p = filename, q = NULL; *p != '\0'; p++)
		if (*p == slash/*'/'*/)
			q = p + 1;
	if (q != NULL)
		*q = '\0';
}

LPSTR getExtName(LPSTR filename)
{
	LPSTR	p;
	LPSTR	q;

	p = getFileName(filename);
	q = NULL;

	while (*p != '\0') {
		if (*p == '.')
			q = p + 1;
		p++;
	}
	if (q == NULL)
		q = p;
	return q;
}

void cutExtName(LPSTR filename)
{
	LPSTR	p;
	LPSTR	q;

	p = getFileName(filename);
	q = NULL;

	while (*p != '\0') {
		if (*p == '.')
			q = p;
		p++;
	}
	if (q != NULL)
		*q = '\0';
}

int kanji1st(LPSTR str, int pos)
{
	int	ret = 0;
	BYTE	c;

	for (; pos > 0; pos--) {
		c = (BYTE)str[pos];
		if (!((0x81 <= c && c <= 0x9f) || (0xe0 <= c && c <= 0xfc)))
			break;
		ret ^= 1;
	}
	return ret;
}

int kanji2nd(LPSTR str, int pos)
{
	int	ret = 0;
	BYTE	c;

	while (pos-- > 0) {
		c = (BYTE)str[pos];
		if (!((0x81 <= c && c <= 0x9f) || (0xe0 <= c && c <= 0xfc)))
			break;
		ret ^= 1;
	}
	return ret;
}


int ex_a2i(LPSTR str, int min, int max)
{
	int	ret = 0;
	char	c;

	if (str == NULL)
		return(min);

	for (;;) {
		c = *str++;
		if (c == ' ')
			continue;
		if ((c < '0') || (c > '9'))
			break;
		ret = ret * 10 + (c - '0');
	}

	if (ret < min)
		return min;
	else if (ret > max)
		return max;
	return ret;
}

void cutyen(LPSTR str)
{
	int pos = strlen(str) - 1;

	if ((pos > 0) && (str[pos] == slash/*'/'*/))
		str[pos] = '\0';
}

void plusyen(LPSTR str, int len)
{
	int	pos = strlen(str);

	if (pos) {
		if (str[pos-1] == slash/*'/'*/)
			return;
	}
	if ((pos + 2) >= len)
		return;
	str[pos++] = slash/*'/'*/;
	str[pos] = '\0';
}


void fname_mix(LPSTR str, LPSTR mix, int size)
{
	LPSTR p;
	int len;
	char c;
	char check;

	cutFileName(str);
	if (mix[0] == slash/*'/'*/)
		str[0] = '\0';

	len = strlen(str);
	p = str + len;
	check = '.';
	while (len < size) {
		c = *mix++;
		if (c == '\0')
			break;

		if (c == check) {
			/* current dir */
			if (mix[0] == slash/*'/'*/) {
				mix++;
				continue;
			}
			/* parent dir */
			if (mix[0] == '.' && mix[1] == slash/*'/'*/) {
				mix += 2;
				cutyen(str);
				cutFileName(str);
				len = strlen(str);
				p = str + len;
				continue;
			}
		}
		if (c == slash/*'/'*/)
			check = '.';
		else
			check = 0;
		*p++ = c;
		len++;
	}
	if (p < str + len)
		*p = '\0';
	else
		str[len - 1] = '\0';
}
