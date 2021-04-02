#pragma once

#ifndef UNICODE_TOKEN_H
#define UNICODE_TOKEN_H

#include "Temp/Dependency.h"

// Интерфейс символа Юникода.
class UnicodeToken {
public:

	// TODO Необходимо добавить в язык возможность композиции интерфейсов.
	// TODO А пока придётся наследовать с другими необходимыми интерфейсами.

	// Является ли текущий символ арабской десятичной цифрой юникода.
	virtual bool IsDigit() = 0;

	// Является ли текущий символ буквой юникода.
	virtual bool IsLetter() = 0;
};

#endif // UNICODE_TOKEN_H
