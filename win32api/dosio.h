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

#include "appftype.h"

#define FSEEK_SET 0
#define FSEEK_CUR 1
#define FSEEK_END 2

#ifdef __cplusplus
extern "C"
{
#endif
	void dosio_init(void);
	void dosio_term(void);

	void *file_open(char *filename);
	void *file_create(char *filename, int ftype);
	uint32_t file_seek(void *handle, long pointer, int16_t mode);
	uint32_t file_read(void *handle, void *data, uint32_t length);
	uint32_t file_write(void *handle, void *data, uint32_t length);
	uint32_t file_zeroclr(void *handle, uint32_t length);
	uint16_t file_lineread(void *handle, void *data, uint16_t length);
	int16_t file_close(void *handle);
	int16_t file_attr(char *filename);

	void file_setcd(char *exename);
	char *file_getcd(char *filename);
	void *file_open_c(char *filename);
	void *file_create_c(char *filename, int ftype);
	int16_t file_attr_c(char *filename);

	int file_getftype(char *filename);

	void dosdateset(uint8_t *dat);
	void dostimeset(uint8_t *dat);

	char *getFileName(char *filename);
	void cutFileName(char *filename);
	char *getExtName(char *filename);
	void cutExtName(char *filename);
	void plusyen(char *str, int len);
	void cutyen(char *str);

	int kanji1st(char *str, int pos);
	int ex_a2i(char *str, int min, int max);

	void fname_mix(char *str, char *mix, int size);

#ifdef __cplusplus
};
#endif

#endif /* __NP2_DOSIO_H__ */
