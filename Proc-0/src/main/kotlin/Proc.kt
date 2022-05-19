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
package proc

import proc.Interop.FileStream

/**
 * Процессор.
 */
class Proc(args: Array<String>) {
	private var _args: Array<String>
	private var _source: FileStream?
	//var Interop.FileStream _destination;
	//var CharStream _charReader;
	//var Symbol _lexer;
	//var ProcSyntax _syntaxReader;
	//var Generator _generator;

	init {
		_args = args
		_source = null
		//_charReader = null
	}

	// Пример параметров "-l Examples/1.base.proc".
	fun Process(): Int {
		if (_args.size <= 1) {
			// Первым параметром всегда идёт полный путь к исполняемому файлу.
			print("Usage: proc [--version] [--help] <command>\n\n")
			print("There are common Proc commands:\n\n")
			print("-l FILE\t\t\tuse lexical analysis on FILE\n")
		} else if (_args[0] == "-l") {
			// Try adding program arguments via Run/Debug configuration.
			// Learn more about running applications: https://www.jetbrains.com/help/idea/running-applications.html.
			println("Proc started with: $_args.joinToString()")
			// Лексический анализ файла.
			_source = FileStream(_args[1]) // Базовый поток состояний, используемый процессором и дочерними анализаторами.
			//_destination = new Interop.FileStream($"{Path.GetFileNameWithoutExtension(_args[1])}.exe", FileMode.Create, FileAccess.Write)
			//_charReader = new Utf8((Reader)_source) // Символьный поток определённой кодировки.
			// В Roslyn следующие строки создаются в SyntaxTree Oo.
			//_lexer = new ProcSymbol(_charReader) // Лексический анализатор исходного кода.
			//_syntaxReader = new ProcSyntax(_lexer) // Синтаксический анализатор.
			// TODO Генерацию можно выполнить несколькими путями:
			// TODO Получить готовое синтаксическое дерево и сгенерировать код.
			// TODO Или получить на вход синтаксический анализатор и в процессе генерации дерева, сформировать код.
			//_generator = new Generator(_destination, _syntaxReader)
			//_generator.CompileAndEmit()
		}

		return 0
	}
}

// Точка входа Proc-0.
fun main(args: Array<String>) {
	Proc(args).Process()
}

// Test function.
fun sum(a:Int, b: Int): Int {
	return a + b
}
