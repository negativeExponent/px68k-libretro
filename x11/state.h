#ifndef _X68K_STATE_H
#define _X68K_STATE_H

#include "compiler.h"

#define STATE_SIZE (16 * 1024 * 1024)

#define PX68K_VERSION_MAJOR 0
#define PX68K_VERSION_MINOR 15
#define PX68K_VERSION_PATCH 0

#define PX68K_VERSION_NUMERIC ((PX68K_VERSION_MAJOR * 10000) + (PX68K_VERSION_MINOR * 100) + (PX68K_VERSION_PATCH))

void *save_open(const char *name, int writing);
void save_close(void *file);
int64_t save_seek(void *file, uint64_t offs, int whence);
uint64_t save_read(void *file, void *buf, uint64_t len);
uint64_t save_write(void *file, const void *buf, uint64_t len);
uint64_t save_get_last_size(void);

uint32_t PX68K_de32lsb(const uint8_t *morp);
void PX68K_en32lsb(uint8_t *buf, uint32_t morp);

static INLINE uint64_t save_handler(void *file, void *buf, uint64_t size, int writing)
{
	if (writing)
	{
		return save_write(file, buf, size);
	}
	if (!writing)
	{
		return save_read(file, buf, size);
	}
	return 0;
}

#define state_context_f(ptr, size) save_handler(f, ptr, size, writing)

int PX68K_SaveStateMem(const char *file);
int PX68K_LoadStateMem(const char *file);

#endif
