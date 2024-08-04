#ifndef _X68K_MOUSE_H
#define _X68K_MOUSE_H

void Mouse_Init(void);
void Mouse_Event(int wparam, float dx, float dy);
void Mouse_SetData(void);
void Mouse_StartCapture(int flag);

#endif /*_X68K_MOUSE_H */
