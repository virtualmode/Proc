#pragma once

#ifndef PROC_HPP
#define PROC_HPP

#include "Temp/Dependency.h"

#include "FileStream.hpp"
#include "SourceToken.hpp"
#include "Utf8.hpp"

// Синтаксический анализатор процессора.
class Proc {

private:

	FileStream &_source;
	Utf8 &_utf8;
	SourceToken &_lexer;

public:

	Proc(const char *fileName):
		_source(FileStream(fileName)),
		_utf8(Utf8((Reader*)&_source)),
		_lexer(SourceToken((CharToken*)&_utf8)) {
	}

	virtual ~Proc() {
	}

	// Начальное состояние машины.
	void Start() {
		int i = 0;
		do {
			_lexer.ReadToken();
			i++;
		} while (_lexer.Type != SymbolType::EndOfStream);
		printf("Proc lexer ready with %u states.\n", i);

		/*// Отладочная информация.
		if (unicode < 256)
			printf_s("%c", unicode);
		else
			printf_s("[%u]", unicode);*/
	}
};

#endif // PROC_HPP
