#pragma once

#ifndef SYMBOL_TYPE_HPP
#define SYMBOL_TYPE_HPP

#include "Temp/Dependency.h"

// Тип последоваельности.
enum class SymbolType {
	Unknown, // Группа непредусмотренных символов.
	Delimiter, // Символы разделителей.
	EndOfLine, // Признак окончания строки (LF, CR, CRLF, NEL, LS, PS).
	EndOfStream, // Терминатор последовательности.
	Number, // Последовательность цифр без разделителей.
	Whitespace, // Горизонтальные или вертикальные отступы между словами (SP, HT, TAB, VT).
	Word, // Слово.
};

#endif // SYMBOL_TYPE_HPP
