/*
	Proc(ess(or))-0

	Версия не является окончательной и необходима в учебных целях.

	0. Виртуальный процессор создаётся с целью изучения теории автоматов и вычислимости. На момент начала работы
	предполагалось создать простую универсальную машину, способную интерпретировать и компилировать код без
	использования сторонних разработок. Принципы и термины, используемые здесь, описаны в книгах:
		Charles Petzold - The Annotated Turing:
			A Guided Tour Through Alan Turing's Historic Paper on Computability and the Turing Machine
		Niklaus Wirth - Compiler Construction

	1. Автомату нужен базовый язык или набор языков, которые он будет понимать, и которых будет достаточно для
	расширения самого себя. Чтобы написать его, потребуется существующий компилятор, например для C/C++. Поэтому Proc-0
	является временной версией процессора с минимальным набором возможностей, необходимых только для его запуска и
	сборки первой версии самого себя без зависимостей. Также решено писать процессор одним листингом, упростив
	переносимость и подчеркнув необходимость использовать только минимум кода, абстрагироваться от файловой системы и
	прочих сервисов. Машина может только выполняться и выполнять другие машины, а код для работы операционной системы,
	оборудованием и прочее должны быть вынесены за пределы компилируемого ядра вычислителя.
*/


// Файл предварительно скомпилированных заголовков.
#include "Temp/Dependency.h"

#include "FileStream.hpp"
#include "SourceReader.hpp"
#include "Utf8.hpp"


// Используемые прототипы Оберон-0.
extern "C" {
	void OssInit(const char *fileName, long pos); // Файл с исходным кодом и его начальная позиция.
	void Oss(const char *fileName); // Файл для записи результатов лексического анализатора.
	void Compile(const char *fileName);
}


// Точка входа.
int main(int argc, char **argv)
{
	// Combines several ideas: UTM, VM, Interpreter, Translator, Compiler.

	// Отладка Оберон-0.
	//printf("Oberon-0\r\n\r\n");
	//Compile("debug.mod");

	// Proc-0.
	if (argc <= 1) { // Первым параметром всегда идёт полный путь к исполняемому файлу.
		printf("Usage: proc [--version] [--help] <command>\n\n");
		printf("There are common Proc commands:\n\n");
		printf("-l FILE\t\t\tuse lexical analysis on FILE\n");

	} else if (strcmp(argv[1], "-l") == 0) { // Лексический анализ файла.
		int i = 0;
		FileStream source(argv[2]);
		Utf8 utf8((Reader*)&source);
		SourceReader lexer(&utf8);
		while (lexer.ReadToken() > 0) {
			i++;
		}
		printf("Proc lexer ready with %u states.\n", i);
	}

	return 0;
}
