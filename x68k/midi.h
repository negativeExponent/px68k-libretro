#ifndef _WINX68K_MIDI_H
#define _WINX68K_MIDI_H

void MIDI_Init(void);
void MIDI_Cleanup(void);
void MIDI_Reset(void);
void MIDI_Stop(void);
uint8_t FASTCALL MIDI_Read(uint32_t adr);
void FASTCALL MIDI_Write(uint32_t adr, uint8_t data);
void MIDI_SetModule(void);
void FASTCALL MIDI_Timer(uint32_t clk);
int MIDI_SetMimpiMap(char *filename);
int MIDI_EnableMimpiDef(int enable);
void MIDI_DelayOut(uint32_t delay);

#endif /* _WINX68K_MIDI_H */
