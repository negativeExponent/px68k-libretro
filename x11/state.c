#include <stdio.h>

#include "common.h"
#include "state.h"

struct save_fp
{
	char *buf;
	uint64_t pos;
	int is_write;
};

void *save_open(const char *name, int writing)
{
	struct save_fp *fp;

	if (!name)
		return NULL;

	fp = malloc(sizeof(*fp));

	if (!fp)
		return NULL;

	fp->buf      = (char *)name;
	fp->pos      = 0;
	fp->is_write = writing;

	return fp;
}

void save_close(void *file)
{
	struct save_fp *fp = file;
	if (fp == NULL)
		return;

	if (fp->pos > STATE_SIZE)
		Error("ERROR: save buffer overflow detected\n");
	else if (fp->is_write && fp->pos < STATE_SIZE)
		/* make sure we don't save trash in leftover space */
		memset(fp->buf + fp->pos, 0, STATE_SIZE - fp->pos);
	free(fp);
}

uint64_t save_read(void *file, void *buf, uint64_t len)
{
	struct save_fp *fp = file;
	if (fp == NULL)
		return 0;

	memcpy(buf, fp->buf + fp->pos, len);
	fp->pos += len;
	return len;
}

uint64_t save_write(void *file, const void *buf, uint64_t len)
{
	struct save_fp *fp = file;
	if (fp == NULL)
		return 0;

	memcpy(fp->buf + fp->pos, buf, len);
	fp->pos += len;
	return len;
}

int64_t save_seek(void *file, uint64_t offs, int whence)
{
	struct save_fp *fp = file;
	uint64_t pos;

	if (fp == NULL)
		return -1;

	switch (whence)
	{
	case SEEK_CUR:
		pos = fp->pos + offs;
		break;
	case SEEK_SET:
		pos = offs;
		break;
	default:
		return -1;
	}

	if (pos <= STATE_SIZE)
	{
		fp->pos = pos;
		return 0;
	}

	return -1;
}

void PX68K_en32lsb(uint8_t *buf, uint32_t morp)
{
	buf[0] = morp;
	buf[1] = morp >> 8;
	buf[2] = morp >> 16;
	buf[3] = morp >> 24;
}

uint32_t PX68K_de32lsb(const uint8_t *morp)
{
	return (morp[0] | (morp[1] << 8) | (morp[2] << 16) | (morp[3] << 24));
}

int winx68k_StateContext(void *f, int writing);
int M68000_StateContext(void *f, int writing);
int GVRAM_StateContext(void *f, int writing);
int TVRAM_StateContext(void *f, int writing);
int CRTC_StateContext(void *f, int writing);
int VCtrl_StateContext(void *f, int writing);
int Pal_StateContext(void *f, int writing);
int BG_StateContext(void *f, int writing);
int DMA_StateContext(void *f, int writing);
int MFP_StateContext(void *f, int writing);
int FDC_StateContext(void *f, int writing);

int RTC_StateContext(void *f, int writing);
int SysPort_StateContext(void *f, int writing);
int IRQH_StateContext(void *f, int writing);
int IOC_StateContext(void *f, int writing);
int PIA_StateContext(void *f, int writing);
int SASI_StateContext(void *f, int writing);
int SCC_StateContext(void *f, int writing);
int FDD_StateContext(void *f, int writing);

int DSWIN_StateContext(void *f, int writing);
int ADPCM_StateContext(void *f, int writing);
int MIDI_StateContext(void *f, int writing);
int OPM_StateContext(void *f, int writing);

int PX68K_SaveStateMem(const char *file)
{
	void *f            = save_open(file, 1);
	uint8_t header[16] = { 0 };

	if (!f)
	{
		return 0;
	}

	header[0] = 'X';
	header[1] = '6';
	header[2] = '8';
	header[3] = 'K';

	PX68K_en32lsb(header + 8, PX68K_VERSION_NUMERIC);

	save_write(f, header, 16);

	winx68k_StateContext(f, 1);
	M68000_StateContext(f, 1);
	GVRAM_StateContext(f, 1);
	TVRAM_StateContext(f, 1);
	CRTC_StateContext(f, 1);
	VCtrl_StateContext(f, 1);
	Pal_StateContext(f, 1);
	BG_StateContext(f, 1);
	DMA_StateContext(f, 1);
	MFP_StateContext(f, 1);
	FDC_StateContext(f, 1);

	RTC_StateContext(f, 1);
	SysPort_StateContext(f, 1);
	IRQH_StateContext(f, 1);
	IOC_StateContext(f, 1);
	PIA_StateContext(f, 1);
	SASI_StateContext(f, 1);
	SCC_StateContext(f, 1);
	FDD_StateContext(f, 1);

	DSWIN_StateContext(f, 1);
	ADPCM_StateContext(f, 1);
	MIDI_StateContext(f, 1);
	OPM_StateContext(f, 1);

	save_close(f);

	return 1;
}

int PX68K_LoadStateMem(const char *file)
{
	void *f            = save_open(file, 0);
	uint8_t header[16] = { 0 };
	int stateversion;

	if (!f)
		return 0;

	save_read(f, header, 16);

	if (memcmp(header, "X68K", 4) != 0)
	{
		save_close(f);
		return 0;
	}

	stateversion = PX68K_de32lsb(header + 8);

	if (stateversion != PX68K_VERSION_NUMERIC)
	{
		save_close(f);
		return 0;
	}

	winx68k_StateContext(f, 0);
	M68000_StateContext(f, 0);
	GVRAM_StateContext(f, 0);
	TVRAM_StateContext(f, 0);
	CRTC_StateContext(f, 0);
	VCtrl_StateContext(f, 0);
	Pal_StateContext(f, 0);
	BG_StateContext(f, 0);
	DMA_StateContext(f, 0);
	MFP_StateContext(f, 0);
	FDC_StateContext(f, 0);

	RTC_StateContext(f, 0);
	SysPort_StateContext(f, 0);
	IRQH_StateContext(f, 0);
	IOC_StateContext(f, 0);
	PIA_StateContext(f, 0);
	SASI_StateContext(f, 0);
	SCC_StateContext(f, 0);
	FDD_StateContext(f, 0);

	DSWIN_StateContext(f, 0);
	ADPCM_StateContext(f, 0);
	MIDI_StateContext(f, 0);
	OPM_StateContext(f, 0);

	save_close(f);

	return 1;
}
