#pragma once

#ifndef CHAR_TOKEN_HPP
#define CHAR_TOKEN_HPP

#include "Temp/Dependency.h"

#include "Char.hpp"
#include "CharReader.hpp"
#include "CharWriter.hpp"

// Интерфейс машины состояний символа.
// TODO CharReader и CharWriter должны использоваться независимо.
// TODO Необходимо добавить в язык возможность композиции интерфейсов.
// TODO А пока придётся наследовать с другими необходимыми интерфейсами.
class CharToken: public CharReader, public CharWriter {
public:

	// TODO Поток со значением кода символа в реализуемой кодировке.
	int Value;

	// Значение лексемы.
	Char Type;

	// Является ли текущий символ индо-арабской десятичной цифрой.
	virtual bool IsDecimalDigit() = 0;

	// Является ли текущий символ латинской буквой.
	virtual bool IsLatinLetter() = 0;



	// Символ является отступом.
	// @deprecated Временная замена использования значения лексемы.
	virtual bool IsWhitespace() = 0;

	// Символ относится к группе разделителей, используемых в компиляторе.
	// @deprecated Временная замена использования значения лексемы.
	virtual bool IsDelimiter() = 0;

	// Символ является разделителем строк.
	// @deprecated Временная замена использования значения лексемы.
	virtual bool IsEndOfLine() = 0;	
};

#endif // CHAR_TOKEN_HPP
