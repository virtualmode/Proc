/*
	4. Первичная обработка исходного кода для компилятора или интерпретатора начинается с лексического анализа. Есть
	несколько способов реализации: обычная реализация, интерпретатор БНФ или регулярных выражений, компилятор
	анализаторов типа Lex. Для базовых языков подойдёт первый вариант, как самый простой и производительный.
	Если рассмотреть вообще любые данные, то при их первичной обработке происходит лексический анализ по сути, но место
	лексем могут занимать специфические конструкции: состояния, символы, цвета, заголовки, звуковые сэмплы и прочее.
	Чтение этих конструкций из потоков, запись и другие операции можно представить как часть одного и того же процесса.
	Такие классы задач можно выделить суффиксами в соответствии от их назначения, например Reader, Writer или Seeker.
*/

// TODO Пространства имён необходимо заменить объектами, чтобы не было проблемы неопределённости типа.
package proc.Source

import proc.Source.Symbol.Keyword
import proc.Source.Symbol.Type
import proc.Text.CharStream
import proc.Text.CharType
import proc.Source.Symbol.Error

/**
 * Лексический анализатор исходного кода, машина состояний, конечный автомат.
 * В других источниках можно встретить варианты: lexical analyzer, lexer, tokenizer, scanner, token reader.
 * Теоретически он должен быть написан для каждой поддерживаемой кодировки.
 * При чтении одного и того же набора символов в разных кодировках все реализации должны возвращать одинаковую лексему.
 * Набор лексем избавляет от необходимости создавать реализацию синтаксического анализатора для каждой кодировки.
 * Но если и текстовые потоки представить аналогичным образом, одного лексического анализатора также будет достаточно.
 */
abstract class SymbolReader { // TODO Это скорее не Symbol, а его часть - Symbol.Reader.

	companion object {
		public val KEYWORD_TABLE_SIZE: Int = 32
	}

	protected var _charToken: CharStream
	protected var _keywordCount: Int
	protected var _keywordTable: Array<Keyword>

	/**
	 * Тип символа.
	 */
	public var Type: Type

	// Нужно реализовать потоки состояний и возможность использования на них объединений union или cast.
	// Язык не должен ограничивать размер чисел из-за архитектуры процессора.
	public var Value: Long // Предполагается, что это и будет единственный поток состояний, хранящий значение лексемы.
	public var Real: Double // [Obsolete] Значение числа с плавающей точкой.
	public var Identifier: proc.Text.String // [Obsolete] Значение идентификатора.

	// TODO Состояние очередной ошибки можно вынести в отдельный интерфейс.
	// TODO Но если здесь достаточно одного состояния, то в синтаксическом анализаторе это может быть несколько ошибок за итерацию.
	public var Error: Error // Флаг наличия ошибки.
	public var ErrorPosition: Long // Позиция в символьном потоке.
	public var ErrorLine: Long // Строка с ошибкой.

	init {
		_keywordTable = Array<Keyword>(KEYWORD_TABLE_SIZE) { Keyword() }
		_keywordCount = 0
		Type = proc.Source.Symbol.Type.Unknown
		Identifier = proc.Text.String("")
		Error = proc.Source.Symbol.Error.None
		ErrorPosition = 0
		ErrorLine = 0
		Real = 0.0
		Value = 0
	}

	/**
	 * Основной конструктор.
	 */
	constructor(charToken: CharStream) {
		// TODO Это не токен в чистом виде, скорее надо переименовать в машину состояний.
		// TODO И передавать композицию интерфейсов CharToken и CharReader например.
		// TODO Но может быть если класс будет работать как дизассемблер, то и CharWriter.
		_charToken = charToken
		_charToken.ReadChar() // Предпросмотр оптимизирует код.
	}

	/**
	 * Перевод машины в состояние ошибки.
	 */
	protected fun SetError(error: Error, message: String)
	{
		Error = error
		ErrorPosition = _charToken.Position
		ErrorLine = _charToken.Line

		// TODO Переделать отладку.
		println("error_file: $ErrorLine:$ErrorPosition: $message")
	}

	/**
	 * Является ли текущий символ частью идентификатора.
	 * @param orDigit Учитывать цифры в середине и конце идентификатора.
	 */
	protected fun IsIdentifierLetter(orDigit: Boolean): Boolean {
		return _charToken.IsLetter() ||
			_charToken.Type == CharType.Underline ||
			(orDigit && _charToken.IsDecimalDigit())
	}

	protected fun ReadIdentifier() {
		Type = proc.Source.Symbol.Type.Identifier
		Value = 0
		do { // Считывание всего идентификатора.
			Identifier[Value as Int] += _charToken.Value
			Value++
			_charToken.ReadChar()
		} while (IsIdentifierLetter(true))
		Identifier[Value as Int] = 0 // Терминальный ноль.

		// Поиск совпадений с ключевыми словами.
		Value = 0
		while (Value < _keywordCount &&
			Identifier == _keywordTable[Value as Int].Identifier)
			Value++
		// Определение типа идентификатора.
		if (Value < _keywordCount)
		{
			Type = _keywordTable[Value as Int].Symbol // Терминальный символ из таблицы языка.
		}
		else
		{
			Type = proc.Source.Symbol.Type.Identifier // Идентификатор считается нетерминальный символ.
		}
	}

	protected fun ReadWhitespace() {
		Type = proc.Source.Symbol.Type.Whitespace
		Value = 0
		do
		{
			Value++
			_charToken.ReadChar()
		} while (_charToken.IsWhitespace())
	}

	/*protected fun ReadDelimiter() {
		Type = SymbolType.Delimiter
		Value = (long)_charToken.Type
		_charToken.ReadChar()
	}*/

	protected fun ReadEndOfLine() {
		Type = proc.Source.Symbol.Type.EndOfLine
		Value = 0
		do
		{
			Value++
			_charToken.ReadChar()
		} while (_charToken.IsEndOfLine())
	}

	/**
	 * Чтение целого числа.
	 */
	protected fun ReadInteger() {
		Type = proc.Source.Symbol.Type.Integer
		Value = 0
		do
		{
			if (Value <= (Long.MAX_VALUE - _charToken.Type as Long + CharType.Digit0 as Long) / 10)
			{
				Value = 10 * Value + _charToken.Type as Long - CharType.Digit0 as Long
			}
			else if (Error != proc.Source.Symbol.Error.None)
			{
				SetError(proc.Source.Symbol.Error.NumberOverflow, "Not enough long size to store number.")
			}
			_charToken.ReadChar()
		} while (_charToken.IsDecimalDigit())
	}

	/**
	 * Добавление зарезервированного слова.
	 */
	public fun EnterKeyword(symbol: Type, name: String) {
		if (_keywordTable[_keywordCount] == null)
			_keywordTable[_keywordCount] = Keyword()

		_keywordTable[_keywordCount].Symbol = symbol
		_keywordTable[_keywordCount].Identifier = proc.Text.String(name)
		_keywordCount++
	}

	/**
	 * Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	 * Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	 * является ли для него состояние машины приемлемым для следующего шага.
	 */
	public abstract fun Read()

}
