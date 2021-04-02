#pragma once

#ifndef SYMBOL_TYPE_H
#define SYMBOL_TYPE_H

#include "Temp/Dependency.h"

// Тип последоваельности.
enum SymbolType {
	Delimiter, // Символы разделителей.
	EndOfLine, // Признак окончания строки (LF, CR, CRLF, NEL, LS, PS).
	EndOfStream, // Терминатор последовательности.
	Number, // Последовательность цифр без разделителей.
	Unknown, // Группа непредусмотренных символов.
	Whitespace, // Горизонтальные или вертикальные отступы между словами (SP, HT, TAB, VT).
	Word, // Слово.
};

#endif // SYMBOL_TYPE_H
