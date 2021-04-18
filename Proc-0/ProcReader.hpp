#pragma once

#ifndef PROC_READER_HPP
#define PROC_READER_HPP

#include "Temp/Dependency.h"

#include "SyntaxReader.hpp"
#include "SourceToken.hpp"

// Синтаксический анализатор Proc.
class ProcReader {

private:

	SourceToken *_sourceToken;

public:

	// Основной конструктор.
	// @param sourceToken Поток лексем исходного кода.
	ProcReader(SourceToken *sourceToken) {
		_sourceToken = sourceToken;
	}

	~ProcReader() {
	}
};

#endif // PROC_READER_HPP
