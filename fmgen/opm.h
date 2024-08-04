// ---------------------------------------------------------------------------
//	OPM-like Sound Generator
//	Copyright (C) cisc 1998, 2003.
// ---------------------------------------------------------------------------
//	$Id: opm.h,v 1.14 2003/06/07 08:25:53 cisc Exp $

#ifndef FM_OPM_H
#define FM_OPM_H

#include "fmgen.h"
#include "fmtimer.h"
#include "psg.h"

// ---------------------------------------------------------------------------
//	class OPM
//	OPM ���ɤ�����(?)�����������벻����˥å�
//	
//	interface:
//	bool Init(uint clock, uint rate, bool);
//		����������Υ��饹����Ѥ������ˤ��ʤ餺�Ƥ�Ǥ������ȡ�
//		����: �����䴰�⡼�ɤ��ѻߤ���ޤ���
//
//		clock:	OPM �Υ����å����ȿ�(Hz)
//
//		rate:	�������� PCM ��ɸ�ܼ��ȿ�(Hz)
//
//				
//		����	���������������� true
//
//	bool SetRate(uint clock, uint rate, bool)
//		�����å��� PCM �졼�Ȥ��ѹ�����
//		�������� Init ��Ʊ�͡�
//	
//	void Mix(Sample* dest, int nsamples)
//		Stereo PCM �ǡ����� nsamples ʬ�������� dest �ǻϤޤ������
//		�ä���(�û�����)
//		��dest �ˤ� sample*2 ��ʬ���ΰ褬ɬ��
//		����Ǽ������ L, R, L, R... �Ȥʤ롥
//		�������ޤǲû��ʤΤǡ����餫��������򥼥����ꥢ����ɬ�פ�����
//		��FM_SAMPLETYPE �� short ���ξ�祯��åԥ󥰤��Ԥ���.
//		�����δؿ��ϲ��������Υ����ޡ��Ȥ���Ω���Ƥ��롥
//		  Timer �� Count �� GetNextEvent ������ɬ�פ����롥
//	
//	void Reset()
//		������ꥻ�å�(�����)����
//
//	void SetReg(uint reg, uint data)
//		�����Υ쥸���� reg �� data ��񤭹���
//	
//	uint ReadStatus()
//		�����Υ��ơ������쥸�������ɤ߽Ф�
//		busy �ե饰�Ͼ�� 0
//	
//	bool Count(uint32 t)
//		�����Υ����ޡ��� t [10^(-6) ��] �ʤ�롥
//		�������������֤��Ѳ������ä���(timer �����С��ե���)
//		true ���֤�
//
//	uint32 GetNextEvent()
//		�����Υ����ޡ��Τɤ��餫�������С��ե�������ޤǤ�ɬ�פ�
//		����[����]���֤�
//		�����ޡ�����ߤ��Ƥ������ 0 ���֤���
//	
//	void SetVolume(int db)
//		�Ʋ����β��̤��?������Ĵ�᤹�롥ɸ���ͤ� 0.
//		ñ�̤��� 1/2 dB��ͭ���ϰϤξ�¤� 20 (10dB)
//
//	���۴ؿ�:
//	virtual void Intr(bool irq)
//		IRQ ���Ϥ��Ѳ������ä����ƤФ�롥
//		irq = true:  IRQ �׵᤬ȯ��
//		irq = false: IRQ �׵᤬�ä���
//

namespace FM
{
	//	YM2151(OPM) ----------------------------------------------------
	typedef struct {
		Timer_t 	timer;
		int32_t		fmvolume;

		uint32_t	clock;
		uint32_t	rate;
		uint32_t	pcmrate;

		uint32_t	pmd;
		uint32_t	amd;
		uint32_t	lfocount;
		uint32_t	lfodcount;

		uint32_t	lfo_count_;
		uint32_t	lfo_count_diff_;
		uint32_t	lfo_step_;
		uint32_t	lfo_count_prev_;

		uint32_t	lfowaveform;
		uint32_t	rateratio;
		uint32_t	noise;
		int32_t		noisecount;
		uint32_t	noisedelta;
		
		bool		interpolation;
		uint8_t		lfofreq;
		uint8_t		status;
		uint8_t		reg01;

		uint8_t		kc[8];
		uint8_t		kf[8];
		uint8_t		pan[8];

		channel4_savestate_t	ch[8];
		chip_savestate_t		chip;
	} opm_savestate_t;

	class OPM : public Timer
	{
	public:
		OPM();
		~OPM() {}

		bool		Init(uint32_t c, uint32_t r, bool=false);
		bool		SetRate(uint32_t c, uint32_t r, bool);
		void		SetLPFCutoff(uint32_t freq);
		void		Reset();
		
		void 		SetReg(uint32_t addr, uint32_t data);
		uint32_t	GetReg(uint32_t addr);
		uint32_t	ReadStatus() { return status & 0x03; }
		
		void 		Mix(Sample* buffer, int32_t nsamples, int16_t *pbsp, int16_t *pbep);
		
		void		SetVolume(int32_t db);
		void		SetChannelMask(uint32_t mask);

		void		Save(opm_savestate_t* data);
		void		Load(opm_savestate_t* data);

	private:
		virtual void Intr(bool) {}
	
	private:
		enum
		{
			OPM_LFOENTS = 512,
		};
		
		void		SetStatus(uint32_t bit);
		void		ResetStatus(uint32_t bit);
		void		SetParameter(uint32_t addr, uint32_t data);
		void		TimerA();
		void		RebuildTimeTable();
		void		MixSub(int32_t activech, ISample**);
		void		MixSubL(int32_t activech, ISample**);
		void		LFO();
		uint32_t	Noise();
		
		int32_t		fmvolume;

		uint32_t	clock;
		uint32_t	rate;
		uint32_t	pcmrate;

		uint32_t	pmd;
		uint32_t	amd;
		uint32_t	lfocount;
		uint32_t	lfodcount;

		uint32_t	lfo_count_;
		uint32_t	lfo_count_diff_;
		uint32_t	lfo_step_;
		uint32_t	lfo_count_prev_;

		uint32_t	lfowaveform;
		uint32_t	rateratio;
		uint32_t	noise;
		int32_t		noisecount;
		uint32_t	noisedelta;
		
		bool		interpolation;
		uint8_t		lfofreq;
		uint8_t		status;
		uint8_t		reg01;

		uint8_t		kc[8];
		uint8_t		kf[8];
		uint8_t		pan[8];

		Channel4 	ch[8];
		Chip		chip;

		static void	BuildLFOTable();
		static int32_t amtable[4][OPM_LFOENTS];
		static int32_t pmtable[4][OPM_LFOENTS];

	public:
		int32_t		dbgGetOpOut(int32_t c, int32_t s) { return ch[c].op[s].dbgopout_; }
		Channel4*	dbgGetCh(int32_t c) { return &ch[c]; }

	};
}

#endif // FM_OPM_H
