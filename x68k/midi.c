/*
 *  MIDI.C - MIDI Board (CZ-6BM1) emulator
 *                           Powered by ぷにゅさん〜
 *
 * 4/18 未明: エクスクルーシヴがうまく通らないのを修正
 * 4/18 朝　: レナムで鳴らなかったのを修正
 * 4/18 昼　: エクスクルーシヴ送信完了を完全に待つ事でドラキュラおっけー
 *
 * ToDo: ・エクスクルーシヴ送信中(例えばドラキュラの音色設定中)に
 *         流石に1MHzまで落ち込むのは…
 *         MIDIの状態を返すポートを教えてもらうこと〜
 *       ・MT-32でのランニングステータスの仕様をチェック
 *       ・終了時の音源のリセット
 *       ・IPLリセット時は実機でもリセットされない筈だが、
 *         ここら辺は好みなので configで設定できてもいいかも
 */


#include "common.h"
#include "prop.h"
#include "winx68k.h"
#include "fileio.h"
#include "mmsystem.h"
#include "x68kmemory.h"
#include "irqh.h"
#include "midi.h"
#include "m68000.h"

#define MIDIBUFFERS 1024			/* 1024は流石に越えないでしょう^_^; */
#define MIDIBUFTIMER 3200			/* 10MHz / (31.25K / 10bit) = 3200 が正解になります...  */
#define MIDIFIFOSIZE 256
#define MIDIDELAYBUF 4096			/* 31250/10 = 3125 byts (1s分) あればおっけ？ */

/* 各機種リセット用に一応。 */
enum {
	MIDI_NOTUSED,
	MIDI_DEFAULT,
	MIDI_MT32,
	MIDI_CM32L,
	MIDI_CM64,
	MIDI_CM300,
	MIDI_CM500,
	MIDI_SC55,
	MIDI_SC88,
	MIDI_LA,				/* Added without meaning */
	MIDI_GM,
	MIDI_GS,
	MIDI_XG,
};

HMIDIOUT	hOut = 0;
MIDIHDR		hHdr;
int32_t		MIDI_CTRL;
int32_t		MIDI_POS;
int32_t		MIDI_SYSCOUNT;
uint8_t		MIDI_LAST;
uint8_t		MIDI_BUF[MIDIBUFFERS];
uint8_t		MIDI_EXCVBUF[MIDIBUFFERS];
uint8_t		MIDI_EXCVWAIT;

uint8_t		MIDI_RegHigh = 0;				/* X68K用 */
uint8_t		MIDI_Playing = 0;				/* マスタスイッチ */
uint8_t		MIDI_Vector = 0;
uint8_t		MIDI_IntEnable = 0;
uint8_t		MIDI_IntVect = 0;
uint8_t		MIDI_IntFlag = 0;
uint32_t	MIDI_Buffered = 0;
long		MIDI_BufTimer = 3333;
uint8_t		MIDI_R05 = 0;
uint32_t	MIDI_GTimerMax = 0;
uint32_t	MIDI_MTimerMax = 0;
long		MIDI_GTimerVal = 0;
long		MIDI_MTimerVal = 0;
uint8_t		MIDI_TxFull = 0;
uint8_t		MIDI_MODULE = MIDI_NOTUSED;

static uint8_t MIDI_ResetType[5] = {
	MIDI_LA, MIDI_GM, MIDI_GS, MIDI_XG
};

typedef struct {
	uint32_t time;
	uint8_t msg;
} DELAYBUFITEM;

static DELAYBUFITEM DelayBuf[MIDIDELAYBUF];
static int32_t DBufPtrW = 0;
static int32_t DBufPtrR = 0;

/*
 * ねこみぢ6、MIMPIトーンマップ対応関係
 */

enum {
	MIMPI_LA = 0,
	MIMPI_PCM,
	MIMPI_GS,
	MIMPI_RHYTHM,
};

static	uint8_t		LOADED_TONEMAP = 0;
static	uint8_t		ENABLE_TONEMAP = 0;
static	uint8_t		TONE_CH[16];
static	uint8_t		TONEBANK[3][128];
static	uint8_t		TONEMAP[3][128];

static uint8_t EXCV_MTRESET[] = { 0xfe, 0xfe, 0xfe};
static uint8_t EXCV_GMRESET[] = { 0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7};
static uint8_t EXCV_GSRESET[] = { 0xf0, 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7f, 0x00, 0x41, 0xf7};
static uint8_t EXCV_XGRESET[] = { 0xf0, 0x43, 0x10, 0x4C, 0x00, 0x00, 0x7E, 0x00, 0xf7};

#define	MIDICTRL_READY		0
#define	MIDICTRL_2uint8_tS	1
#define	MIDICTRL_3uint8_tS	2
#define	MIDICTRL_EXCLUSIVE	3
#define	MIDICTRL_TIMECODE	4
#define MIDICTRL_SYSTEM		5

#define	MIDI_EXCLUSIVE		0xf0
#define MIDI_TIMECODE		0xf1
#define MIDI_SONGPOS		0xf2
#define MIDI_SONGSELECT		0xf3
#define	MIDI_TUNEREQUEST	0xf6
#define	MIDI_EOX			0xf7
#define	MIDI_TIMING			0xf8
#define MIDI_START			0xfa
#define MIDI_CONTINUE		0xfb
#define	MIDI_STOP			0xfc
#define	MIDI_ACTIVESENSE	0xfe
#define	MIDI_SYSTEMRESET	0xff

#define MIDIOUTS(a,b,c) (((uint32_t)c << 16) | ((uint32_t)b << 8) | (uint32_t)a)

/*
 *   割り込み
 */
uint32_t FASTCALL MIDI_Int(uint8_t irq)
{
	uint32_t ret;
	IRQH_IRQCallBack(irq);
	if ( irq==4 )
	{
		ret = (uint32_t)(MIDI_Vector|MIDI_IntVect);
	}
	else
	{
		ret = (uint32_t)(-1);
	}

	return ret;
}


/*
 *   たいまを進める
 */
void FASTCALL MIDI_Timer(uint32_t clk)
{
	if ( !Config.MIDI_SW ) return;	/* MIDI OFF時は帰る */

	MIDI_BufTimer -= clk;
	if (MIDI_BufTimer<0)
	{
		MIDI_BufTimer += MIDIBUFTIMER;
		if (MIDI_Buffered)
		{
			MIDI_Buffered--;
			if ( (MIDI_Buffered<MIDIFIFOSIZE)&&(MIDI_IntEnable&0x40) )		/* Tx FIFO Empty Interrupt（エトプリ） */
			{
				MIDI_IntFlag |= 0x40;
				MIDI_IntVect = 0x0c;
				IRQH_Int(4, &MIDI_Int);
			}
		}
	}

	if (MIDI_MTimerMax)
	{
		 MIDI_MTimerVal -= clk;
		if (MIDI_MTimerVal<0)		/* みぢたいまー割り込み（魔法大作戦） */
		{
			while (MIDI_MTimerVal<0) MIDI_MTimerVal += MIDI_MTimerMax*80;
			if ( (!(MIDI_R05&0x80))&&(MIDI_IntEnable&0x02) )
			{
				MIDI_IntFlag |= 0x02;
				MIDI_IntVect = 0x02;
				IRQH_Int(4, &MIDI_Int);
			}
		}
	}

	if (MIDI_GTimerMax)
	{
		MIDI_GTimerVal -= clk;
		if (MIDI_GTimerVal<0)		/* じぇねらるたいまー割り込み（RCD.X） */
		{
			while (MIDI_GTimerVal<0) MIDI_GTimerVal += MIDI_GTimerMax*80;
			if ( MIDI_IntEnable&0x80 )
			{
				MIDI_IntFlag |= 0x80;
				MIDI_IntVect = 0x0e;
				IRQH_Int(4, &MIDI_Int);
			}
		}
	}
}


/*
 *   MIDIモジュールの設定
 */
void MIDI_SetModule(void)
{
	if (Config.MIDI_SW)
		MIDI_MODULE = MIDI_ResetType[Config.MIDI_Type];
	else
		MIDI_MODULE = MIDI_NOTUSED;
}


/*
 *   えくすくるーしぶ ごー
 */
void MIDI_Sendexclusive(uint8_t *excv, int32_t length)
{
	/* エクスクルーシヴを送ります */
	memcpy(MIDI_EXCVBUF, excv, length);
	hHdr.lpData = MIDI_EXCVBUF;
	hHdr.dwFlags = 0;
	hHdr.dwBufferLength = length;
	midiOutPrepareHeader(hOut, &hHdr, sizeof(MIDIHDR));
	midiOutLongMsg(hOut, &hHdr, sizeof(MIDIHDR));
	MIDI_EXCVWAIT = 1;
}


/*
 *   えくすくるーしぶを送り終えるまで待つお
 */
void MIDI_Waitlastexclusiveout(void) {

	/* エクスクルーシヴ送信完了まで待ちましょう〜 */
	if (MIDI_EXCVWAIT) {
		while(midiOutUnprepareHeader(hOut, &hHdr, sizeof(MIDIHDR))
						== MIDIERR_STILLPLAYING);
		MIDI_EXCVWAIT = 0;
	}
}


/*
 *   りせっと〜
 */
void MIDI_Reset(void) {

	uint32_t msg;

	memset(DelayBuf, 0, sizeof(DelayBuf));
	DBufPtrW = DBufPtrR = 0;

	if (hOut) {
		switch(MIDI_MODULE) {
			case MIDI_NOTUSED:
				return;
			case MIDI_MT32:
			case MIDI_CM32L:
			case MIDI_CM64:
			case MIDI_LA:
				/* ちょっと乱暴かなぁ…
				 * 一応 SC系でも通る筈ですけど…
				 */
				MIDI_Waitlastexclusiveout();
				MIDI_Sendexclusive(EXCV_MTRESET, sizeof(EXCV_MTRESET));
				break;
			case MIDI_SC55:
			case MIDI_SC88:
			case MIDI_GS:
				MIDI_Waitlastexclusiveout();
				MIDI_Sendexclusive(EXCV_GSRESET, sizeof(EXCV_GSRESET));
				break;
			case MIDI_XG:
				MIDI_Waitlastexclusiveout();
				MIDI_Sendexclusive(EXCV_XGRESET, sizeof(EXCV_XGRESET));
				break;
			default:
				MIDI_Waitlastexclusiveout();
				MIDI_Sendexclusive(EXCV_GMRESET, sizeof(EXCV_GMRESET));
				break;
		}
		MIDI_Waitlastexclusiveout();
		for (msg=0x7bb0; msg<0x7bc0; msg++) {
			midiOutShortMsg(hOut, msg);
		}
	}
}


/*
 *   しょきか〜
 */
void MIDI_Init(void) {

	memset(DelayBuf, 0, sizeof(DelayBuf));
	DBufPtrW = DBufPtrR = 0;

	MIDI_SetModule();
	MIDI_RegHigh = 0;
	MIDI_Vector = 0;
	MIDI_IntEnable = 0;
	MIDI_IntVect = 0;
	MIDI_IntFlag = 0;
	MIDI_R05 = 0;

	MIDI_CTRL = MIDICTRL_READY;
	MIDI_LAST = 0x80;
	MIDI_EXCVWAIT = 0;

	if (!hOut) {
		if (midiOutOpen(&hOut, MIDI_MAPPER, 0, 0, CALLBACK_NULL)
							== MMSYSERR_NOERROR) {
			midiOutReset(hOut);
		}
		else
			hOut = 0;
	}
}


/*
 *   撤収〜
 */
void MIDI_Cleanup(void) {

	if (hOut) {
		MIDI_Reset();
		MIDI_Waitlastexclusiveout();
		midiOutReset(hOut);
		midiOutClose(hOut);
		hOut = 0;
	}
}


/*
 *   メッセージ判別
 */
void MIDI_Message(uint8_t mes) {

	if (!hOut) {
		return;
	}

	switch(mes) {								/* ここの対応はお好みで */
		case MIDI_TIMING:
		case MIDI_START:
		case MIDI_CONTINUE:
		case MIDI_STOP:
		case MIDI_ACTIVESENSE:
			return;
		case MIDI_SYSTEMRESET:					/* 一応イリーガル〜 */
			return;
	}

	if (MIDI_CTRL == MIDICTRL_READY) {			/* 初回限定 */
		if (mes & 0x80) {
			/* status */
			MIDI_POS = 0;
			switch(mes & 0xf0) {
				case 0xc0:
				case 0xd0:
					MIDI_CTRL = MIDICTRL_2uint8_tS;
					break;
				case 0x80:
				case 0x90:
				case 0xa0:
				case 0xb0:
				case 0xe0:
					MIDI_LAST = mes;			/* この方が失敗しないなり… */
					MIDI_CTRL = MIDICTRL_3uint8_tS;
					break;
				default:
					switch(mes) {
						case MIDI_EXCLUSIVE:
							MIDI_CTRL = MIDICTRL_EXCLUSIVE;
							break;
						case MIDI_TIMECODE:
							MIDI_CTRL = MIDICTRL_TIMECODE;
							break;
						case MIDI_SONGPOS:
							MIDI_CTRL = MIDICTRL_SYSTEM;
							MIDI_SYSCOUNT = 3;
							break;
						case MIDI_SONGSELECT:
							MIDI_CTRL = MIDICTRL_SYSTEM;
							MIDI_SYSCOUNT = 2;
							break;
						case MIDI_TUNEREQUEST:
							MIDI_CTRL = MIDICTRL_SYSTEM;
							MIDI_SYSCOUNT = 1;
							break;
						default:
							return;
					}
					break;
			}
		}
		else {						/* Key-onのみな気がしたんだけど忘れた… */
			/* running status */
			MIDI_BUF[0] = MIDI_LAST;
			MIDI_POS = 1;
			MIDI_CTRL = MIDICTRL_3uint8_tS;
		}
	}
	else if ( (mes&0x80) && ((MIDI_CTRL!=MIDICTRL_EXCLUSIVE)||(mes!=MIDI_EOX)) )
	{
		/* メッセージのデータ部にコントロールバイトが出た時…（GENOCIDE2） */
		/* status */
		MIDI_POS = 0;
		switch(mes & 0xf0) {
			case 0xc0:
			case 0xd0:
				MIDI_CTRL = MIDICTRL_2uint8_tS;
				break;
			case 0x80:
			case 0x90:
			case 0xa0:
			case 0xb0:
			case 0xe0:
				MIDI_LAST = mes;			/* この方が失敗しないなり… */
				MIDI_CTRL = MIDICTRL_3uint8_tS;
				break;
			default:
				switch(mes) {
					case MIDI_EXCLUSIVE:
						MIDI_CTRL = MIDICTRL_EXCLUSIVE;
						break;
					case MIDI_TIMECODE:
						MIDI_CTRL = MIDICTRL_TIMECODE;
						break;
					case MIDI_SONGPOS:
						MIDI_CTRL = MIDICTRL_SYSTEM;
						MIDI_SYSCOUNT = 3;
						break;
					case MIDI_SONGSELECT:
						MIDI_CTRL = MIDICTRL_SYSTEM;
						MIDI_SYSCOUNT = 2;
						break;
					case MIDI_TUNEREQUEST:
						MIDI_CTRL = MIDICTRL_SYSTEM;
						MIDI_SYSCOUNT = 1;
						break;
					default:
						return;
				}
				break;
		}
	}

	MIDI_BUF[MIDI_POS++] = mes;

	switch(MIDI_CTRL) {
		case MIDICTRL_2uint8_tS:
			if (MIDI_POS >= 2) {
				if (ENABLE_TONEMAP) {
					if (((MIDI_BUF[0] & 0xf0) == 0xc0) &&
						(TONE_CH[MIDI_BUF[0] & 0x0f] < MIMPI_RHYTHM)) {
						MIDI_BUF[1] = TONEMAP[ TONE_CH[MIDI_BUF[0] & 0x0f] ][ MIDI_BUF[1] & 0x7f ];
					}
				}
				MIDI_Waitlastexclusiveout();
				midiOutShortMsg(hOut, MIDIOUTS(MIDI_BUF[0], MIDI_BUF[1], 0));
				MIDI_CTRL = MIDICTRL_READY;
			}
			break;
		case MIDICTRL_3uint8_tS:
			if (MIDI_POS >= 3) {
				MIDI_Waitlastexclusiveout();
				midiOutShortMsg(hOut,
							MIDIOUTS(MIDI_BUF[0], MIDI_BUF[1], MIDI_BUF[2]));
				MIDI_CTRL = MIDICTRL_READY;
			}
			break;
		case MIDICTRL_EXCLUSIVE:
			if (mes == MIDI_EOX) {
				MIDI_Waitlastexclusiveout();
				MIDI_Sendexclusive(MIDI_BUF, MIDI_POS);
				MIDI_CTRL = MIDICTRL_READY;
			}
			else if (MIDI_POS >= MIDIBUFFERS) {		/* おーばーふろー */
				MIDI_CTRL = MIDICTRL_READY;
			}
			break;
		case MIDICTRL_TIMECODE:
			if (MIDI_POS >= 2) {
				if ((mes == 0x7e) || (mes == 0x7f)) {
					/* exclusiveと同じでいい筈… */
					MIDI_CTRL = MIDICTRL_EXCLUSIVE;
				}
				else {
					MIDI_CTRL = MIDICTRL_READY;
				}
			}
			break;
		case MIDICTRL_SYSTEM:
			if (MIDI_POS >= MIDI_SYSCOUNT) {
				MIDI_CTRL = MIDICTRL_READY;
			}
			break;
	}
}


/*
 *   I/O Read
 */
uint8_t FASTCALL MIDI_Read(uint32_t adr)
{
	uint8_t ret = 0;

	if ( (adr<0xeafa01)||(adr>=0xeafa10)||(!Config.MIDI_SW) )
	{
		/* 変なアドレスか、
		 * MIDI OFF時にはバスエラーにする
		 */
		BusErrFlag = 1;
		return 0;
	}

	switch(adr&15)
	{
	case 0x01:
		ret = (MIDI_Vector | MIDI_IntVect);
		MIDI_IntVect=0x10;
		break;
	case 0x03:
		break;
	case 0x05:
		break;
	case 0x07:
		break;
	case 0x09:			/* R04, 14, ... 94 */
		switch(MIDI_RegHigh)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			if (MIDI_Buffered>=MIDIFIFOSIZE)
			{
				ret = 0x01;	/* Tx full/not ready */
			}
			else
			{
				ret = 0xc0;	/* Tx empty/ready */
			}
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		}
		break;
	case 0x0b:			/* R05, 15, ... 95 */
		switch(MIDI_RegHigh)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		}
		break;
	case 0x0d:			/* R06, 16, ... 96 */
		switch(MIDI_RegHigh)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		}
		break;
	case 0x0f:			/* R07, 17, ... 97 */
		switch(MIDI_RegHigh)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		}
		break;
	}
	return ret;
}


static void AddDelayBuf(uint8_t msg)
{
	int32_t newptr = (DBufPtrW+1)%MIDIDELAYBUF;
	if ( newptr!=DBufPtrR ) {
		DelayBuf[DBufPtrW].time = timeGetTime();
		DelayBuf[DBufPtrW].msg  = msg;
		DBufPtrW = newptr;
	}
}


void MIDI_DelayOut(uint32_t delay)
{
	uint32_t t = timeGetTime();
	while ( DBufPtrW!=DBufPtrR ) {
		if ( (t-DelayBuf[DBufPtrR].time)>=delay ) {
			MIDI_Message(DelayBuf[DBufPtrR].msg);
			DBufPtrR = (DBufPtrR+1)%MIDIDELAYBUF;
		} else
			break;
	}
}


/*
 *   I/O Write
 */
void FASTCALL MIDI_Write(uint32_t adr, uint8_t data)
{
	if ( (adr<0xeafa01)||(adr>=0xeafa10)||(!Config.MIDI_SW) )
	{
		/* 変なアドレスか、
		 * MIDI OFF時にはバスエラーにする
		 */
		BusErrFlag = 1;
		return;
	}

	switch(adr&15)
	{
	case 0x01:
		break;
	case 0x03:
		MIDI_RegHigh = data&0x0f;
		if (data&0x80) MIDI_Init();
		break;
	case 0x05:
		break;
	case 0x07:
		break;
	case 0x09:			/* R04, 14, ... 94 */
		switch(MIDI_RegHigh)
		{
		case 0:
			MIDI_Vector = (data&0xe0);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			MIDI_GTimerMax = (MIDI_GTimerMax&0xff00)|(uint32_t)data;
			break;
		case 9:
			break;
		}
		break;
	case 0x0b:			/* R05, 15, ... 95 */
		switch(MIDI_RegHigh)
		{
		case 0:
			MIDI_R05 = data;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			MIDI_GTimerMax = (MIDI_GTimerMax&0xff)|(((uint32_t)(data&0x3f))*256);
			if (data&0x80)
				MIDI_GTimerVal = MIDI_GTimerMax*80;
			break;
		case 9:
			break;
		}
		break;
	case 0x0d:			/* R06, 16, ... 96 */
		switch(MIDI_RegHigh)
		{
		case 0:
			MIDI_IntEnable = data;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:			/* Out Data Byte */
			if (!MIDI_Buffered)
				MIDI_BufTimer = MIDIBUFTIMER;
			MIDI_Buffered ++;
			AddDelayBuf(data);
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			MIDI_MTimerMax = (MIDI_MTimerMax&0xff00)|(uint32_t)data;
			break;
		case 9:
			break;
		}
		break;
	case 0x0f:			/* R07, 17, ... 97 */
		switch(MIDI_RegHigh)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			MIDI_MTimerMax = (MIDI_MTimerMax&0xff)|(((uint32_t)(data&0x3f))*256);
			if (data&0x80)
				MIDI_MTimerVal = MIDI_MTimerMax*80;
			break;
		case 9:
			break;
		}
		break;
	}
}


/*
 * MIMPIトーンファイル読み込み（ねこみぢ6）
 */

static int32_t exstrcmp(char *str, char *cmp) {

	uint8_t	c;

	while(*cmp) {
		c = *str++;
		if ((c >= 'a') && (c <= 'z')) {
			c -= 0x20;
		}
		if (c != *cmp++) {
			return(TRUE);
		}
	}
	return(FALSE);
}

static void cutdelimita(char **buf) {

	uint8_t	c;

	for(;;) {
		c = **buf;
		if (!c) {
			break;
		}
		if (c > ' ') {
			break;
		}
		(*buf)++;
	}
}

static int32_t getvalue(char **buf, int32_t cutspace) {

	int32_t		ret = 0;
	int32_t	valhit = 0;
	uint8_t	c;

	if (cutspace) {
		cutdelimita(buf);
	}
	for (;; valhit=1) {
		c = **buf;
		if (!c) {
			if (!valhit) {
				return(-1);
			}
			else {
				break;
			}
		}
		if ((c < '0') || (c > '9')) {
			break;
		}
		ret = ret * 10 + (c - '0');
		(*buf)++;
	}
	return(ret);
}

static int32_t file_readline(FILEH fh, char *buf, int32_t len) {

	uint32_t	pos;
	uint32_t	readsize;
	uint32_t	i;

	if (len < 2) {
		return(-1);
	}
	pos = File_Seek(fh, 0, FSEEK_CUR);
	if (pos == (uint32_t)-1) {
		return(-1);
	}
	readsize = File_Read(fh, buf, len-1);
	if (readsize == (uint32_t)-1) {
		return(-1);
	}
	if (!readsize) {
		return(-1);
	}
	for (i=0; i<readsize; i++) {
		pos++;
		if ((buf[i] == 0x0a) || (buf[i] == 0x0d)) {
			break;
		}
	}
	buf[i] = '\0';
	if (File_Seek(fh, pos, FSEEK_SET) != pos) {
		return(-1);
	}
	return(i);
}

static void mimpidefline_analaize(char *buf) {

	cutdelimita(&buf);
	if (*buf == '@') {
		int32_t		ch;
		buf++;
		ch = getvalue(&buf, FALSE);
		if ((ch < 1) || (ch > 16)) {
			return;
		}
		ch--;
		cutdelimita(&buf);
		if (!exstrcmp(buf, "LA")) {
			TONE_CH[ch] = MIMPI_LA;
		}
		else if (!exstrcmp(buf, "PCM")) {
			TONE_CH[ch] = MIMPI_PCM;
		}
		else if (!exstrcmp(buf, "GS")) {
			TONE_CH[ch] = MIMPI_GS;
		}
		else if (!exstrcmp(buf, "RHYTHM")) {
			TONE_CH[ch] = MIMPI_RHYTHM;
		}
	}
	else {
		int32_t	mod, num, bank, tone;
		mod = getvalue(&buf, FALSE);
		if ((mod < 0) || (mod >= MIMPI_RHYTHM)) {
			return;
		}
		num = getvalue(&buf, TRUE);
		if ((num < 1) || (num > 128)) {
			return;
		}
		num--;
		tone = getvalue(&buf, TRUE);
		if ((tone < 1) || (tone > 128)) {
			return;
		}
		if (*buf == ':') {
			buf++;
			bank = tone - 1;
			tone = getvalue(&buf, TRUE);
			if ((tone < 1) || (tone > 128)) {
				return;
			}
			TONEBANK[mod][num] = bank;
		}
		TONEMAP[mod][num] = tone-1;
	}
}

int32_t MIDI_SetMimpiMap(char *filename) {

	uint8_t		b;
	FILEH		fh;
	char		buf[128];

	LOADED_TONEMAP = 0;
	memset(TONE_CH, 0, sizeof(TONE_CH));
	memset(TONEBANK[0], 0, sizeof(TONEBANK));
	for (b=0; b<128; b++) {
		TONEMAP[0][b] = b;
		TONEMAP[1][b] = b;
		TONEMAP[2][b] = b;
	}
	TONE_CH[9] = MIMPI_RHYTHM;

	if ((filename == NULL) || (!filename[0])) {
		ENABLE_TONEMAP = 0;
		return(FALSE);
	}
	fh = File_Open(filename);
	if (fh == (FILEH)-1) {
		ENABLE_TONEMAP = 0;
		return(FALSE);
	}
	while(file_readline(fh, buf, sizeof(buf)) >= 0) {
		mimpidefline_analaize(buf);
	}
	File_Close(fh);

	LOADED_TONEMAP = 1;
	return(TRUE);
}

int32_t MIDI_EnableMimpiDef(int32_t enable) {

	ENABLE_TONEMAP = 0;
	if ((enable) && (LOADED_TONEMAP)) {
		ENABLE_TONEMAP = 1;
		return(TRUE);
	}
	return(FALSE);
}
