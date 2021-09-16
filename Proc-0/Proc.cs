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

// Combines several ideas: UTM, VM, Interpreter, Translator, Compiler.

// Точка входа Proc-0.
if (args.Length <= 1) { // Первым параметром всегда идёт полный путь к исполняемому файлу.
	Console.Write("Usage: proc [--version] [--help] <command>\n\n");
	Console.Write("There are common Proc commands:\n\n");
	Console.Write("-l FILE\t\t\tuse lexical analysis on FILE\n");

} else if (args[1] == "-l") { // Лексический анализ файла.
	var source = new FileStream(args[2], FileMode.Open, FileAccess.Read); // Базовый поток состояний, используемый процессором и дочерними анализаторами.
	var charToken = new Utf8((Reader)source); // Символьный поток определённой кодировки.
	var lexer = new ProcSymbol(charToken); // Лексический анализатор исходного кода.
	var processor = new Proc(lexer); // Синтаксический анализатор.
	processor.Start();
}

return 0; // OMG!

/// <summary>
/// Синтаксический анализатор процессора.
/// Proc[]
/// []Proc
/// Pr[]c
/// Pr[][
/// </summary>
class Proc {

	private Symbol _lexer;

	// OBSOLETE
	// А может сделать как-то общую цепочку для любого языка?
	// stream -> streamN -> lex -> synt

	// Вместо цепочки можно использовать сразу анализатор.
	//ISyntaxAnalyzer syntaxAnalyzer

	/// <summary>
	/// Но почему не лексический анализатор в параметре?!
	/// Т.к. класс скорее является фабрикой лексико-синтаксических цепочек классов,
	/// которые всегда цепляются на базовый поток.
	/// </summary>
	public Proc(Symbol symbolToken) {
		_lexer = symbolToken;
	}

	//public Proc(ISyntaxAnalyzer syntaxAnalyzer) { } // Сразу перейти в состояние другого процессора.

	/// <summary>
	/// Начальное состояние машины.
	/// </summary>
	public void Start() {
		int i = 0;
		do {
			_lexer.ReadToken();
			i++;
		} while (_lexer.Type != SymbolType.EndOfStream);
		Console.WriteLine("Proc lexer ready with %u states.", i);

		/*// Отладочная информация.
		if (unicode < 256)
			printf_s("%c", unicode);
		else
			printf_s("[%u]", unicode);*/
	}
}
