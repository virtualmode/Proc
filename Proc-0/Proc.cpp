/*
	Proc(ess(or))

	Версия не является окончательной и необходима в учебных целях.
*/

#include "Global.h"
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

	} else if (argv[1] == "-l") { // Лексический анализ файла.
		/*int i = 0;
		Stream source(argv[0]);
		LexicalAnalyzer lexer(&source);
		while (lexer.Get()) {
			i++;
		}
		printf("Proc lexer ready with %u states.\n", i);*/
	}

	return 0;
}
