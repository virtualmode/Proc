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
	расширения самого себя. Чтобы написать его, потребуется существующий компилятор, например CSC. Поэтому Proc-0
	является временной версией процессора с минимальным набором возможностей, необходимых только для его запуска и
	сборки первой версии самого себя без зависимостей.
*/

// Combines several ideas: UTM, VM, Interpreter, Translator, Compiler.

// Точка входа Proc-0.
if (args.Length <= 1) { // Первым параметром всегда идёт полный путь к исполняемому файлу.
	Console.Write("Usage: proc [--version] [--help] <command>\n\n");
	Console.Write("There are common Proc commands:\n\n");
	Console.Write("-l FILE\t\t\tuse lexical analysis on FILE\n");

} else if (args[0] == "-l") { // Лексический анализ файла.
	var source = new Interop.FileStream(args[1], FileMode.Open, FileAccess.Read); // Базовый поток состояний, используемый процессором и дочерними анализаторами.
	var charToken = new Utf8((Reader)source); // Символьный поток определённой кодировки.
	var lexer = new ProcSymbol(charToken); // Лексический анализатор исходного кода.
	var processor = new ProcSyntax(lexer); // Синтаксический анализатор.
	processor.Start();
}

return 0; // OMG!
