#ifndef _win68_opm_fmgen
#define _win68_opm_fmgen

void		*opm_new(int32_t c, int32_t r);
void		opm_delete(void *opm);
void		opm_setrate(void* opm, uint32_t c, uint32_t r);
void		opm_reset(void *opm);
void		opm_count(void *opm, int32_t us);
uint32_t	opm_readstatus(void *opm);
void		opm_setreg(void *opm, uint32_t addr, uint32_t data);
void		opm_mix(void *opm, int16_t *buffer, int32_t length, int16_t *pbsp, int16_t *pbep);
void		opm_setvolume(void *opm, int32_t db);
void		opm_setchannelmask(void* opm, uint32_t mask);
int		 	opm_statecontext(void *opm, void *f, int writing);

#if 0
int OPM_Init(int32_t clock, int32_t rate);
void OPM_Cleanup(void);
void OPM_Reset(void);
void OPM_Update(int16_t *buffer, int32_t length, uint8_t *pbsp, uint8_t *pbep);
void FASTCALL OPM_Write(uint32_t adr, uint8_t data);
uint8_t FASTCALL OPM_Read(uint32_t adr);
void FASTCALL OPM_Timer(uint32_t step);
void OPM_SetVolume(uint8_t vol);
void OPM_SetRate(int32_t clock, int32_t rate);
void OPM_RomeoOut(uint32_t delay);
#endif

#ifdef HAVE_MERCURY
int M288_Init(int32_t clock, int32_t rate, const char* path);
void M288_Cleanup(void);
void M288_Reset(void);
void M288_Update(int16_t *buffer, int32_t length);
void FASTCALL M288_Write(uint32_t r, uint8_t v);
uint8_t FASTCALL M288_Read(uint16_t a);
void FASTCALL M288_Timer(uint32_t step);
void M288_SetVolume(uint8_t vol);
void M288_SetRate(int32_t clock, int32_t rate);
void M288_RomeoOut(uint32_t delay);
#endif /* !HAVE_MERCURY */

#endif /* _win68_opm_fmgen */
