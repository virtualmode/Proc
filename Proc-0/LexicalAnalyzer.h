/*
	LexicalAnalyzer

	4. Основной лексический анализатор Proc.
	Первичная обработка исходного кода для компилятора или интерпретатора начинается с лексического анализа.
	Есть несколько способов реализации: обычная реализация, интерпретатор БНФ или регулярных выражений,
	или компилятор анализаторов типа Lex. Для временной реализации подойдёт первый вариант.

	TODO Варианты для переименования: lexical analyzer, lexer, tokenizer, scanner, ProcScanner.
*/

#pragma once

#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "Stream.h"
#include "Utf8.h"

class LexicalAnalyzer {

private:

	Reader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	LexicalAnalyzer(Reader *reader);
	~LexicalAnalyzer();

	bool Get();

};

#endif
