/*
	AssemblerScanner

	5. Здесь будет что-то типа читабельного представления.

	TODO Варианты для переименования: Amd64AssemblerScanner, т.к. хрен его знает можно ли другие ассемблеры представить одинаково.
*/

#pragma once

#ifndef ASSEMBLER_SCANNER_H
#define ASSEMBLER_SCANNER_H

#include "Stream.h"
#include "Utf8.h"

class AssemblerScanner {

private:

	Reader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	AssemblerScanner(Reader *reader);
	~AssemblerScanner();

	bool Get();

};

#endif
