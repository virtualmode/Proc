#pragma once

#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "Stream.h"

class LexicalAnalyzer {

private:

	Reader *_reader;
	char _symbol;

public:

	LexicalAnalyzer(Reader *reader);

	bool Get();

};

#endif
