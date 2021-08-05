#pragma once

#ifndef CHAR_HPP
#define CHAR_HPP

#include "Temp/Dependency.h"

#include "CharType.hpp"

// Код символа для внутреннего использования.
// TODO Тип символа в Proc отличается размером от C/C++ типа и должен быть переименован без подчёркивания.
#define _char unsigned long
//typedef unsigned long Char;

// Интерфейс работы с токеном символа определённой кодировки.
class Char {
protected:
public:

	// Поток состояний со значением кода символа в реализуемой кодировке.
	_char Value;

	// Тип токена.
	CharType Type;

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

#endif // CHAR_HPP
