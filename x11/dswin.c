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

#include "common.h"
#include "compiler.h"
#include "state.h"

#include "../x68k/adpcm.h"
#include "../x68k/mercury.h"
#include "../x68k/midi.h"
#include "../x68k/opm.h"

#include "dswin.h"
#include "prop.h"

#include "state.h"


#define PCMBUF_SIZE 2 * 48000

static int16_t rsndbuf[PCMBUF_SIZE];
static int16_t pcmbuffer[PCMBUF_SIZE];

static int16_t *pbsp     = pcmbuffer;
static int16_t *pbrp     = pcmbuffer;
static int16_t *pbwp     = pcmbuffer;
static int16_t *pbep     = &pcmbuffer[PCMBUF_SIZE];

#ifdef HAVE_MERCURY
static int16_t UNUSED *pcmbufp  = pcmbuffer;
#endif

static uint32_t ratebase = 22050;

static int32_t DSound_PreCounter = 0;
static int audio_fd           = 1;

void DSound_Init(uint32_t rate)
{
	if (rate == 0)
	{
		audio_fd = -1;
		return;
	}

	ratebase = rate;
}

void DSound_Play(void)
{
	if (audio_fd >= 0)
	{
		ADPCM_SetVolume((uint8_t)Config.PCM_VOL);
		OPM_SetVolume((uint8_t)Config.OPM_VOL);
	}
}

void DSound_Stop(void)
{
	if (audio_fd >= 0)
	{
		ADPCM_SetVolume(0);
		OPM_SetVolume(0);
		MIDI_Stop();
	}
}

void DSound_Cleanup(void)
{
	if (audio_fd >= 0)
		audio_fd = -1;
}

static void sound_send(int32_t length)
{
	ADPCM_Update((int16_t *)pbwp, length, pbsp, pbep);
	OPM_Update((int16_t *)pbwp, length, pbsp, pbep);
#ifdef HAVE_MERCURY
	/* Mcry_Update((int16_t *)pcmbufp, length); */
#endif

	pbwp += length * 2;
	if (pbwp >= pbep)
		pbwp = pbsp + (pbwp - pbep);
}

void FASTCALL DSound_Send0(int32_t clock)
{
	int length = 0;

	if (audio_fd < 0)
		return;

	DSound_PreCounter += (ratebase * clock);

	while (DSound_PreCounter >= 10000000L)
	{
		length++;
		DSound_PreCounter -= 10000000L;
	}

	if (length == 0)
		return;

	sound_send(length);
}

static void FASTCALL DSound_Send(int32_t length)
{
	if (audio_fd < 0)
		return;
	sound_send(length);
}

int audio_samples_avail(void)
{
	if (pbrp <= pbwp)
		return (pbwp - pbrp) / 2;
	else
		return (pbep - pbrp) / 2 + (pbwp - pbsp) / 2;
}

void audio_samples_discard(int discard)
{
	int avail = audio_samples_avail();

	if (discard > avail)
		discard = avail;

	if (discard <= 0)
		return;

	if (pbrp > pbwp)
	{
		int availa = (pbep - pbrp) / 2;
		if (discard >= availa)
		{
			pbrp = pbsp;
			discard -= availa;
		}
	}

	pbrp += 2 * discard;
}

void raudio_callback(void *userdata, int32_t len)
{
	int32_t datalen = 0;
	int32_t lena = 0;
	int32_t lenb = 0;
	int16_t *buf;

cb_start:
	if (pbrp <= pbwp)
	{
		/* pcmbuffer
		 * +---------+-------------+----------+
		 * |         |/////////////|          |
		 * +---------+-------------+----------+
		 * A         A<--datalen-->A          A
		 * |         |             |          |
		 * pbsp     pbrp          pbwp       pbep
		 */

		datalen = pbwp - pbrp;

		if (datalen <= 0)
			return;

		/* needs more data */
		if (datalen < len)
			DSound_Send((len - datalen) / 2);

		/* change to TYPEC or TYPED */
		if (pbrp > pbwp)
			goto cb_start;

		buf = pbrp;
		pbrp += len;
		/* TYPEA: */
	}
	else
	{
		/* pcmbuffer
		 * +---------+-------------+----------+
		 * |/////////|             |//////////|
		 * +------+--+-------------+----------+
		 * <-lenb->  A             <---lena--->
		 * A         |             A          A
		 * |         |             |          |
		 * pbsp     pbwp          pbrp       pbep
		 */

		lena = pbep - pbrp;

		if (lena >= len)
		{
			buf = pbrp;
			pbrp += len;
			/* TYPEC: */
		}
		else
		{
			lenb = len - lena;

			if (pbwp - pbsp < lenb)
				DSound_Send((lenb - (pbwp - pbsp)) / 2);

			if (lena > 0) memcpy(rsndbuf, pbrp, lena * 2);
			if (lenb > 0) memcpy(&rsndbuf[lena], pbsp, lenb * 2);
			buf  = rsndbuf;
			pbrp = pbsp + lenb;
			/* TYPED: */
		}
	}
	memcpy(userdata, buf, len * 2);
}

int DSWIN_StateContext(void *f, int writing) {
	/* state_context_f(pcmbuffer, sizeof(pcmbuffer)); */
	state_context_f(&DSound_PreCounter, sizeof(DSound_PreCounter));

	return 1;
}
