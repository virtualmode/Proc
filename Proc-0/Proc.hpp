#pragma once

#ifndef PROC_HPP
#define PROC_HPP

#include "Temp/Dependency.h"

#include "FileStream.hpp"
#include "SymbolToken.hpp"
#include "Utf8.hpp"

// Синтаксический анализатор процессора.
class Proc {

private:

	Utf8 &_utf8;
	SymbolToken &_lexer;

public:

	Proc(Reader &source):
		_utf8(Utf8(&source)),
		_lexer(SymbolToken((CharToken*)&_utf8)) {
	}

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
