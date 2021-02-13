#pragma once

#ifndef PROC_READER_H
#define PROC_READER_H

#include "Temp/Dependency.h"

#include "SyntaxReader.hpp"
#include "TokenReader.hpp"

// Синтаксический анализатор Proc.
class ProcReader: public SyntaxReader {

private:

	TokenReader *_reader;

public:

	// Основной конструктор.
	// @param reader Входящий поток символов.
	ProcReader(TokenReader *reader) {
		_reader = reader;
	}

	~ProcReader() {
	}

	virtual int ReadSyntax() = 0;

	virtual void ReadBody() = 0;
	virtual void ReadDefinition() = 0;
};

#endif // PROC_READER_H
