/// <summary>
/// Синтаксический анализатор процессора.
/// Proc[]
/// []Proc
/// Pr[]c
/// Pr[][
/// </summary>
class ProcSyntax : SyntaxReader {

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
	public ProcSyntax(Symbol symbolToken) : base(symbolToken) {
	}

	//public Proc(ISyntaxAnalyzer syntaxAnalyzer) { } // Сразу перейти в состояние другого процессора.

	/// <summary>
	/// Начальное состояние машины.
	/// </summary>
	public override void Start() {
		int i = 0;
		do {
			_lexer.Read();
			i++;
		} while (_lexer.Type != Source.Symbol.Type.EndOfStream);
		Console.WriteLine($"Proc lexer ready with {i} states.");

		/*// Отладочная информация.
		if (unicode < 256)
			printf_s("%c", unicode);
		else
			printf_s("[%u]", unicode);*/
	}

	public override void ReadBody()
	{
		throw new NotImplementedException();
	}

	public override void ReadDefinition()
	{
		throw new NotImplementedException();
	}

	public override int ReadSyntax()
	{
		throw new NotImplementedException();
	}
}
