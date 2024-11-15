#pragma once
#include "GRB.h"
#include "LT.h"
#include "LexAnaliz.h"
#include <stack>
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short> MFSTSTSTACK;		///���� ��������

namespace MFST
{
	struct MfstState			//��������� �������� (��� ����������)
	{
		short lenta_position;	///������� �� �����
		short nrule;
		short nrulechain;		///� ���. �������, ���. �������
		MFSTSTSTACK st;			///���� ��������
		MfstState();
		MfstState(
			short pposition,	///������� �� �����
			MFSTSTSTACK pst,	///���� ��������
			short pnrulechain	///� ������� �������, ���. �������
		);
		MfstState(
			short pposition,
			MFSTSTSTACK pst,
			short pnrule,
			short pnrulechain
		);
	};

	struct Mfst					//���������� �������
	{
		enum RC_STEP {			///��� �������� �-� step
			NS_OK,				///0 (������� ������� � �������, ���. �������� � ����)
			NS_NORULE,			///1 (�� ������� ������� (������ � ����������)) 
			NS_NORULECHAIN,		///2 (�� ������� ���������� ������� ������� (������ � ���. ����)
			NS_ERROR,			///3 (����������� ����������)
			TS_OK,				///4 (���. ������ ����� == ������� �����, ������������ �����, pop �����)
			TS_NOK,				///5 (���. ������ ����� != ������� �����, ������������� ���������)
			LENTA_END,			///6 (���. ������� ����� >= lenta_size)
			SURPRISE
		};			///7 (����������� ��� �������� (������ � step)

		struct MfstDiagnosis		//�����������
		{
			short lenta_position;	///������� �� �����
			RC_STEP rc_step;		///��� ���������� ����
			short nrule;			///����� �������
			short nrule_chain;		///����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(
				short plenta_position,
				RC_STEP prc_step,
				short pnrule,
				short pnrule_chain);
		}diagnosis[MFST_DIAGN_NUMBER];	///��������� ����� �������� ���������

		GRBALPHABET* lenta;		///���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;	///���. ������� �� �����
		short nrule;			///����� ���. �������
		short nrulechain;		///����� ���. �������, ���. �������
		short lenta_size;		///������ �����
		GRB::Greibach grebach;	///��������� �������
		LT::LexTable lex;		///���. ������ ��
		MFSTSTSTACK st;			///���� ��������
		std::stack<MfstState> storestate;	///���� ��� ���������� ���������
		Mfst();
		Mfst(
			LT::LexTable plex,
			GRB::Greibach pgrebach);

		char* getCSt		///�������� ���������� �����
		(
			char* buf
		);
		char* getCLenta		///�����: n �������� � pos
		(
			char* buf,
			short pos,
			short n = 25
		);
		char* getDiagnosis	///�����. n-�� ������ ����������� ��� 0x00
		(
			short n,
			char* buf
		);
		bool savestate(std::ostream& stream_out);	///��������� ��������� ��������
		bool reststate(std::ostream& stream_out);	///�����. ��������� ��������
		bool push_chain		///��������� ������� ������� � ����
		(
			GRB::Rule::Chain chain	///������� �������
		);
		RC_STEP step(std::ostream& stream_out);		///��������� ��� ��������
		bool start(std::ostream& stream_out);		///��������� �������
		bool savediagnosis
		(
			RC_STEP pprc_step	///��� ���������� ����
		);
		void printrules(std::ostream& stream_out);	///������� ������������������ ������


		struct Deducation	///�����
		{
			short size;				///���-�� ����� � ������
			short* nrules;			///������ ������ ����������
			short* nrulechains;		///������ ������� ������ ���������� (nrules)
			Deducation() {
				size = 0;
				nrules = 0;
				nrulechains = 0;
			};
		}deducation;
		bool savededucation();		///��������� ������ ������
	};
	void SyntaxCheck(LexAnal::Lex lex, Log::LOG log, std::ostream& stream_out);
}