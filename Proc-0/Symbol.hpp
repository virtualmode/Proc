#pragma once

#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include "Temp/Dependency.h"

// Лексемы исходного кода.
enum class Symbol {
	Unknown, // Группа непредусмотренных символов.
	Delimiter, // Символы допустимых разделителей.
	EndOfLine, // Признак окончания строки (LF, CR, CRLF, NEL, LS, PS, VT).
	EndOfStream, // Терминатор последовательности.
	Integer, // Последовательность цифр без разделителей.
	Whitespace, // Горизонтальные отступы между словами (SP, HT, TAB).
	Word, // Слово.
};

#endif // SYMBOL_HPP
