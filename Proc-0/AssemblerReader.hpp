#pragma once

#ifndef ASSEMBLER_READER_H
#define ASSEMBLER_READER_H

#include "CharReader.hpp"
#include "FileStream.hpp"
#include "TokenReader.hpp"
#include "Utf8.hpp"

/*
	5. Здесь будет что-то типа читабельного представления машинного языка, а может сразу нескольких. Как вариант
	стоит подумать в принципе о наследовании анализаторов от LexicalScanner.
*/

// AssemblerScanner
// TODO Варианты для переименования: Amd64AssemblerScanner,
// TODO т.к. хрен его знает можно ли другие ассемблеры представить одинаково.
class AssemblerReader: public TokenReader {

private:

	CharReader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	AssemblerReader(CharReader *reader) {
		_reader = reader;

		_writer = new FileStream("debug.txt", O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE);
		_utf8 = new Utf8((Writer*)_writer);
	}

	~AssemblerReader() {
		delete _utf8;
		_writer->Close();
		delete _writer;
	}

	bool Get() {
		int symbol = _reader->ReadChar();
		if (symbol > 0) {
			// Вывод UTF-8:
			if (symbol < 256)
				printf_s("%c", symbol);
			else
				printf_s("[%u]", symbol);
			// Запись UTF-8:
			_utf8->WriteChar(symbol);

			return true;
		}
		
		return false;
	}
};

#endif // ASSEMBLER_READER_H
