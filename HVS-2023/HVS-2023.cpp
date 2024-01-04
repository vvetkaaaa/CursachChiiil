#include "stdafx.h"
#include "Polish.h"

int _tmain(int argc, _TCHAR* argv[])
{

	setlocale(LC_ALL, "RU");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		
		LexAnal::Lex lex = LexAnal::LexAnaliz(parm, in);
		Log::WriteLexTableLog(lex.lextab, *log.stream);

		MFST::SyntaxCheck(lex, log, *log.stream);
		
		Semantic::Parse(lex, log);
		
		Polish::startPolish(lex);
		LexAnal::Synchronization(lex);
		
		Log::WriteLexTableLog(lex.lextab, *log.stream);
		IT::ShowTable(lex.idtab, *log.stream);
		LT::ShowTable(lex.lextab, *log.stream);
		
		Gen::Generator Gener(lex.lextab, lex.idtab, "C:\\LAB_3SEM\\cursachchill\\HVS-2023\\ASM\\asm.asm");
		cout << "Компиляция прошла успешно!!!\n\n";
		Log::Close(log);
		
	}
	catch (Error::ERROR e)
	{
		if (e.inext.line != -1 && e.inext.col != 0) {
			cout << "Ошибка " << e.id << ": " << e.message << "\nCтрока: " << e.inext.line << "\nПозиция: " << e.inext.col << endl;
		}
		else {
			cout << "Ошибка " << e.id << ": " << e.message << endl;
		}
		Log::WriteError(log, e);
	};
	return 0;
}