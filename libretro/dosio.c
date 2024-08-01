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
#ifndef USE_LIBRETRO_VFS
#include <sys/param.h>
#endif

#include "dosio.h"

#ifdef _WIN32
#define SLASH '\\'
#else
#define SLASH '/'
#endif

static char  curpath[MAX_PATH] = "";
static char *curfilep = curpath;

void plusyen(char *s, size_t len)
{
	size_t pos = strlen(s);

	if (pos)
	{
		if (s[pos-1] == SLASH)
			return;
	}
	if ((pos + 2) >= len)
		return;
	s[pos++] = SLASH;
	s[pos]   = '\0';
}

void *file_open(const char *filename)
{
	void *ret;

#ifdef USE_LIBRETRO_VFS
	ret = filestream_open(filename,
		RETRO_VFS_FILE_ACCESS_READ_WRITE |
		RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING,
		RETRO_VFS_FILE_ACCESS_HINT_NONE);
	if (!ret)
	{
		ret = filestream_open(filename,
			RETRO_VFS_FILE_ACCESS_READ,
			RETRO_VFS_FILE_ACCESS_HINT_NONE);
		if (!ret)
			return NULL;
	}

	return ret;
#else
	ret = create_file(filename, GENERIC_READ | GENERIC_WRITE,
	    OPEN_EXISTING);
	if (!ret)
	{
		if (!(ret = create_file(filename, GENERIC_READ,
		    OPEN_EXISTING)))
			return NULL;
	}
	return ret;
#endif
}

size_t file_lread(void* handle, void *data, size_t length)
{
	int64_t readsize;

#ifdef USE_LIBRETRO_VFS
	readsize = filestream_read((RFILE *)handle, data, (int64_t)length);
	if (readsize <= 0)
		return 0;
#else
	if (read_file(handle, data, length, &readsize) == 0)
		return 0;
#endif
	return (size_t)readsize;
}

size_t file_lwrite(void *handle, void *data, size_t length)
{
	int64_t writesize;

#ifdef USE_LIBRETRO_VFS
	writesize = filestream_write((RFILE *)handle, data, (int64_t)length);
	if (writesize <= 0)
		return 0;
#else
	if (write_file(handle, data, length, &writesize) == 0)
		return 0;
#endif
	return (size_t)writesize;
}

void file_setcd(const char *exename)
{
	strncpy(curpath, exename, sizeof(curpath) - 1);
	plusyen(curpath, sizeof(curpath));
	curfilep  = curpath + strlen(exename) + 1;
	*curfilep = '\0';
}

void *file_open_c(const char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));
	return file_open(curpath);
}

void *file_create_c(const char *filename)
{
	strncpy(curfilep, filename, MAX_PATH - (curfilep - curpath));

#ifdef USE_LIBRETRO_VFS
	if (string_is_empty(filename)) return NULL;
	if (path_is_directory(filename)) return NULL;

	return filestream_open(filename,
		RETRO_VFS_FILE_ACCESS_READ_WRITE,
		RETRO_VFS_FILE_ACCESS_HINT_NONE);
#else
	return create_file(curpath, GENERIC_READ | GENERIC_WRITE,
	    CREATE_ALWAYS);
#endif
}
