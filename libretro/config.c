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

#include <stdio.h>

#include "../x11/common.h"
#include "compiler.h"
#include "dosio.h"

/*
 * XXX: REWRITE ME!!!
 */
static int _WritePrivateProfileString_subr(
        FILEH **fp, int64_t pos, int64_t nowpos,
        const char *buf, const char *file)
{
	char *p         = NULL;
	int32_t st_size = 0;

	if (wrap_vfs_stat(file, &st_size) == 0)
		return 1;

	if (!(p = (char *)malloc(st_size)))
		return 1;

	file_rewind(*fp);
	if (file_read(*fp, p, st_size) < 1)
		goto out;
	file_close(*fp);

	*fp = file_create(file);
	if (*fp == NULL)
		goto out;
	if (file_write(*fp, p, pos) < 1)
		goto out;
	if (file_write(*fp, (char *)buf, strlen(buf)) < 1)
		goto out;
	if (((int64_t)st_size - nowpos) > 0)
	{
		if (file_write(*fp, p + nowpos, st_size - nowpos) < 1)
			goto out;
	}
	free(p);
	return 0;

out:
	free(p);
	return 1;
}

BOOL WritePrivateProfileString(
        const char *sect, const char *key,
        const char *str, const char *inifile)
{
	char lbuf[256];
	char newbuf[256];

	FILEH *fp     = NULL;
	int64_t pos   = 0;
	int found    = 0;
	int notfound = 0;
	int delta    = 0;

	if (wrap_vfs_stat(inifile, 0) == 1)
		fp = file_open(inifile);
	else
		fp = file_create(inifile);

	if (!fp)
		return FALSE;

	while (!file_eof(fp))
	{
		file_gets(fp, lbuf, sizeof(lbuf));
		/* XXX should be case insensitive */
		if (lbuf[0] == '['
			&& !strncasecmp(sect, &lbuf[1], strlen(sect))
			&& lbuf[strlen(sect) + 1] == ']')
		{
			found = 1;
			break;
		}
	}
	if (file_eof(fp) && !found)
	{
		/*
		 * Now create new section and key.
		 */
		file_rewind(fp);
		sprintf(newbuf, "[%s]\n", sect);
		if (file_write(fp, newbuf, strlen(newbuf)) < 1)
			goto writefail;
		sprintf(newbuf, "%s=%s\n", key, str);
		if (file_write(fp, newbuf, strlen(newbuf)) < 1)
			goto writefail;
		file_close(fp);
		return TRUE;
	}

	pos   = 0; /* gcc happy */
	found = 0;
	while (!file_eof(fp))
	{
		pos = file_tell(fp);
		file_gets(fp, lbuf, sizeof(lbuf));
		if (lbuf[0] == '[' && strchr(lbuf, ']'))
		{
			notfound = 1;
			break;
		}
		/* XXX should be case insensitive */
		if (!strncasecmp(key, lbuf, strlen(key))
			&& lbuf[strlen(key)] == '=')
		{
			found = 1;
			sprintf(newbuf, "%s=%s\n", key, str);
			delta = strlen(newbuf) - strlen(lbuf);
			if (delta == 0)
			{
				if (!strncasecmp(newbuf, lbuf, strlen(newbuf)))
					break;
				/* overwrite */
				file_seek(fp, pos, FSEEK_SET);
				if (file_write(fp, newbuf, strlen(newbuf)) < 1)
					goto writefail;
			}
			else if (delta > 0)
			{
				if (!_WritePrivateProfileString_subr(&fp, pos,
					file_tell(fp), newbuf, inifile))
					goto writefail;
			}
			else
			{
				if (!_WritePrivateProfileString_subr(&fp, pos,
					file_tell(fp), newbuf, inifile))
					goto writefail;
			}
			break;
		}
	}
	if (file_eof(fp) && !found)
	{
		/* Now create new key. */
		file_seek(fp, 0L, FSEEK_END);
		sprintf(newbuf, "%s=%s\n", key, str);
		if (file_write(fp, newbuf, strlen(newbuf)) < 1)
			goto writefail;
	}
	else if (notfound)
	{
		sprintf(newbuf, "%s=%s\n", key, str);
		if (!_WritePrivateProfileString_subr(&fp, pos,
			file_tell(fp), newbuf, inifile))
			goto writefail;
	}

	file_close(fp);
	return TRUE;

writefail:
	file_close(fp);
	return FALSE;
}

uint32_t GetPrivateProfileString(
        const char *sect, const char *key,
        const char *defvalue, char *buf, uint32_t len,
        const char *inifile)
{
	char lbuf[256];
	FILEH *fp = NULL;

	if (sect == NULL
	 || key == NULL
	 || defvalue == NULL
	 || buf == NULL
	 || len == 0
	 || inifile == NULL)
		return 0;

	memset(buf, 0, len);

	if (!(fp = file_open_rb(inifile)))
		goto nofile;
	while (!file_eof(fp))
	{
		file_gets(fp, lbuf, sizeof(lbuf));
		/* XXX should be case insensitive */
		if (lbuf[0] == '['
			&& !strncasecmp(sect, &lbuf[1], strlen(sect))
			&& lbuf[strlen(sect) + 1] == ']')
			break;
	}
	if (file_eof(fp))
		goto notfound;
	while (!file_eof(fp))
	{
		file_gets(fp, lbuf, sizeof(lbuf));
		if (lbuf[0] == '[' && strchr(lbuf, ']'))
			goto notfound;
		/* XXX should be case insensitive */
		if (!strncasecmp(key, lbuf, strlen(key))
			&& lbuf[strlen(key)] == '=')
		{
			char *dst, *src;
			src = &lbuf[strlen(key) + 1];
			dst = buf;
			while (*src != '\r' && *src != '\n' && *src != '\0')
				*dst++ = *src++;
			*dst = '\0';
			file_close(fp);
			return strlen(buf);
		}
	}
notfound:
#ifdef DEBUG
	p6logd(("[%s]:%s not found\n", sect, key));
#endif
	file_close(fp);
nofile:
	strncpy(buf, defvalue, len);
	/* not include nul */
	return strlen(buf);
}

uint32_t GetPrivateProfileInt(
	const char *sect, const char *key, int defvalue,
    const char *inifile)
{
	char lbuf[256];
	FILEH *fp = NULL;

	if (sect == NULL
		|| key == NULL
		|| inifile == NULL)
		return 0;

	fp = file_open_rb(inifile);
	if (fp == NULL)
		goto nofile;
	while (!file_eof(fp))
	{
		file_gets(fp, lbuf, sizeof(lbuf));
		/* XXX should be case insensitive */
		if (lbuf[0] == '['
			&& !strncasecmp(sect, &lbuf[1], strlen(sect))
			&& lbuf[strlen(sect) + 1] == ']')
			break;
	}
	if (file_eof(fp))
		goto notfound;
	while (!file_eof(fp))
	{
		file_gets(fp, lbuf, sizeof(lbuf));
		if (lbuf[0] == '[' && strchr(lbuf, ']'))
			goto notfound;
		/* XXX should be case insensitive */
		if (!strncasecmp(key, lbuf, strlen(key))
			&& lbuf[strlen(key)] == '=')
		{
			int value;
			sscanf(&lbuf[strlen(key) + 1], "%d", &value);
			file_close(fp);
			return value;
		}
	}
notfound:
	file_close(fp);
nofile:
	return defvalue;
}
