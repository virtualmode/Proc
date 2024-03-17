/*
	Proc(ess(or))-0

	Proc[]
	[]Proc
	Pr[]c
	Pr[][

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
return new Proc(args).Process();

/// <summary>
/// Процессор.
/// </summary>
class Proc
{
	private readonly string[] _args;
	private Interop.FileStream _source;
	private Interop.FileStream _destination;
	private CharStream _charReader;
	private Symbol _lexer;
	private ProcSyntax _syntaxReader;
	private Generator _generator;

	public Proc(string[] args)
	{
		_args = args;
		_source = null;
		_charReader = null;
	}

	// Пример параметров "-l Examples/1.base.proc".
	public int Process()
	{
		if (_args.Length <= 1)
		{ // Первым параметром всегда идёт полный путь к исполняемому файлу.
			Console.Write("Usage: proc [--version] [--help] <command>\n\n");
			Console.Write("There are common Proc commands:\n\n");
			Console.Write("-l FILE\t\t\tuse lexical analysis on FILE\n");
		}
		else if (_args[0] == "-l")
		{ // Лексический анализ файла.
			_source = new Interop.FileStream(_args[1], FileMode.Open, FileAccess.Read); // Базовый поток состояний, используемый процессором и дочерними анализаторами.
			_destination = new Interop.FileStream($"{Path.GetFileNameWithoutExtension(_args[1])}.exe", FileMode.Create, FileAccess.Write);
			_charReader = new Utf8((Reader)_source); // Символьный поток определённой кодировки.
			// В Roslyn следующие строки создаются в SyntaxTree Oo.
			_lexer = new ProcSymbol(_charReader); // Лексический анализатор исходного кода.
			_syntaxReader = new ProcSyntax(_lexer); // Синтаксический анализатор.
			// TODO Генерацию можно выполнить несколькими путями:
			// TODO Получить готовое синтаксическое дерево и сгенерировать код.
			// TODO Или получить на вход синтаксический анализатор и в процессе генерации дерева, сформировать код.
			_generator = new Generator(_destination, _syntaxReader);
			_generator.CompileAndEmit();
		}

		return 0;
	}
}
