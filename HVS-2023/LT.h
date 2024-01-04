#pragma once
#include "In.h"
#include "Error.h"
#include "Parm.h"
#include <fstream>
#define LEXEMA_FIXSIZE 1	//фиксированный размер лексем
#define LT_MAXSIZE 4096		//макс количество строк в таблице
#define LT_TI_NULLIDX 0xffffffff	//нет элемента ТИ
#define LEX_UINT		't'	//лексема для integer
#define LEX_STR			't'
#define LEX_BOOL		't'	//лексема для string
#define LEX_LITERAL		'l'	//лексема для литерала
#define LEX_ID			'i'	//лексема для идентификатора
#define LEX_FUNCTION	'f'	//лексема для function
#define LEX_MAIN		'm'	//лексема для main
#define LEX_NEW			'd'	//лексема для declare
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

namespace LT	//ТАБЛИЦА ЛЕКСЕМ
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

	struct Entry	//строка таблицы лексем
	{
		char lexema;	///лексема
		int sn;			///№ строки в исх. тексте
		int idxTI;		///индекс в ТИ или в LT_TI_NULLIDX
		int priority;
		operations op;
	};

	struct LexTable		//экземпляр таблицы лексем
	{
		int maxsize;	///емкость ТЛ < LT_MAXSIZE
		int size;		///тек. размер ТЛ < maxsize
		Entry* table;	///массив строк ТЛ
	};

	LexTable Create( // создать таблицу лексем
		int size	/// емкость таблицы лексем < LT_MAXSIZE
	);
	void Add(				//добавить строку в таблицу лексем
		LexTable& lextable, ///экземпл¤р таблицы лексем
		Entry entry			///строка таблицы лексем
	);

	
	Entry GetEntry(			//получить строку таблицы лексем
		LexTable& lextable,	///экземпл¤р таблицы лексем
		int n				///номер получаемой строки
	);

	Entry WriteEntry(Entry& entry, char lexema, int indx, int line);

	void Delete(LexTable& lextable); //удалить таблицу лексем (освободить пам¤ть)
	
	void ShowTable(LexTable lextable, std::ostream& stream_out);
};


