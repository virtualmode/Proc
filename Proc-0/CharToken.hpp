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

	// Поток со значением кода символа в реализуемой кодировке.
	int Value;

	virtual bool IsWhitespace() = 0;

	virtual bool IsEndOfLine() = 0;

	virtual bool IsDelimiter() = 0;

	// Является ли текущий символ индо-арабской десятичной цифрой.
	virtual bool IsDecimalDigit() = 0;

	// Является ли текущий символ латинской буквой.
	virtual bool IsLatinLetter() = 0;
};

#endif // CHAR_TOKEN_HPP
