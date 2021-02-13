#pragma once

#ifndef SOURCE_READER_H
#define SOURCE_READER_H

#include "Temp/Dependency.h"

#include "CharReader.hpp"
#include "TokenReader.hpp"

// Лексический анализатор исходного кода.
class SourceReader: public TokenReader {

private:

	CharReader *_reader;

	// Текущий символ.
	int _symbol;

public:

	// Основной конструктор.
	// @param reader Входящий поток символов.
	SourceReader(CharReader *reader) {
		_reader = reader;
	}

	~SourceReader() {
	}

	virtual int ReadToken() {
		int symbol = _reader->ReadChar();
		if (symbol > 0) {
			// Вывод UTF-8:
			if (symbol < 256)
				printf_s("%c", symbol);
			else
				printf_s("[%u]", symbol);

			return 1;
		}
		
		return 0;
	}
};

#endif // SOURCE_READER_H
