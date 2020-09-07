// Lexical analyzer, lexer, tokenizer.

#include "Temp/Global.h"
#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(Reader *reader) {
	_reader = reader;
}

bool LexicalAnalyzer::Get() {
	if (_reader->Read((object)&_symbol, 256) > 0) {
		printf_s("%c", _symbol);
		return true;
	}
	
	return false;
}
