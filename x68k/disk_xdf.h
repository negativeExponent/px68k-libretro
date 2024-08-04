#ifndef _X68K_XDF_H
#define _X68K_XDF_H

void XDF_Init(void);
void XDF_Cleanup(void);
int XDF_SetFD(int drive, char *filename);
int XDF_Eject(int drive);
int XDF_Seek(int drv, int trk, FDCID *id);
int XDF_ReadID(int drv, FDCID *id);
int XDF_WriteID(int drv, int trk, uint8_t *buf, int num);
int XDF_Read(int drv, FDCID *id, uint8_t *buf);
int XDF_ReadDiag(int drv, FDCID *id, FDCID *retid, uint8_t *buf);
int XDF_Write(int drv, FDCID *id, uint8_t *buf, int del);
int XDF_GetCurrentID(int drv, FDCID *id);

#endif /* _X68K_XDF_H */
