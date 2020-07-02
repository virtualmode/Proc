#pragma once

#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

class LexicalAnalyzer {

private:

	Stream *_stream;

public:

	LexicalAnalyzer(Stream *stream);

	bool Get();

};

#endif
