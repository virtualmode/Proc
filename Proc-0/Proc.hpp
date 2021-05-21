#pragma once

#ifndef PROC_HPP
#define PROC_HPP

#include "Temp/Dependency.h"

#include "FileStream.hpp"
#include "Utf8.hpp"
#include "SymbolToken.hpp"
#include "ProcSymbolToken.hpp"

// Синтаксический анализатор процессора.
class Proc {
private:

	// Лексический анализатор исходного кода.
	SymbolToken &_lexer;

	// OBSOLETE
	// А может сделать как-то общую цепочку для любого языка?
	// stream -> streamN -> lex -> synt

	// Вместо цепочки можно использовать сразу анализатор.
	//ISyntaxAnalyzer syntaxAnalyzer

public:

	// Но почему не лексический анализатор в параметре?!
	// Т.к. класс скорее является фабрикой лексико-синтаксических цепочек классов,
	// которые всегда цепляются на базовый поток.
	Proc(SymbolToken &symbolToken):
		_lexer(symbolToken) {
	}

	//Proc(ISyntaxAnalyzer syntaxAnalyzer) // Сразу перейти в состояние другого процессора.

	virtual ~Proc() {
	}

	// Начальное состояние машины.
	void Start() {
		int i = 0;
		do {
			_lexer.ReadToken();
			i++;
		} while (_lexer.Type != Symbol::EndOfStream);
		printf("Proc lexer ready with %u states.\n", i);

		/*// Отладочная информация.
		if (unicode < 256)
			printf_s("%c", unicode);
		else
			printf_s("[%u]", unicode);*/
	}
};

#endif // PROC_HPP
