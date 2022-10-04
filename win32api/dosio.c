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

#include "../x11/common.h"
#include "dosio.h"

extern char slash;

static char	curpath[MAX_PATH] = "";
static char *curfilep = curpath;

void dosio_init(void)
{

	/* Nothing to do. */
}

void dosio_term(void)
{

	/* Nothing to do. */
}

/* ファイル操作 */
void *file_open(char *filename)
{
	void *ret;

	ret = CreateFile(filename, GENERIC_READ | GENERIC_WRITE,
	    0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ret == INVALID_HANDLE_VALUE) {
		ret = CreateFile(filename, GENERIC_READ,
		    0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (ret == INVALID_HANDLE_VALUE)
			return NULL;
	}
	return ret;
}

void *file_create(char *filename)
{
	void *ret;

	ret = CreateFile(filename, GENERIC_READ | GENERIC_WRITE,
	    0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ret == INVALID_HANDLE_VALUE)
		return NULL;
	return ret;
}

uint32_t file_seek(void *handle, long pointer, int16_t mode)
{
	return SetFilePointer(handle, pointer, 0, mode);
}

uint32_t file_read(void *handle, void *data, uint32_t length)
{
	uint32_t	readsize;

	if (ReadFile(handle, data, length, &readsize, NULL) == 0)
		return 0;
	return readsize;
}

uint32_t file_write(void *handle, void *data, uint32_t length)
{
	uint32_t	writesize;

	if (WriteFile(handle, data, length, &writesize, NULL) == 0)
		return 0;
	return writesize;
}

uint32_t file_zeroclr(void *handle, uint32_t length)
{
	char	buf[256];
	uint32_t	size;
	uint32_t	wsize;
	uint32_t	ret = 0;

	memset(buf, 0, sizeof(buf));
	while (length > 0) {
		wsize = (length >= sizeof(buf)) ? sizeof(buf) : length;

		size = file_write(handle, buf, wsize);
		if (size == (uint32_t)-1)
			return -1;

		ret += size;
		if (size != wsize)
			break;
		length -= wsize;
	}
	return ret;
}

uint16_t file_lineread(void *handle, void *data, uint16_t length)
{
	char *p = (char *)data;
	uint32_t	readsize;
	uint32_t	pos;
	uint16_t	ret = 0;

	if ((length == 0) || ((pos = file_seek(handle, 0, 1)) == (uint32_t)-1))
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

int16_t file_close(void *handle)
{
	FAKE_CloseHandle(handle);
	return 0;
}

int16_t file_attr(char *filename)
{
	return (int16_t)GetFileAttributes(filename);
}

							// カレントファイル操作
void file_setcd(char *exename)
{

	strncpy(curpath, exename, sizeof(curpath) - 1);
	plusyen(curpath, sizeof(curpath));
	curfilep = curpath + strlen(exename) + 1;
	*curfilep = '\0';
}

char *file_getcd(char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return curpath;
}

void *file_open_c(char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_open(curpath);
}

void *file_create_c(char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_create(curpath);
}

int16_t file_attr_c(char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_attr(curpath);
}

int file_getftype(char *filename)
{
	(void)filename;
	return 0;
}

char *getFileName(char *filename)
{
	char *p, *q;

	for (p = q = filename; *p != '\0'; p++)
		if (*p == slash/*'/'*/)
			q = p + 1;
	return q;
}

void cutFileName(char *filename)
{
	char *p, *q;

	for (p = filename, q = NULL; *p != '\0'; p++)
		if (*p == slash/*'/'*/)
			q = p + 1;
	if (q != NULL)
		*q = '\0';
}

char *getExtName(char *filename)
{
	char *p;
	char *q;

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

void cutExtName(char *filename)
{
	char *p;
	char *q;

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

int kanji1st(char *str, int pos)
{
	int	ret = 0;
	uint8_t	c;

	for (; pos > 0; pos--) {
		c = (uint8_t)str[pos];
		if (!((0x81 <= c && c <= 0x9f) || (0xe0 <= c && c <= 0xfc)))
			break;
		ret ^= 1;
	}
	return ret;
}

static int kanji2nd(char *str, int pos)
{
	int	ret = 0;
	uint8_t	c;

	while (pos-- > 0) {
		c = (uint8_t)str[pos];
		if (!((0x81 <= c && c <= 0x9f) || (0xe0 <= c && c <= 0xfc)))
			break;
		ret ^= 1;
	}
	return ret;
}


int ex_a2i(char *str, int min, int max)
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

void cutyen(char *str)
{
	int pos = strlen(str) - 1;

	if ((pos > 0) && (str[pos] == slash/*'/'*/))
		str[pos] = '\0';
}

void plusyen(char *str, int len)
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


void fname_mix(char *str, char *mix, int size)
{
	char *p;
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
