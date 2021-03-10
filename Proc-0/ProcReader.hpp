#pragma once

#ifndef PROC_READER_H
#define PROC_READER_H

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

#endif // PROC_READER_H
