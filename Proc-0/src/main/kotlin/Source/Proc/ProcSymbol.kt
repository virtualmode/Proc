package proc.Source.Proc

import proc.Source.SymbolReader
import proc.Text.CharStream
import proc.Text.CharType

/**
 * Лексический анализатор Proc.
 */
class ProcSymbol : SymbolReader {

	/**
	 * Основной конструктор.
	 * @param charToken Символьный поток.
	 */
	constructor(charToken: CharStream) : super(charToken) {
		// Access modifiers.
		EnterKeyword(proc.Source.Symbol.Type.Private, "private")
		EnterKeyword(proc.Source.Symbol.Type.Protected, "protected")
		EnterKeyword(proc.Source.Symbol.Type.Public, "public")

		EnterKeyword(proc.Source.Symbol.Type.Constant, "const")
		EnterKeyword(proc.Source.Symbol.Type.Static, "static")

		EnterKeyword(proc.Source.Symbol.Type.Class, "class")
		EnterKeyword(proc.Source.Symbol.Type.Enumeration, "enum")
	}

	protected fun ReadNumber() {
	}

	/**
	 * Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	 * Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	 * является ли для него состояние машины приемлемым для следующего шага.
	 */
	public override fun Read() {
		// В зависимости от текущего состояния необходимо определить следующую m-конфигурацию.
		// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		if (_charToken.Type == CharType.EndOfStream)
			Type = proc.Source.Symbol.Type.EndOfStream

		else if (IsIdentifierLetter(false))
			ReadIdentifier()

		else if (_charToken.IsWhitespace())
			ReadWhitespace()

		else if (_charToken.IsEndOfLine())
			ReadEndOfLine()

		else if (_charToken.IsDecimalDigit()) // TODO Эта штука уйдет в метод разбора нетерминалов скорее всего, т.к. числа разные могут быть.
			ReadInteger() // Наверное переделать в считывание числа в принципе любого для языка.

		//region Простые терминалы

		/*else if (_charToken.Type == CharType.Comma) {
			_charToken.ReadChar()
			Type = Type.Comma
		}

		else if (_charToken.Type == CharType.Colon) {
			_charToken.ReadChar()
			Type = Type.Colon
		}

		else if (_charToken.Type == CharType.Semicolon) {
			_charToken.ReadChar()
			Type = Type.Semicolon
		}

		else if (_charToken.Type == CharType.Tilde) {
			_charToken.ReadChar()
			Type = Type.Tilde
		}

		else if (_charToken.Type == CharType.LeftParenthesis) {
			_charToken.ReadChar()
			Type = Type.LeftParenthesis
		}

		else if (_charToken.Type == CharType.RightParenthesis) {
			_charToken.ReadChar()
			Type = Type.RightParenthesis
		}

		else if (_charToken.Type == CharType.LeftCurlyBracket) {
			_charToken.ReadChar()
			Type = Type.LeftCurlyBracket
		}

		else if (_charToken.Type == CharType.RightCurlyBracket) {
			_charToken.ReadChar()
			Type = Type.RightCurlyBracket
		}

		else if (_charToken.Type == CharType.LeftSquareBracket) {
			_charToken.ReadChar()
			Type = Type.LeftSquareBracket
		}

		else if (_charToken.Type == CharType.RightSquareBracket) {
			_charToken.ReadChar()
			Type = Type.RightSquareBracket
		}*/

		//endregion Простые терминалы

		/*else if (_charToken.Type == CharType.Slash) {
			_charToken.ReadChar()
			if (_charToken.Type == CharType.EqualsSign) {
				_charToken.ReadChar()
				Type = Type.DivideAssignment
			} else {
				Type = Type.Slash
			}
		}

		else if (_charToken.Type == CharType.ExclamationMark) {
			_charToken.ReadChar()
			if (_charToken.Type == CharType.EqualsSign) {
				_charToken.ReadChar()
				Type = Type.NotEqualsPredicate
			} else {
				Type = Type.ExclamationMark
			}
		}

		else if (_charToken.Type == CharType.EqualsSign) {
			_charToken.ReadChar()
			if (_charToken.Type == CharType.EqualsSign) {
				_charToken.ReadChar()
				Type = Type.EqualsPredicate
			} else if (_charToken.Type == CharType.GreaterThanSign) {
			} else {
				Type = Type.ExclamationMark
			}
		}*/

		else {
			Type = proc.Source.Symbol.Type.Unknown
			_charToken.ReadChar()
		}
	}
}
