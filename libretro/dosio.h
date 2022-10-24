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

#ifndef __NP2_DOSIO_H__
#define __NP2_DOSIO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define FSEEK_SET 0
#define FSEEK_CUR 1
#define FSEEK_END 2

#define STAT_IS_VALID     (1 << 0)
#define STAT_IS_DIRECTORY (1 << 1)

	struct DIRH
	{
		struct RDIR *dir;
		const char *d_name;
	};

	typedef struct DIRH DIRH;
	typedef struct RFILE FILEH;

	void dosio_init(void);
	void dosio_term(void);

	FILEH		*file_open(const char *filename);
	FILEH		*file_open_rb(const char *filename);
	FILEH		*file_create(const char *filename);
	char 		*file_gets(FILEH *handle, char *buffer, size_t length);
	int64_t		file_seek(FILEH *handle, int64_t offset, int origin);
	int64_t		file_read(FILEH *handle, void *buffer, int64_t length);
	int64_t		file_write(FILEH *handle, void *buffer, int64_t length);
	int64_t		file_tell(FILEH *handle);
	void		file_rewind(FILEH *handle);
	int			file_eof(FILEH *handle);
	int			file_close(FILEH *handle);

	int			wrap_vfs_stat(const char *path, int32_t *size);

	DIRH		*wrap_vfs_opendir(const char *filename);
	void		wrap_vfs_closedir(DIRH *rdir);
	int			wrap_vfs_readdir(DIRH *rdir);

	void 		file_setcd(char *exename);
	char 		*file_getcd(char *filename);
	FILEH		*file_open_c(char *filename);
	FILEH		*file_open_rb_c(char *filename);
	FILEH		*file_create_c(char *filename);

	char 		*getFileName(char *filename);
	void 		cutFileName(char *filename);
	char 		*getExtName(char *filename);
	void 		cutExtName(char *filename);
	void 		plusyen(char *str, int len);
	void 		cutyen(char *str);

	int 		kanji1st(char *str, int pos);
	int 		ex_a2i(char *str, int min, int max);

	void 		fname_mix(char *str, char *mix, int size);

#ifdef __cplusplus
};
#endif

#endif /* __NP2_DOSIO_H__ */
