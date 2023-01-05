using System.Runtime.CompilerServices;

/// <summary>
/// Лексический анализатор документации.
/// </summary>
class HelpSymbol : Symbol
{
	/// <summary>
	/// Основной конструктор.
	/// </summary>
	/// <param name="charToken">Символьный поток.</param>
	public HelpSymbol(CharStream charToken) : base(charToken)
	{
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	private void ReadDelimiter()
	{
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadNumber()
	{
	}

	/// <summary>
	/// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	/// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	/// является ли для него состояние машины приемлемым для следующего шага.
	/// </summary>
	public override void Read()
	{
		//// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		//if (_charToken.Type == CharType.EndOfStream)
		//{
		//	Type = Source.Symbol.Type.EndOfStream;
		//	return;
		//}

		//// В зависимости от текущего состояния необходимо определить следующую m-конфигурацию.
		//if (IsIdentifierLetter(false))
		//	ReadIdentifier();
		//else if (_charToken.IsWhitespace())
		//	ReadWhitespace();
		//else if (_charToken.IsEndOfLine())
		//	ReadEndOfLine();
		//else if (_charToken.IsDecimalDigit())
		//	ReadInteger(); // Наверное переделать в считывание числа в принципе любого для языка.
		//else
		//	ReadDelimiter();
	}
}
