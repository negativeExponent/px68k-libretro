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

#include        <stdint.h>
#include	"common.h"
#include	"dswin.h"
#include	"prop.h"
#include	"adpcm.h"
#include	"mercury.h"
#include	"fmg_wrap.h"

#define PCMBUF_SIZE 2*48000

static int16_t pcmbuffer[PCMBUF_SIZE];
static int16_t rsndbuf  [PCMBUF_SIZE];
static int32_t snd_precounter = 0;

int16_t *pbsp = pcmbuffer;
int16_t *pbrp = pcmbuffer, *pbwp = pcmbuffer;
int16_t *pbep = &pcmbuffer[PCMBUF_SIZE];

static int ratebase;

void DSound_Init(int rate)
{
   ratebase = rate;
}

void DSound_Play(void)
{
	ADPCM_SetVolume((uint8_t)Config.PCM_VOL);
	OPM_SetVolume((uint8_t)Config.OPM_VOL);	
}

void DSound_Stop(void)
{
	ADPCM_SetVolume(0);
	OPM_SetVolume(0);	
}

static void sound_send(int length)
{
   int rate = ratebase;

   ADPCM_Update(pbwp, length, rate, pbsp, pbep);
   OPM_Update(pbwp, length, rate, pbsp, pbep);

   pbwp += length * 2;
   if (pbwp >= pbep)
      pbwp = pbsp + (pbwp - pbep);
}

void DSound_Send0(int32_t clock)
{
	int length = 0;

	snd_precounter += (ratebase * clock);

	while (snd_precounter >= 10000000L)
	{
		length++;
		snd_precounter -= 10000000L;
	}

	if (length != 0)
		sound_send(length);
}

int audio_samples_avail(void)
{
   if (pbrp <= pbwp)
      return (pbwp - pbrp) / 2;
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

void raudio_callback(void *userdata, int len)
{
   int lena, lenb, datalen;
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
      {
	      int length = (len - datalen) / 2;
	      sound_send(length);
      }

      /* change to TYPEC or TYPED */
      if (pbrp > pbwp)
         goto cb_start;

      buf = pbrp;
      pbrp += len;
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
      }
      else
      {
         lenb = len - lena;

         if (pbwp - pbsp < lenb)
         {
            int length = (lenb - (pbwp - pbsp)) / 2;
            sound_send(length);
	      }

         if (lena > 0) memcpy(rsndbuf, pbrp, lena * 2);
         if (lenb > 0) memcpy(&rsndbuf[lena], pbsp, lenb * 2);
         buf  = rsndbuf;
         pbrp = pbsp + lenb;
      }
   }
   memcpy(userdata, buf, len * 2);
}
