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
	/// 
	/// </summary>
	public ProcSyntax(Symbol symbolToken) : base(symbolToken) {
	}

	//public Proc(ISyntaxAnalyzer syntaxAnalyzer) { } // Сразу перейти в состояние другого процессора.

	/// <summary>
	/// Начальное состояние машины.
	/// </summary>
	public override void Read() {
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

	//public void ReadBody()
	//{
	//	throw new NotImplementedException();
	//}

	//public void ReadDefinition()
	//{
	//	throw new NotImplementedException();
	//}

	//// Чтение очередной конструкции.
	//// Вообще парсер видимо за один вызов должен всё обработать.
	//// Причем верхнем узлом будет модуль/листинг.
	//// Мне кажется Parse() все равно надо разбить на шаги.
	//// @return Количество успешно прочтённых TODO.
	//public int ReadSyntax()
	//{
	//	throw new NotImplementedException();
	//}
}
