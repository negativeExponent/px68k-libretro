#include "../x11/common.h"

#include "dosio.h"

#include "fdc.h"
#include "fdd.h"
#include "disk_dim.h"

/*
	22-10-24
		https://pc98.org/main.html
		- respect header trackflag instead of overriding it,
		prevents unnecessary resizing upon eject or saving of image file
	22-10-08
		-add header identifier check
		-prevent image corruption when loading invalid or unknown headers
		 by freeing DIMImg[drv] upon failed DIM_SetFD
 */

/* DIM Image Header */
typedef struct {
	uint8_t type;
	uint8_t trkflag[170];
	uint8_t headerinfo[15];
	uint8_t date[4];
	uint8_t time[4];
	uint8_t comment[61];
	uint8_t overtrack;
} DIM_HEADER;

/* DIM Disk Type */
enum
{
	DIM_2HD = 0,
	DIM_2HS,
	DIM_2HC,
	DIM_2HDE,
	DIM_2HQ = 9
};

static const int SctLength[10] = {
	1024 * 8, 1024 * 9, 512 * 15, 1024 * 9, 0, 0, 0, 0, 0, 512 * 18
};

static char DIMFile[4][MAX_PATH];
static int DIMCur[4]      = { 0, 0, 0, 0 };
static int DIMTrk[4]      = { 0, 0, 0, 0 };
static uint8_t *DIMImg[4] = { 0, 0, 0, 0 };
static int DIMUpd[4]      = { 0, 0, 0, 0 };

void DIM_Init(void)
{
	int drv;

	for (drv = 0; drv < 4; drv++)
	{
		DIMCur[drv] = 0;
		DIMTrk[drv] = 0;
		DIMImg[drv] = 0;
		DIMUpd[drv] = 0;
		memset(DIMFile[drv], 0, MAX_PATH);
	}
}

void DIM_Cleanup(void)
{
	int drv;

	for (drv = 0; drv < 4; drv++)
		DIM_Eject(drv);
}

int DIM_SetFD(int drv, char *filename)
{
	FILEH *fp;
	DIM_HEADER *dh;
	uint32_t i, len;
	uint8_t *p;

	strncpy(DIMFile[drv], filename, MAX_PATH);
	DIMFile[drv][MAX_PATH - 1] = 0;

	DIMImg[drv] = (uint8_t *)malloc(1024 * 9 * 170 + sizeof(DIM_HEADER)); /* Maximum size */
	if (!DIMImg[drv])
		return FALSE;
	memset(DIMImg[drv], 0xe5, 1024 * 9 * 170 + sizeof(DIM_HEADER));
	fp = file_open_rb(DIMFile[drv]);
	if (!fp)
	{
		memset(DIMFile[drv], 0, MAX_PATH);
		FDD_SetReadOnly(drv);
		return FALSE;
	}

	file_seek(fp, 0, FSEEK_SET);
	if (file_read(fp, DIMImg[drv], sizeof(DIM_HEADER)) != sizeof(DIM_HEADER))
		goto dim_set_error;
	dh = (DIM_HEADER *)DIMImg[drv];
	/* check for header string identifier */
	if (strcmp((char *)&dh->headerinfo[0], "DIFC HEADER  ") != 0)
		goto dim_set_error;
	if (dh->type > 9)
		goto dim_set_error;
	len = SctLength[dh->type];
	if (!len)
		goto dim_set_error;
	p = DIMImg[drv] + sizeof(DIM_HEADER);
	for (i = 0; i < 170; i++)
	{
		if (dh->trkflag[i])
		{
			if (file_read(fp, p, len) != len)
				goto dim_set_error;
		}
		p += len;
	}
	file_close(fp);
	DIMUpd[drv] = 0;
	return TRUE;

dim_set_error:
	free(DIMImg[drv]);
	DIMImg[drv] = 0;
	DIMUpd[drv] = 0;
	file_close(fp);
	FDD_SetReadOnly(drv);
	return FALSE;
}

static int DIMSave(int drv)
{
	DIM_HEADER *dh;
	FILEH *fp;
	uint8_t *p;
	uint32_t len;
	int i;

	if (!FDD_IsReadOnly(drv))
	{
		dh  = (DIM_HEADER *)DIMImg[drv];
		p   = DIMImg[drv] + sizeof(DIM_HEADER);
		len = SctLength[dh->type];
		fp  = file_open(DIMFile[drv]);
		if (!fp)
			return FALSE;
		file_seek(fp, 0, FSEEK_SET);
		if (file_write(fp, DIMImg[drv], sizeof(DIM_HEADER)) != sizeof(DIM_HEADER))
			return FALSE;
		for (i = 0; i < 170; i++)
		{
			if (dh->trkflag[i])
			{
				if (file_write(fp, p, len) != len)
					return FALSE;
			}
			p += len;
		}
		file_close(fp);
	}
	return TRUE;
}

int DIM_Eject(int drv)
{
	int ret = TRUE;

	if (!DIMImg[drv])
	{
		memset(DIMFile[drv], 0, MAX_PATH);
		return FALSE;
	}

	if (DIMUpd[drv])
		ret = DIMSave(drv);
	
	free(DIMImg[drv]);
	DIMImg[drv] = 0;
	DIMUpd[drv] = 0;
	memset(DIMFile[drv], 0, MAX_PATH);
	return ret;
}

static void SetID(int drv, FDCID *id, int c, int h, int r)
{
	int type = DIMImg[drv][0];

	switch (type)
	{
	case DIM_2HD: /* 1024byte/sct, 8sct/trk */
		id->n = 3;
		break;
	case DIM_2HS: /* 1024byte/sct, 9sct/trk */
		if ((c) || (h) || (r != 1))
			r += 9;
		id->n = 3;
		break;
	case DIM_2HDE:
		if ((c) || (h) || (r != 1))
			h += 0x80;
		id->n = 3;
		break;
	case DIM_2HC: /* 512byte/sct, 15sct/trk */
	case DIM_2HQ: /* 512byte/sct, 18sct/trk */
		id->n = 2;
		break;
	}
	id->c = c;
	id->h = h;
	id->r = r;
}

static int IncTrk(int drv, int r)
{
	int type = DIMImg[drv][0];

	switch (type)
	{
	case DIM_2HD: /* 1024byte/sct, 8sct/trk */
		r = (r + 1) & 7;
		break;

	case DIM_2HS: /* 1024byte/sct, 9sct/trk */
		if (r > 8)
			r -= 9; /* 9SCDRV�� */
		/* fallthrough */
	case DIM_2HDE:
		r = (r + 1) % 9;
		break;

	case DIM_2HC: /* 512byte/sct, 15sct/trk */
		r = (r + 1) % 15;
		break;

	case DIM_2HQ: /* 512byte/sct, 18sct/trk */
		r = (r + 1) % 18;
		break;
	}
	return r;
}

static int GetPos(int drv, FDCID *id)
{
	int ret, c = id->c, h = id->h, r = id->r, n = id->n;
	int type = DIMImg[drv][0];

	switch (type)
	{
	case DIM_2HD: /* 1024byte/sct, 8sct/trk */
		if ((c < 0) || (c > 84) || (h < 0) || (h > 1) || (r < 1) || (r > 8) || (n != 3))
			return 0;
		ret = SctLength[type] * (c * 2 + h) + ((r - 1) << 10);
		ret += sizeof(DIM_HEADER);
		break;
	case DIM_2HS: /* 1024byte/sct, 9sct/trk */
		if (r > 9)
			r -= 9; /* 9SCDRV�� */
		if ((c < 0) || (c > 84) || (h < 0) || (h > 1) || (r < 1) || (r > 9) || (n != 3))
			return 0;
		ret = SctLength[type] * (c * 2 + h) + ((r - 1) << 10);
		ret += sizeof(DIM_HEADER);
		break;
	case DIM_2HDE:
		h &= 1; /* 9SCDRV�� */
		if ((c < 0) || (c > 84) || (h < 0) || (h > 1) || (r < 1) || (r > 9) || (n != 3))
			return 0;
		ret = SctLength[type] * (c * 2 + h) + ((r - 1) << 10);
		ret += sizeof(DIM_HEADER);
		break;
	case DIM_2HC: /* 512byte/sct, 15sct/trk */
		if ((c < 0) || (c > 84) || (h < 0) || (h > 1) || (r < 1) || (r > 15) || (n != 2))
			return 0;
		ret = SctLength[type] * (c * 2 + h) + ((r - 1) << 9);
		ret += sizeof(DIM_HEADER);
		break;
	case DIM_2HQ: /* 512byte/sct, 18sct/trk */
		if ((c < 0) || (c > 84) || (h < 0) || (h > 1) || (r < 1) || (r > 18) || (n != 2))
			return 0;
		ret = SctLength[type] * (c * 2 + h) + ((r - 1) << 9);
		ret += sizeof(DIM_HEADER);
		break;
	default:
		ret = 0;
		break;
	}

	return ret;
}

static int CheckTrack(int drv, int trk)
{
	DIM_HEADER *dh = (DIM_HEADER *)DIMImg[drv];

	switch (dh->type)
	{
	case DIM_2HD: /* 1024byte/sct, 8sct/trk */
		if (((trk > 153) && (!dh->overtrack)) || (!dh->trkflag[trk]))
			return 0;
		break;
	case DIM_2HS: /* 1024byte/sct, 9sct/trk */
		if (((trk > 159) && (!dh->overtrack)) || (!dh->trkflag[trk]))
			return 0;
		break;
	case DIM_2HDE:
		if (((trk > 159) && (!dh->overtrack)) || (!dh->trkflag[trk]))
			return 0;
		break;
	case DIM_2HC: /* 512byte/sct, 15sct/trk */
		if (((trk > 159) && (!dh->overtrack)) || (!dh->trkflag[trk]))
			return 0;
		break;
	case DIM_2HQ: /* 512byte/sct, 18sct/trk */
		if (((trk > 159) && (!dh->overtrack)) || (!dh->trkflag[trk]))
			return 0;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

int DIM_Seek(int drv, int trk, FDCID *id)
{
	if ((drv < 0) || (drv > 3))
		return FALSE;
	if ((trk < 0) || (trk > 169))
		return FALSE;
	if (!DIMImg[drv])
		return FALSE;
	if (DIMTrk[drv] != trk)
		DIMCur[drv] = 0;
	SetID(drv, id, trk >> 1, trk & 1, DIMCur[drv] + 1);
	DIMTrk[drv] = trk;
	return TRUE;
}

int DIM_GetCurrentID(int drv, FDCID *id)
{
	if ((drv < 0) || (drv > 3))
		return FALSE;
	if ((DIMTrk[drv] < 0) || (DIMTrk[drv] > 169))
		return FALSE;
	if (!DIMImg[drv])
		return FALSE;
	if (!CheckTrack(drv, DIMTrk[drv]))
		return FALSE;
	SetID(drv, id, DIMTrk[drv] >> 1, DIMTrk[drv] & 1, DIMCur[drv] + 1);
	return TRUE;
}

int DIM_ReadID(int drv, FDCID *id)
{
	if ((drv < 0) || (drv > 3))
		return FALSE;
	if ((DIMTrk[drv] < 0) || (DIMTrk[drv] > 169))
		return FALSE;
	if (!DIMImg[drv])
		return FALSE;
	if (!CheckTrack(drv, DIMTrk[drv]))
		return FALSE;
	SetID(drv, id, DIMTrk[drv] >> 1, DIMTrk[drv] & 1, DIMCur[drv] + 1);
	DIMCur[drv] = IncTrk(drv, DIMCur[drv]);
	return TRUE;
}

int DIM_WriteID(int drv, int trk, uint8_t *buf, int num)
{
#if 0
	int i;
	uint8_t c = buf[num<<2];
	if ( (drv<0)||(drv>3) ) return FALSE;
	if ( (trk<0)||(trk>169) ) return FALSE;
	if ( !DIMImg[drv] ) return FALSE;
	if ( num!=8 ) return FALSE;
	for (i=0; i<8; i++, buf+=4) {
		if ( (((buf[0]<<1)+buf[1])!=trk)||(buf[2]<1)||(buf[2]>8)||(buf[3]!=3) ) return FALSE;
	}
	DIMTrk[drv] = trk;
	return TRUE;
#else
	(void)drv;
	(void)trk;
	(void)buf;
	(void)num;
	return FALSE;
#endif
}

int DIM_Read(int drv, FDCID *id, uint8_t *buf)
{
	int pos;
	if ((drv < 0) || (drv > 3))
		return FALSE;
	if (!DIMImg[drv])
		return FALSE;
	if ((((id->c << 1) + (id->h & 1)) != DIMTrk[drv]))
		return FALSE;
	if (!CheckTrack(drv, (id->c << 1) + (id->h & 1)))
		return FALSE;
	pos = GetPos(drv, id);
	if (!pos)
		return FALSE;
	memcpy(buf, DIMImg[drv] + pos, (id->n == 2) ? 512 : 1024);
	DIMCur[drv] = IncTrk(drv, id->r - 1);
	return TRUE;
}

int DIM_ReadDiag(int drv, FDCID *id, FDCID *retid, uint8_t *buf)
{
	int pos;
	(void)id;
	if ((drv < 0) || (drv > 3))
		return FALSE;
	if (!DIMImg[drv])
		return FALSE;
	if (!CheckTrack(drv, DIMTrk[drv]))
		return FALSE;
	SetID(drv, retid, DIMTrk[drv] >> 1, DIMTrk[drv] & 1, DIMCur[drv] + 1);
	pos = GetPos(drv, retid);
	if (!pos)
		return FALSE;
	memcpy(buf, DIMImg[drv] + pos, (retid->n == 2) ? 512 : 1024);
	DIMCur[drv] = IncTrk(drv, DIMCur[drv]);
	return TRUE;
}

int DIM_Write(int drv, FDCID *id, uint8_t *buf, int del)
{
	int pos;
	(void)del;
	if ((drv < 0) || (drv > 3))
		return FALSE;
	if (!DIMImg[drv])
		return FALSE;
	if ((((id->c << 1) + (id->h & 1)) != DIMTrk[drv]))
		return FALSE;
	if (!CheckTrack(drv, (id->c << 1) + (id->h & 1)))
		return FALSE;
	pos = GetPos(drv, id);
	if (!pos)
		return FALSE;
	memcpy(DIMImg[drv] + pos, buf, (id->n == 2) ? 512 : 1024);
	DIMCur[drv] = IncTrk(drv, id->r - 1);
	if (!DIMUpd[drv])
		DIMUpd[drv] = 1;
	return TRUE;
}
