package proc.Source.Proc

import proc.Source.SymbolReader
import proc.Text.CharStream

/**
 * Лексический анализатор документации.
 */
class HelpSymbol: SymbolReader {

	/**
	 * Основной конструктор.
	 * @param charToken Символьный поток.
	 */
	constructor(charToken: CharStream) : super(charToken) {
	}

	private fun ReadDelimiter() {
	}

	protected fun ReadNumber() {
	}

	/**
	 * Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	 * Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	 * является ли для него состояние машины приемлемым для следующего шага.
	 */
	public override fun Read() {
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
