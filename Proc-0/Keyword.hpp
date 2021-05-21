#pragma once

#ifndef KEYWORD_HPP
#define KEYWORD_HPP

#include "Temp/Dependency.h"

#include "Symbol.hpp"

#define KEYWORD_ID_SIZE 32

// Информация о зарезервированном слове.
struct Keyword {
	Symbol Symbol;
	char Identifier[KEYWORD_ID_SIZE];
};

#endif // KEYWORD_HPP
