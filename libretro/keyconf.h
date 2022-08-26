#ifndef _x68_keyconf
#define _x68_keyconf

extern HWND hWndKeyConf;
extern uint16_t  KeyConf_CodeW;
extern uint32_t KeyConf_CodeL;
extern char KeyConfMessage[255];
LRESULT CALLBACK KeyConfProc(HWND hWnd, uint32_t msg, WPARAM wp, LPARAM lp);

#endif // _x68_keyconf
