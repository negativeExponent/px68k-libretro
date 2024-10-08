/*
 * Copyright 2000 Masaru OKI
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
 * 3. The name of the author may not be used to endorse or promote products
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

#if !defined(__APPLE__)
#define _POSIX_C_SOURCE 199309L
#endif
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#include "peace.h"

#define SEC_TO_MS(sec) ((sec)*1000)
#define SEC_TO_US(sec) ((sec)*1000000)
#define SEC_TO_NS(sec) ((sec)*1000000000)

#define NS_TO_SEC(ns)   ((ns)/1000000000)
#define NS_TO_MS(ns)    ((ns)/1000000)
#define NS_TO_US(ns)    ((ns)/1000)

#ifdef _WIN32
uint32_t FAKE_GetTickCount(void)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	return tv.tv_usec / 1000 + tv.tv_sec * 1000;
}
#else
static struct timespec ts;

uint64_t millis(void)
{
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(SEC_TO_MS((uint64_t)ts.tv_sec) + NS_TO_MS((uint64_t)ts.tv_nsec));
}

uint64_t micros(void)
{
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(SEC_TO_US((uint64_t)ts.tv_sec) + NS_TO_US((uint64_t)ts.tv_nsec));
}

uint32_t FAKE_GetTickCount(void)
{
	return (uint32_t)(millis() & 0xffffffff);
}
#endif
