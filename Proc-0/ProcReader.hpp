#pragma once

#ifndef PROC_READER_HPP
#define PROC_READER_HPP

#include "Temp/Dependency.h"

#include "SyntaxReader.hpp"
#include "SymbolToken.hpp"

// Синтаксический анализатор Proc.
class ProcReader {

private:

	SymbolToken *_sourceToken;

public:

	// Основной конструктор.
	// @param sourceToken Поток лексем исходного кода.
	ProcReader(SymbolToken *sourceToken) {
		_sourceToken = sourceToken;
	}

	~ProcReader() {
	}
};

#endif // PROC_READER_HPP
