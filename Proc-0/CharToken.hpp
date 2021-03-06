#pragma once

#ifndef CHAR_TOKEN_HPP
#define CHAR_TOKEN_HPP

#include "Temp/Dependency.h"

#include "Char.hpp"
#include "CharReader.hpp"
#include "CharWriter.hpp"
#include "CharSeeker.hpp"

// Интерфейс машины состояний символа.
// TODO CharReader и CharWriter должны использоваться независимо.
// TODO Необходимо добавить в язык возможность композиции интерфейсов.
// TODO А пока придётся наследовать с другими необходимыми интерфейсами.
class CharToken: public CharReader, public CharWriter, public CharSeeker {
public:

	// TODO Поток со значением кода символа в реализуемой кодировке.
	int Value;

	// Значение лексемы.
	Char Type;

	// Является ли текущий символ индо-арабской десятичной цифрой.
	virtual bool IsDecimalDigit() = 0;

	// Является ли текущий символ строчной латинской буквой.
	virtual bool IsSmallLatinLetter() = 0;

	// Является ли текущий символ заглавной латинской буквой.
	virtual bool IsCapitalLatinLetter() = 0;

	// Является ли текущий символ латинской буквой.
	virtual bool IsLatinLetter() = 0;

	// Символ является отступом.
	// @deprecated Достаточно специфическая реализация для использования в таком виде.
	virtual bool IsWhitespace() = 0;

	// Символ относится к группе допустимых разделителей, используемых в компиляторе.
	// @deprecated Достаточно специфическая реализация для использования в таком виде.
	virtual bool IsDelimiter() = 0;

	// Символ является разделителем строк или входит в последовательность разделения.
	// @deprecated Название не совсем соответствует действительности.
	virtual bool IsEndOfLine() = 0;
};

#endif // CHAR_TOKEN_HPP
