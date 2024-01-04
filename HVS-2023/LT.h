#pragma once
#include "In.h"
#include "Error.h"
#include "Parm.h"
#include <fstream>
#define LEXEMA_FIXSIZE 1	//������������� ������ ������
#define LT_MAXSIZE 4096		//���� ���������� ����� � �������
#define LT_TI_NULLIDX 0xffffffff	//��� �������� ��
#define LEX_UINT		't'	//������� ��� integer
#define LEX_STR			't'
#define LEX_BOOL		't'	//������� ��� string
#define LEX_LITERAL		'l'	//������� ��� ��������
#define LEX_ID			'i'	//������� ��� ��������������
#define LEX_FUNCTION	'f'	//������� ��� function
#define LEX_MAIN		'm'	//������� ��� main
#define LEX_NEW			'd'	//������� ��� declare
#define LEX_RETURN		'r'	//return
#define LEX_WRITE		'w' //write
#define LEX_IF			'?' //if
#define LEX_ELSE        'e' //else
#define LEX_SEMICOLON	';'	//;
#define LEX_COMMA		','	//,
#define LEX_LEFTBRACE	'{'	//{
#define LEX_BRACELET	'}'	//}
#define LEX_LEFTHESIS	'('	//(
#define LEX_RIGHTHESIS	')'	//)
#define LEX_RAV			'='	//=
#define DIV				'|'

#define LEX_OPERATOR	'v'
#define LEX_MORE		'v' // >
#define LEX_LESS		'v' // <
#define LEX_EQUALS		'v' // ~
#define LEX_NEQUALS		'v' // !
#define LEX_EQORMORE	'v' // ^
#define LEX_EQORLESS	'v' // _

namespace LT	//������� ������
{
	enum operations {
		OPLUS = 1,
		OMINUS,
		OMORE,
		OLESS,
		OMOREEQ,
		OLESSEQ,
		OEQUALS,
		ONONEQUALS,
		OEQORMORE,
		OEQORLESS
	};

	struct Entry	//������ ������� ������
	{
		char lexema;	///�������
		int sn;			///� ������ � ���. ������
		int idxTI;		///������ � �� ��� � LT_TI_NULLIDX
		int priority;
		operations op;
	};

	struct LexTable		//��������� ������� ������
	{
		int maxsize;	///������� �� < LT_MAXSIZE
		int size;		///���. ������ �� < maxsize
		Entry* table;	///������ ����� ��
	};

	LexTable Create( // ������� ������� ������
		int size	/// ������� ������� ������ < LT_MAXSIZE
	);
	void Add(				//�������� ������ � ������� ������
		LexTable& lextable, ///�������� ������� ������
		Entry entry			///������ ������� ������
	);

	
	Entry GetEntry(			//�������� ������ ������� ������
		LexTable& lextable,	///�������� ������� ������
		int n				///����� ���������� ������
	);

	Entry WriteEntry(Entry& entry, char lexema, int indx, int line);

	void Delete(LexTable& lextable); //������� ������� ������ (���������� �����)
	
	void ShowTable(LexTable lextable, std::ostream& stream_out);
};


