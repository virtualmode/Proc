/*
	Amd64Scanner

	6. Это лексический анализатор двоичного кода архитектуры AMD64.
*/

#pragma once

#ifndef AMD64_SCANNER_H
#define AMD64_SCANNER_H

#include "Stream.h"
#include "Utf8.h"

class Amd64Scanner {

private:

	Reader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	Amd64Scanner(Reader *reader);
	~Amd64Scanner();

	bool Get();

};

#endif
