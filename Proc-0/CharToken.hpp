#pragma once

#ifndef CHAR_TOKEN_H
#define CHAR_TOKEN_H

#include "Temp/Dependency.h"

#include "Char.hpp"
#include "CharReader.hpp"
#include "CharWriter.hpp"

// Интерфейс машины состояний символа.
// TODO CharReader и CharWriter должны использоваться независимо.
class CharToken: public CharReader, public CharWriter {
public:

	// TODO Необходимо добавить в язык возможность композиции интерфейсов.
	// TODO А пока придётся наследовать с другими необходимыми интерфейсами.

	// Представление символа.
	Char Value;

	// Является ли текущий символ арабской десятичной цифрой.
	virtual bool IsDigit() = 0;

	// Является ли текущий символ буквой.
	virtual bool IsLetter() = 0;
};

#endif // CHAR_TOKEN_H
