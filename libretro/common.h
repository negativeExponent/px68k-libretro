#ifndef _LIBRETRO_WINX68K_COMMON_H
#define _LIBRETRO_WINX68K_COMMON_H

#ifdef _WIN32
#include "windows.h"
#endif

#include <string.h>

#ifndef _WIN32
#include "windows.h"
#endif

#include <libretro.h>
extern retro_log_printf_t log_cb;

#ifdef USE_LIBRETRO_VFS
#include <streams/file_stream.h>
#include <string/stdstring.h>
#include <file/file_path.h>
#endif

#undef FASTCALL
#define FASTCALL

#ifdef PSP
#ifdef MAX_PATH
#undef MAX_PATH
#endif
#define MAX_PATH 256
#endif

#endif
