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

#include <file/file_path.h>
#include <string/stdstring.h>
#include <streams/file_stream.h>

#include "../x11/common.h"
#include "dosio.h"

extern char slash;

static char	curpath[MAX_PATH] = "";
static char *curfilep = curpath;

void dosio_init(void) {}
void dosio_term(void) {}

/**
 * wrapper to stdio.h's fopen using VFS routines
 */
static RFILE *fopen_wrapper(char *filename, const char *mode)
{
	RFILE *output        = NULL;
	int retro_mode       = RETRO_VFS_FILE_ACCESS_READ;
	bool position_to_end = false;

	if (string_is_empty(filename)) return NULL;
	if (path_is_directory(filename)) return NULL;

	if (strstr(mode, "r"))
	{
		retro_mode = RETRO_VFS_FILE_ACCESS_READ;
		if (strstr(mode, "+"))
		{
			retro_mode = RETRO_VFS_FILE_ACCESS_READ_WRITE |
			             RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING;
		}
	}
	else if (strstr(mode, "w"))
	{
		retro_mode = RETRO_VFS_FILE_ACCESS_WRITE;
		if (strstr(mode, "+")) retro_mode = RETRO_VFS_FILE_ACCESS_READ_WRITE;
	}
	else if (strstr(mode, "a"))
	{
		retro_mode =
		    RETRO_VFS_FILE_ACCESS_WRITE | RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING;
		position_to_end = true;
		if (strstr(mode, "+"))
		{
			retro_mode = RETRO_VFS_FILE_ACCESS_READ_WRITE |
			             RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING;
		}
	}

	output =
	    filestream_open(filename, retro_mode, RETRO_VFS_FILE_ACCESS_HINT_NONE);
	if (output && position_to_end)
		filestream_seek(output, 0, RETRO_VFS_SEEK_POSITION_END);

	return output;
}

/**
 * Open a file for reading ("r").
 * The file must exist.
 */
RFILE *file_open(char *filename)
{
	return fopen_wrapper(filename, "r");
}

/**
 * Open a file for both reading and writting ("r+").
 * The file must exist.
 */
RFILE *file_open_rw(char *filename)
{
	return fopen_wrapper(filename, "r+");
}

/**
 * Creates and empty file for and writing ("w+")
 * If a file with the same name already exists, its content
 * is erased and the file is considered as a new empty file.
 */
RFILE *file_create(char *filename)
{
	return fopen_wrapper(filename, "w+");
}

/**
 * Returns 0 on success
 */
int64_t file_seek(RFILE *stream, int64_t offset, int origin)
{
	int seek_position = -1;

	switch (origin)
	{
	case FSEEK_SET:
		seek_position = RETRO_VFS_SEEK_POSITION_START;
		break;
	case FSEEK_CUR:
		seek_position = RETRO_VFS_SEEK_POSITION_CURRENT;
		break;
	case FSEEK_END:
		seek_position = RETRO_VFS_SEEK_POSITION_END;
		break;
	}

	return filestream_seek(stream, offset, seek_position);
}

int64_t file_read(RFILE *stream, void *buffer, int64_t length)
{
	return filestream_read(stream, buffer, length);
}

int64_t file_write(RFILE *stream, void *buffer, int64_t length)
{
	return filestream_write(stream, buffer, length);
}

char *file_gets(RFILE *stream, char *buffer, size_t length)
{
	return filestream_gets(stream, buffer, length);
}

int64_t file_tell(RFILE *stream)
{
	return filestream_tell(stream);
}

void file_rewind(RFILE *stream)
{
	filestream_rewind(stream);
}

int file_eof(RFILE *stream)
{
	return filestream_eof(stream);
}

int file_close(RFILE *stream)
{
	filestream_close(stream);
	return 0;
}

/*
 * Sets a default path for current file operation
 */
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

/**
 * Open a file for reading ("r")
 * from a path provided from file_setcd().
 * The file must exist.
 */
RFILE *file_open_c(char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return fopen_wrapper(curpath, "r");
}

/**
 * Open a file for both reading and writing ("r+")
 * from a path provided from file_setcd().
 * The file must exist.
 */
RFILE *file_open_rw_c(char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return fopen_wrapper(curpath, "r+");
}

/**
 * Creates and empty file for and writing ("w")
 * from a path provided from file_setcd().
 * If a file with the same name already exists, its content
 * is erased and the file is considered as a new empty file.
 */
RFILE *file_create_c(char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return fopen_wrapper(curpath, "w");
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

static int UNUSED kanji2nd(char *str, int pos)
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
