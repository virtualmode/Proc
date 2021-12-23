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
//namespace Source;

using System.Runtime.CompilerServices;

using Source.Symbol;

using String = Text.String;
using Type = Source.Symbol.Type;

/// <summary>
/// Лексический анализатор исходного кода, машина состояний, конечный автомат.
/// В других источниках можно встретить варианты: lexical analyzer, lexer, tokenizer, scanner, token reader.
/// Теоретически он должен быть написан для каждой поддерживаемой кодировки.
/// При чтении одного и того же набора символов в разных кодировках все реализации должны возвращать одинаковую лексему.
/// Набор лексем избавляет от необходимости создавать реализацию синтаксического анализатора для каждой кодировки.
/// Но если и текстовые потоки представить аналогичным образом, одного лексического анализатора также будет достаточно.
/// </summary>
abstract class Symbol // TODO Это скорее не Symbol, а его часть - Symbol.Reader.
{
	public const int KEYWORD_TABLE_SIZE = 32;

	protected CharStream _charToken;
	protected int _keywordCount;
	protected Keyword[] _keywordTable;

	/// <summary>
	/// Тип символа.
	/// </summary>
	public Type Type;

	// Нужно реализовать потоки состояний и возможность использования на них объединений union или cast.
	// Язык не должен ограничивать размер чисел из-за архитектуры процессора.
	public long Value; // Предполагается, что это и будет единственный поток состояний, хранящий значение лексемы.
	public double Real; // [Obsolete] Значение числа с плавающей точкой.
	public String Identifier; // [Obsolete] Значение идентификатора.

	// TODO Состояние очередной ошибки можно вынести в отдельный интерфейс.
	// TODO Но если здесь достаточно одного состояния, то в синтаксическом анализаторе это может быть несколько ошибок за итерацию.
	public Source.Symbol.Error Error; // Флаг наличия ошибки.
	public long ErrorPosition; // Позиция в символьном потоке.
	public long ErrorLine; // Строка с ошибкой.

	/// <summary>
	/// Основной конструктор.
	/// </summary>
	/// <param name="charToken"></param>
	public Symbol(CharStream charToken)
	{
		// TODO Это не токен в чистом виде, скорее надо переименовать в машину состояний.
		// TODO И передавать композицию интерфейсов CharToken и CharReader например.
		// TODO Но может быть если класс будет работать как дизассемблер, то и CharWriter.
		_charToken = charToken;
		_charToken.ReadChar(); // Предпросмотр оптимизирует код.
		_keywordTable = new Keyword[KEYWORD_TABLE_SIZE];
		_keywordCount = 0;
		Type = Type.Unknown;
		Identifier = new String();
		Error = Source.Symbol.Error.None;
		ErrorPosition = 0;
		ErrorLine = 0;
		Real = 0.0d;
		Value = 0;
	}

	/// <summary>
	/// Перевод машины в состояние ошибки.
	/// </summary>
	protected void SetError(Source.Symbol.Error error, String message)
	{
		Error = error;
		ErrorPosition = _charToken.Position;
		ErrorLine = _charToken.Line;

		// TODO Переделать отладку.
		Console.WriteLine($"error_file:{ErrorLine}:{ErrorPosition}: {message}");
	}

	/// <summary>
	/// Является ли текущий символ частью идентификатора.
	/// </summary>
	/// <param name="orDigit">Учитывать цифры в середине и конце идентификатора.</param>
	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected bool IsIdentifierLetter(bool orDigit)
	{
		return _charToken.IsLetter() ||
			_charToken.Type == CharType.Underline ||
			(orDigit && _charToken.IsDecimalDigit());
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadIdentifier()
	{
		Type = Type.Identifier;
		Value = 0;
		do { // Считывание всего идентификатора.
			Identifier[Value] += _charToken.Value;
			Value++;
			_charToken.ReadChar();
		} while (IsIdentifierLetter(true));
		Identifier[Value] = '\0'; // Терминальный ноль.

		// Поиск совпадений с ключевыми словами.
		Value = 0;
		while (Value < _keywordCount &&
			Identifier == _keywordTable[Value].Identifier)
			Value++;
		// Определение типа идентификатора.
		if (Value < _keywordCount)
		{
			Type = _keywordTable[Value].Symbol; // Терминальный символ из таблицы языка.
		}
		else
		{
			Type = Type.Identifier; // Идентификатор считается нетерминальный символ.
		}
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadWhitespace()
	{
		Type = Type.Whitespace;
		Value = 0;
		do
		{
			Value++;
			_charToken.ReadChar();
		} while (_charToken.IsWhitespace());
	}

	/*[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadDelimiter()
	{
		Type = SymbolType.Delimiter;
		Value = (long)_charToken.Type;
		_charToken.ReadChar();
	}*/

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadEndOfLine()
	{
		Type = Type.EndOfLine;
		Value = 0;
		do
		{
			Value++;
			_charToken.ReadChar();
		} while (_charToken.IsEndOfLine());
	}

	/// <summary>
	/// Чтение целого числа.
	/// </summary>
	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadInteger()
	{
		Type = Type.Integer;
		Value = 0;
		do
		{
			if (Value <= (long.MaxValue - (long)_charToken.Type + (long)CharType.Digit0) / 10)
			{
				Value = 10 * Value + (long)_charToken.Type - (long)CharType.Digit0;
			}
			else if (Error != Source.Symbol.Error.None)
			{
				SetError(Source.Symbol.Error.NumberOverflow, "Not enough long size to store number.");
			}
			_charToken.ReadChar();
		} while (_charToken.IsDecimalDigit());
	}

	/// <summary>
	/// Добавление зарезервированного слова.
	/// </summary>
	public void EnterKeyword(Type symbol, string name) {
		if (_keywordTable[_keywordCount] == null)
			_keywordTable[_keywordCount] = new Keyword();

		_keywordTable[_keywordCount].Symbol = symbol;
		_keywordTable[_keywordCount].Identifier = name;
		_keywordCount++;
	}

	/// <summary>
	/// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	/// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	/// является ли для него состояние машины приемлемым для следующего шага.
	/// </summary>
	public abstract void Read();
}
