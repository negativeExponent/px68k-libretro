/* ---------------------------------------------------------------------------------------
 *  FDD.C - 内蔵FDD Unit（イメージファイルの管理とFD挿抜割り込みの発生）
 */

#include "common.h"
#include "fdd.h"
#include "disk_d88.h"
#include "disk_dim.h"
#include "disk_xdf.h"
#include "fdc.h"
#include "ioc.h"
#include "irqh.h"
#include "status.h"

typedef struct {
	int SetDelay[4];
	int Types[4];
	int ROnly[4];
	int EMask[4];
	int Blink[4];
	int Access;
} FDDINFO;

enum { FD_Non, FD_XDF, FD_D88, FD_DIM }; /* do not re-order */

static FDDINFO fdd;
static int (*SetFD[4])(int, char *)                         = { 0, XDF_SetFD, D88_SetFD, DIM_SetFD };
static int (*Eject[4])(int)                                 = { 0, XDF_Eject, D88_Eject, DIM_Eject };
static int (*Seek[4])(int, int, FDCID *)                    = { 0, XDF_Seek, D88_Seek, DIM_Seek };
static int (*ReadID[4])(int, FDCID *)                       = { 0, XDF_ReadID, D88_ReadID, DIM_ReadID };
static int (*WriteID[4])(int, int, uint8_t *, int)          = { 0, XDF_WriteID, D88_WriteID, DIM_WriteID };
static int (*Read[4])(int, FDCID *, uint8_t *)              = { 0, XDF_Read, D88_Read, DIM_Read };
static int (*ReadDiag[4])(int, FDCID *, FDCID *, uint8_t *) = { 0, XDF_ReadDiag, D88_ReadDiag, DIM_ReadDiag };
static int (*Write[4])(int, FDCID *, uint8_t *, int)        = { 0, XDF_Write, D88_Write, DIM_Write };
static int (*GetCurrentID[4])(int, FDCID *) = { 0, XDF_GetCurrentID, D88_GetCurrentID, DIM_GetCurrentID };

static void ConvertCapital(unsigned char *buf)
{
	for (; *buf; buf++)
	{
		if (((*buf >= 0x80) && (*buf <= 0x9f)) || (*buf >= 0xe0))
		{
			buf++;
		}
		else if ((*buf >= 'a') && (*buf <= 'z'))
			*buf -= 0x20;
	}
}

static int GetDiskType(char *file)
{
	char tmp[8], *p;

	p = strrchr(file, '.');
	if (p)
	{
		memset(tmp, 0, 8);
		strncpy(tmp, p + 1, 3);
		ConvertCapital((unsigned char *)tmp);
		if ((!strncmp(tmp, "D88", 3)) || (!strncmp(tmp, "88D", 3)))
			return FD_D88;
		else if (!strncmp(tmp, "DIM", 3))
			return FD_DIM;
	}
	return FD_XDF;
}

static int32_t FASTCALL FDD_Int(int32_t irq)
{
	IRQH_IRQCallBack(irq);
	if (irq == 1)
		return ((int32_t)IOC_IntVect + 1);
	return IRQ_DEFAULT_VECTOR;
}

/* FDせっと - すぐには割り込み上げないです */
void FDD_SetFD(int drive, char *filename, int readonly)
{
	int type = GetDiskType(filename);

	if ((drive < 0) || (drive > 3))
		return;
	FDD_EjectFD(drive);
	if (SetFD[type])
	{
		if (SetFD[type](drive, filename))
		{
			fdd.Types[drive] = type;
			fdd.ROnly[drive] |= readonly;
			fdd.SetDelay[drive] = 3;
			fdd.EMask[drive]    = 0;
			fdd.Blink[drive]    = 0;
			StatBar_SetFDD(drive, filename);
			StatBar_ParamFDD(drive,
			    (fdd.Types[drive] != FD_Non) ? ((fdd.Access == drive) ? 2 : 1) : 0,
			    ((fdd.Types[drive] != FD_Non) && (!fdd.EMask[drive])) ? 1 : 0, (fdd.Blink[drive]) ? 1 : 0);
		}
	}
}

void FDD_EjectFD(int drive)
{
	int type;

	if ((drive < 0) || (drive > 3))
		return;
	type = fdd.Types[drive];
	if (Eject[type])
	{
		Eject[type](drive);
		if (IOC_IntStat & 2)
			IRQH_Int(1, &FDD_Int);
	}
	fdd.Types[drive] = FD_Non;
	fdd.ROnly[drive] = 0;
	fdd.EMask[drive] = 0;
	fdd.Blink[drive] = 0;
	StatBar_SetFDD(drive, "");
	StatBar_ParamFDD(drive, (fdd.Types[drive] != FD_Non) ? ((fdd.Access == drive) ? 2 : 1) : 0,
	    ((fdd.Types[drive] != FD_Non) && (!fdd.EMask[drive])) ? 1 : 0, (fdd.Blink[drive]) ? 1 : 0);
}

/* Eject Mask / Blink / AccessDrive */
void FDD_SetEMask(int drive, int emask)
{
	if ((drive < 0) || (drive > 3))
		return;
	if (fdd.EMask[drive] == emask)
		return;
	fdd.EMask[drive] = emask;
	StatBar_ParamFDD(drive, (fdd.Types[drive] != FD_Non) ? ((fdd.Access == drive) ? 2 : 1) : 0,
	    ((fdd.Types[drive] != FD_Non) && (!fdd.EMask[drive])) ? 1 : 0, (fdd.Blink[drive]) ? 1 : 0);
}

void FDD_SetAccess(int drive)
{
	if (fdd.Access == drive)
		return;
	fdd.Access = drive;
	StatBar_ParamFDD(0, (fdd.Types[0] != FD_Non) ? ((fdd.Access == 0) ? 2 : 1) : 0,
	    ((fdd.Types[0] != FD_Non) && (!fdd.EMask[0])) ? 1 : 0, (fdd.Blink[0]) ? 1 : 0);
	StatBar_ParamFDD(1, (fdd.Types[1] != FD_Non) ? ((fdd.Access == 1) ? 2 : 1) : 0,
	    ((fdd.Types[1] != FD_Non) && (!fdd.EMask[1])) ? 1 : 0, (fdd.Blink[1]) ? 1 : 0);
}

void FDD_SetBlink(int drive, int blink)
{
	if ((drive < 0) || (drive > 3))
		return;
	if (fdd.Blink[drive] == blink)
		return;
	fdd.Blink[drive] = blink;
	StatBar_ParamFDD(drive, (fdd.Types[drive] != FD_Non) ? ((fdd.Access == drive) ? 2 : 1) : 0,
	    ((fdd.Types[drive] != FD_Non) && (!fdd.EMask[drive])) ? 1 : 0, (fdd.Blink[drive]) ? 1 : 0);
}

void FDD_Init(void)
{
	memset(&fdd, 0, sizeof(FDDINFO));
	fdd.Access = -1;
	D88_Init();
	XDF_Init();
	DIM_Init();
}

void FDD_Cleanup(void)
{
	D88_Cleanup();
	XDF_Cleanup();
	DIM_Cleanup();
}

void FDD_Reset(void)
{
	int i;

	FDD_SetAccess(-1);
	for (i = 0; i < 4; i++)
	{
		FDD_SetEMask(i, 0);
		FDD_SetBlink(i, 0);
	}
}

/* FD入れ替えが起こっていたら割り込み発生 */
void FDD_SetFDInt(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		if (fdd.SetDelay[i])
		{
			fdd.SetDelay[i]--;
			if (fdd.SetDelay[i] <= 0)
			{
				if (IOC_IntStat & 2)
					IRQH_Int(1, &FDD_Int);
				fdd.SetDelay[i] = 0;
			}
		}
	}
}

int FDD_Seek(int drv, int trk, FDCID *id)
{
	int type;

	if ((drv < 0) || (drv > 3))
		return FALSE;
	type = fdd.Types[drv];
	if (Seek[type])
		return Seek[type](drv, trk, id);
	return FALSE;
}

int FDD_ReadID(int drv, FDCID *id)
{
	int type;

	if ((drv < 0) || (drv > 3))
		return FALSE;
	type = fdd.Types[drv];
	if (ReadID[type])
		return ReadID[type](drv, id);
	return FALSE;
}

int FDD_WriteID(int drv, int trk, uint8_t *buf, int num)
{
	int type;

	if ((drv < 0) || (drv > 3))
		return FALSE;
	type = fdd.Types[drv];
	if (WriteID[type])
		return WriteID[type](drv, trk, buf, num);
	return FALSE;
}

int FDD_Read(int drv, FDCID *id, uint8_t *buf)
{
	int type;

	if ((drv < 0) || (drv > 3))
		return FALSE;
	type = fdd.Types[drv];
	if (Read[type])
		return Read[type](drv, id, buf);
	return FALSE;
}

int FDD_ReadDiag(int drv, FDCID *id, FDCID *retid, uint8_t *buf)
{
	int type;

	if ((drv < 0) || (drv > 3))
		return FALSE;
	type = fdd.Types[drv];
	if (ReadDiag[type])
		return ReadDiag[type](drv, id, retid, buf);
	return FALSE;
}

int FDD_Write(int drv, FDCID *id, uint8_t *buf, int del)
{
	int type;

	if ((drv < 0) || (drv > 3))
		return FALSE;
	type = fdd.Types[drv];
	if (Write[type])
		return Write[type](drv, id, buf, del);
	return FALSE;
}

int FDD_GetCurrentID(int drv, FDCID *id)
{
	int type;

	if ((drv < 0) || (drv > 3))
		return FALSE;
	type = fdd.Types[drv];
	if (GetCurrentID[type])
		return GetCurrentID[type](drv, id);
	return FALSE;
}

int FDD_IsReady(int drv)
{
	if ((drv < 0) || (drv > 3))
		return FALSE;
	if ((fdd.Types[drv] != FD_Non) && (!fdd.SetDelay[drv]))
		return TRUE;
	return FALSE;
}

int FDD_IsReadOnly(int drv)
{
	if ((drv < 0) || (drv > 3))
		return FALSE;
	return fdd.ROnly[drv];
}

void FDD_SetReadOnly(int drv)
{
	fdd.ROnly[drv] |= 1;
}
