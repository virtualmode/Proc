/// <summary>
/// Синтаксический анализатор процессора.
/// Proc[]
/// []Proc
/// Pr[]c
/// Pr[][
/// </summary>
class ProcSyntax {

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
	public ProcSyntax(Symbol symbolToken) {
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
		Console.WriteLine($"Proc lexer ready with {i} states.");

		/*// Отладочная информация.
		if (unicode < 256)
			printf_s("%c", unicode);
		else
			printf_s("[%u]", unicode);*/
	}
}
