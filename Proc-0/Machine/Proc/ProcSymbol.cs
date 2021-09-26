/// <summary>
/// Лексический анализатор Proc.
/// </summary>
class ProcSymbol: Symbol {

	/// <summary>
	/// Основной конструктор.
	/// </summary>
	/// <param name="charToken">Символьный поток.</param>
	public ProcSymbol(CharStream charToken):
		base(charToken) {
		EnterKeyword(SymbolType.Class, "class");
		EnterKeyword(SymbolType.Enumeration, "enum");
	}

	/// <summary>
	/// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	/// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	/// является ли для него состояние машины приемлемым для следующего шага.
	/// </summary>
	public override void ReadToken()
	{
		// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		if (_charToken.EndOfStream) {
			Type = SymbolType.EndOfStream;
			return;
		}

		// В зависимости от текущего состояния необходимо определить следующую m-конфигурацию.
		if (IsIdentifierLetter(false)) {
			ReadIdentifier();
		} else if (_charToken.IsWhitespace()) {
			ReadWhitespace();
		} else if (_charToken.IsDelimiter()) {
			ReadDelimiter();
		} else if (_charToken.IsEndOfLine()) {
			ReadEndOfLine();
		} else if (_charToken.IsDecimalDigit()) {
			ReadInteger();
		} else {
			ReadUnknown();
		}
	}
}
