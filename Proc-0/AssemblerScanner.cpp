// Lexical analyzer, lexer, tokenizer.

#include "Temp/Global.h"
#include "AssemblerScanner.h"

AssemblerScanner::AssemblerScanner(Reader *reader) {
	_reader = reader;

	_writer = new FileStream("debug.txt", O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE);
	_utf8 = new Utf8((Writer*)_writer);
}

AssemblerScanner::~AssemblerScanner() {
	delete _utf8;
	_writer->Close();
	delete _writer;
}

bool AssemblerScanner::Get() {
	int symbol = _reader->Read(NULL); // TODO Temporary crutches.
	if (symbol > 0) {
		// Вывод UTF-8:
		if (symbol < 256)
			printf_s("%c", symbol);
		else
			printf_s("[%u]", symbol);
		// Запись UTF-8:
		_utf8->Write((Reader *)&symbol);

		return true;
	}
	
	return false;
}
