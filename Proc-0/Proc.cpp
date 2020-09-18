/*
	Proc(ess(or))

	Версия не является окончательной и необходима в учебных целях.
*/

#include "Temp/Global.h"
#include "Proc.h"

int main(int argc, char **argv)
{
	// Combines several ideas: UTM, VM, Interpreter, Translator, Compiler.

	// Отладка Оберон-0:
	//printf("Oberon-0\r\n\r\n");
	//Compile("debug.mod");

	// Proc-0:
	if (argc <= 1) { // Первым параметром всегда идёт полный путь к исполняемому файлу.
		printf("Usage: proc [--version] [--help] <command>\n\n");
		printf("There are common Proc commands:\n\n");
		printf("-l FILE\t\t\tuse lexical analysis on FILE\n");

	} else if (strcmp(argv[1], "-l") == 0) { // Лексический анализ файла.
		int i = 0;
		FileStream source(argv[2]);
		Utf8 utf8((Reader*)&source);
		LexicalAnalyzer lexer(&utf8);
		while (lexer.Get()) {
			i++;
		}
		printf("Proc lexer ready with %u states.\n", i);
	}

	return 0;
}
