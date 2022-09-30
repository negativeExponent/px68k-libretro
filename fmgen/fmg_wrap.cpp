// cisc����Υ����������ܥ�̤򶯰��ˤ���ԡ��˷Ҥ������
// extern "C" ����������������ʤ��ƥ��ƥ��ʤ�

// readme.txt�˽��äơ���������
//  - opna.cpp��YMF288�ѤΥ��饹�ɲä��Ƥޤ���OPNA���Τޤ�ޤ����ɤ͡ʤۤ�Ȥ��������ʤ����ޤ��������
//  - ¿ʬ¾��Ϯ�äƤʤ��Ϥ��ġ�

#ifdef __cplusplus
extern "C" {
#endif

#include "../x11/common.h"
#include "../x11/winx68k.h"
#include "../x11/dswin.h"
#include "../x11/prop.h"

#include "../x68k/mfp.h"
#include "../x68k/adpcm.h"
#include "../x68k/mercury.h"
#include "../x68k/fdc.h"

#include "fmg_wrap.h"

#include "opm.h"
#include "opna.h"

#ifdef __cplusplus
}
#endif

/* DUMMY CALLBACKS */
#define	juliet_load()
#define	juliet_unload()
#define	juliet_prepare()
#define	juliet_YM2151Reset()
#define	juliet_YM2151IsEnable()	FALSE
#define	juliet_YM2151W(r,d)

#define RMBUFSIZE (256*1024)

typedef struct {
	uint32_t time;
	int reg;
	uint8_t data;
} RMDATA;

static RMDATA RMData[RMBUFSIZE];
static int RMPtrW;
static int RMPtrR;

class MyOPM : public FM::OPM
{
public:
	MyOPM();
	virtual ~MyOPM() {}
	void WriteIO(uint32_t adr, uint8_t data);
	void Count2(uint32_t clock);
private:
	virtual void Intr(bool);
	int CurReg;
	uint32_t CurCount;
};


MyOPM::MyOPM()
{
	CurReg = 0;
}

void MyOPM::WriteIO(uint32_t adr, uint8_t data)
{
	if( adr&1 ) {
		if ( CurReg==0x1b ) {
			::ADPCM_SetClock((data>>5)&4);
			::FDC_SetForceReady((data>>6)&1);
		}
		SetReg((int)CurReg, (int)data);
		if ( (juliet_YM2151IsEnable())&&(Config.SoundROMEO) ) {
			int newptr = (RMPtrW+1)%RMBUFSIZE;
			if ( newptr!=RMPtrR ) {
#if 0
				RMData[RMPtrW].time = timeGetTime();
				RMData[RMPtrW].reg  = CurReg;
				if ( CurReg==0x14 ) data &= 0xf3;	// Int Enable�ϥޥ�������
				RMData[RMPtrW].data = data;
				RMPtrW = newptr;
			}
#else
				OPM_RomeoOut(Config.BufferSize*5);
			}
			RMData[RMPtrW].time = timeGetTime();
			RMData[RMPtrW].reg  = CurReg;
			if ( CurReg==0x14 ) data &= 0xf3;	// Int Enable�ϥޥ�������
			RMData[RMPtrW].data = data;
			RMPtrW = newptr;
#endif
		}
	} else {
		CurReg = (int)data;
	}
}

void MyOPM::Intr(bool f)
{
	if ( f ) ::MFP_Int(12);
}


void MyOPM::Count2(uint32_t clock)
{
	CurCount += clock;
	Count(CurCount/10);
	CurCount %= 10;
}


static MyOPM* opm = NULL;

int OPM_Init(int clock, int rate)
{
	juliet_load();
	juliet_prepare();

	RMPtrW = RMPtrR = 0;
	memset(RMData, 0, sizeof(RMData));

	opm = new MyOPM();
	if ( !opm ) return FALSE;
	if ( !opm->Init(clock, rate, TRUE) ) {
		delete opm;
		opm = NULL;
		return FALSE;
	}
	return TRUE;
}


void OPM_Cleanup(void)
{
	juliet_YM2151Reset();
	juliet_unload();
	delete opm;
	opm = NULL;
}


void OPM_SetRate(int clock, int rate)
{
	if ( opm ) opm->SetRate(clock, rate, TRUE);
}


void OPM_Reset(void)
{
	RMPtrW = RMPtrR = 0;
	memset(RMData, 0, sizeof(RMData));

	if ( opm ) opm->Reset();
	juliet_YM2151Reset();
}


uint8_t FASTCALL OPM_Read(uint32_t adr)
{
	if ((adr & 3) == 3)
	{
		uint8_t ret = 0;
		if ( opm ) ret = opm->ReadStatus();
		if ( (juliet_YM2151IsEnable())&&(Config.SoundROMEO) ) {
			int newptr = (RMPtrW+1)%RMBUFSIZE;
			ret = (ret&0x7f)|((newptr==RMPtrR)?0x80:0x00);
		}
		return ret;
	}
	return 0xff;
}


void FASTCALL OPM_Write(uint32_t adr, uint8_t data)
{
#ifdef RFMDRV
	char buf[2];
#endif

	if (adr & 1)
	{
		uint reg = !!((adr & 3) == 3);
		if (opm) opm->WriteIO(reg, data);
	}

#ifdef RFMDRV
	buf[0] = adr & 3;
	buf[1] = data;
	send(rfd_sock, buf, sizeof(buf), 0);
#endif
}

void OPM_Update(int16_t *buffer, int length, int rate, uint8_t *pbsp, uint8_t *pbep)
{
	if ( (!juliet_YM2151IsEnable())||(!Config.SoundROMEO) )
		if ( opm ) opm->Mix((FM::Sample*)buffer, length, rate, pbsp, pbep);
}


void FASTCALL OPM_Timer(uint32_t step)
{
	if ( opm ) opm->Count2(step);
}


void OPM_SetVolume(uint8_t vol)
{
	int v = (vol)?((16-vol)*4):192;		// ���Τ��餤���ʤ�
	if ( opm ) opm->SetVolume(-v);
}


void OPM_RomeoOut(uint32_t delay)
{
	uint32_t t = timeGetTime();
	if ( (juliet_YM2151IsEnable())&&(Config.SoundROMEO) ) {
		while ( RMPtrW!=RMPtrR ) {
			if ( (t-RMData[RMPtrR].time)>=delay ) {
				juliet_YM2151W(RMData[RMPtrR].reg, RMData[RMPtrR].data);
				RMPtrR = (RMPtrR+1)%RMBUFSIZE;
			} else
				break;
		}
	}
}

#ifndef NO_MERCURY
// ----------------------------------------------------------
// ---------------------------- YMF288 (�����Ǥޏ������ꏢ�)
// ----------------------------------------------------------
// TODO : ROMEO��288��á����

class YMF288 : public FM::Y288
{
public:
	YMF288();
	virtual ~YMF288() {}
	void WriteIO(uint32_t adr, uint8_t data);
	uint8_t ReadIO(uint32_t adr);
	void Count2(uint32_t clock);
	void SetInt(int f) { IntrFlag = f; };
private:
	virtual void Intr(bool);
	int CurReg[2];
	uint32_t CurCount;
	int IntrFlag;
};

YMF288::YMF288()
{
	CurReg[0] = 0;
	CurReg[1] = 0;
	IntrFlag = 0;
}

void YMF288::WriteIO(uint32_t adr, uint8_t data)
{
	if( adr&1 ) {
		SetReg(((adr&2)?(CurReg[1]+0x100):CurReg[0]), (int)data);
	} else {
		CurReg[(adr>>1)&1] = (int)data;
	}
}


uint8_t YMF288::ReadIO(uint32_t adr)
{
	uint8_t ret = 0;
	if ( adr&1 ) {
		ret = GetReg(((adr&2)?(CurReg[1]+0x100):CurReg[0]));
	} else {
		ret = ((adr)?(ReadStatusEx()):(ReadStatus()));
	}
	return ret;
}


void YMF288::Intr(bool f)
{
	if ( (f)&&(IntrFlag) ) ::Mcry_Int();
}


void YMF288::Count2(uint32_t clock)
{
	CurCount += clock;
	Count(CurCount/10);
	CurCount %= 10;
}


static YMF288* ymf288a = NULL;
static YMF288* ymf288b = NULL;


int M288_Init(int clock, int rate, const char* path)
{
	ymf288a = new YMF288();
	ymf288b = new YMF288();
	if ( (!ymf288a)||(!ymf288b) ) {
		M288_Cleanup();
		return FALSE;
	}
	if ( (!ymf288a->Init(clock, rate, TRUE, path))||(!ymf288b->Init(clock, rate, TRUE, path)) ) {
		M288_Cleanup();
		return FALSE;
	}
	ymf288a->SetInt(1);
	ymf288b->SetInt(0);
	return TRUE;
}


void M288_Cleanup(void)
{
	delete ymf288a;
	delete ymf288b;
	ymf288a = ymf288b = NULL;
}


void M288_SetRate(int clock, int rate)
{
	if ( ymf288a ) ymf288a->SetRate(clock, rate, TRUE);
	if ( ymf288b ) ymf288b->SetRate(clock, rate, TRUE);
}


void M288_Reset(void)
{
	if ( ymf288a ) ymf288a->Reset();
	if ( ymf288b ) ymf288b->Reset();
}


uint8_t FASTCALL M288_Read(uint16_t adr)
{
	if ( adr<=3 ) {
		if ( ymf288a )
			return ymf288a->ReadIO(adr);
		else
			return 0;
	} else {
		if ( ymf288b )
			return ymf288b->ReadIO(adr&3);
		else
			return 0;
	}
}


void FASTCALL M288_Write(uint32_t adr, uint8_t data)
{
	if ( adr<=3 ) {
		if ( ymf288a ) ymf288a->WriteIO(adr, data);
	} else {
		if ( ymf288b ) ymf288b->WriteIO(adr&3, data);
	}
}


void M288_Update(int16_t *buffer, int length)
{
	if ( ymf288a ) ymf288a->Mix((FM::Sample*)buffer, length);
	if ( ymf288b ) ymf288b->Mix((FM::Sample*)buffer, length);
}


void FASTCALL M288_Timer(uint32_t step)
{
	if ( ymf288a ) ymf288a->Count2(step);
	if ( ymf288b ) ymf288b->Count2(step);
}


void M288_SetVolume(uint8_t vol)
{
	int v1 = (vol)?((16-vol)*4-24):192;		// ���Τ��餤���ʤ�
	int v2 = (vol)?((16-vol)*4):192;		// �����������
	if ( ymf288a ) {
		ymf288a->SetVolumeFM(-v1);
		ymf288a->SetVolumePSG(-v2);
	}
	if ( ymf288b ) {
		ymf288b->SetVolumeFM(-v1);
		ymf288b->SetVolumePSG(-v2);
	}
}
#endif /* !NO_MERCURY */