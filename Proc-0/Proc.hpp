#pragma once

#ifndef PROC_HPP
#define PROC_HPP

#include "Temp/Dependency.h"

#include "FileStream.hpp"
#include "SourceToken.hpp"
#include "Utf8.hpp"

class Proc {
public:
	void Main(const char *fileName) {
		int i = 0;
		FileStream source(fileName);
		Utf8 utf8((Reader*)&source);
		SourceToken lexer(&utf8);
		do {
			lexer.ReadToken();
			i++;
		} while (lexer.Type != SymbolType::EndOfStream);
		printf("Proc lexer ready with %u states.\n", i);

		/*// Отладочная информация.
		if (unicode < 256)
			printf_s("%c", unicode);
		else
			printf_s("[%u]", unicode);*/
	}
};

#endif // PROC_HPP
