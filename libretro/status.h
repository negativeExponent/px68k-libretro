#ifndef winx68k_statusbar_h
#define winx68k_statusbar_h

#ifdef __cplusplus
extern "C" {
#endif

#if 1

/* Misc: Used to trigger rumble when FDD is reading data.
 * Reset at every frame */
extern int FDD_IsReading;

#define	StatBar_Show(s)
#define	StatBar_UpdateTimer()
#define	StatBar_SetFDD(d,f)
#define	StatBar_HDD(s)

INLINE void StatBar_ParamFDD(int drv, int access, int insert, int blink)
{
	static int fdd_access[2], fdd_insert[2], fdd_blink[2];
	int update;

	if ((drv < 0) || (drv > 1))
		return;

	update = 0;
	if (fdd_access[drv] != access) {
		fdd_access[drv] = access;
		update = 1;
	}
	if (fdd_insert[drv] != insert) {
		fdd_insert[drv] = insert;
		update = 1;
	}
	if (fdd_blink[drv] != blink) {
		fdd_blink[drv] = blink;
		update = 1;
	}

	if (update)
		FDD_IsReading = ((fdd_insert[0] && fdd_access[0] == 2) || (fdd_insert[1] && fdd_access[1] == 2)) ? 1 : 0;
}

#else

void StatBar_Redraw(void);
void StatBar_Show(int sw);
void StatBar_Draw(void ** dis);
void StatBar_FDName(int drv, char* name);
void StatBar_FDD(int drv, int led, int col);
void StatBar_UpdateTimer(void);
void StatBar_SetFDD(int drv, char* file);
void StatBar_ParamFDD(int drv, int access, int insert, int blink);
void StatBar_HDD(int sw);

#endif

#ifdef __cplusplus
};
#endif

#endif //winx68k_statusbar_h
