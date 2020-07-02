/*
	Process(or)
	
	Combines several ideas: UTM, VM, Interpreter, Translator, Compiler.
*/

#include "proc.h"

int main(int argc, char **argv)
{
	// Отладка Оберон-0:
	//printf("Oberon-0\r\n\r\n");
	//Compile("debug.mod", 0);

	// Использование компилятора:
	if (argc == 0) {
		printf("Usage: proc [--version] [--help] <command>\n\n");
		printf("There are common Proc commands:\n\n");
		printf("-l FILE\t\t\tuse lexical analysis on FILE\n");

	} else if (argv[0] == "-l") {
		int i = 0;
		Stream source(argv[0]);
		LexicalAnalyzer lexer(&source);
		while (lexer.Get()) {
			i++;
		}
		printf("Proc lexer ready with %u states.\n", i);
		
	}

	return 0;
}
