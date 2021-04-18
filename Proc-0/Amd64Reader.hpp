#pragma once

#ifndef AMD64_READER_HPP
#define AMD64_READER_HPP

#include "CharReader.hpp"
#include "FileStream.hpp"
#include "Utf8.hpp"

// Лексический анализатор двоичного кода архитектуры AMD64.
class Amd64Reader {

private:

	CharReader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	Amd64Reader(CharReader *reader) {
		_reader = reader;

		_writer = new FileStream("debug.txt", O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE);
		_utf8 = new Utf8((Writer*)_writer);
	}

	~Amd64Reader() {
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

#endif // AMD64_READER_HPP
