/*
	4. Первичная обработка исходного кода для компилятора или интерпретатора начинается с лексического анализа. Есть
	несколько способов реализации: обычная реализация, интерпретатор БНФ или регулярных выражений, компилятор
	анализаторов типа Lex. Для базовых языков подойдёт первый вариант, как самый простой и производительный.
	Если рассмотреть вообще любые данные, то при их первичной обработке происходит лексический анализ по сути, но место
	лексем могут занимать специфические конструкции: состояния, символы, цвета, заголовки, звуковые сэмплы и прочее.
	Чтение этих конструкций из потоков, запись и другие операции можно представить как часть одного и того же процесса.
	Такие классы задач можно выделить суффиксами в соответствии от их назначения, например Reader, Writer или Seeker.
*/

using System.Runtime.CompilerServices;

/// <summary>
/// Лексический анализатор исходного кода, машина состояний, конечный автомат.
/// В других источниках можно встретить варианты: lexical analyzer, lexer, tokenizer, scanner, token reader.
/// Теоретически он должен быть написан для каждой поддерживаемой кодировки.
/// При чтении одного и того же набора символов в разных кодировках все реализации должны возвращать одинаковую лексему.
/// Набор лексем избавляет от необходимости создавать реализацию синтаксического анализатора для каждой кодировки.
/// Но если и текстовые потоки представить аналогичным образом, одного лексического анализатора также будет достаточно.
/// </summary>
abstract class Symbol
{
	public const int KEYWORD_TABLE_SIZE = 32;

	protected CharStream _charToken;
	protected int _keywordCount;
	protected Keyword[] _keywordTable = new Keyword[KEYWORD_TABLE_SIZE];

	/// <summary>
	/// Тип символа.
	/// </summary>
	public SymbolType Type;

	// Нужно реализовать потоки состояний и возможность использования на них объединений union или cast.
	// Язык не должен ограничивать размер чисел из-за архитектуры процессора.
	public long Value; // Предполагается, что это и будет единственный поток состояний, хранящий значение лексемы.
	public double Real; // [Obsolete] Значение числа с плавающей точкой.
	public int[] Identifier = new int[Keyword.KEYWORD_ID_SIZE]; // [Obsolete] Значение идентификатора.

	// TODO Состояние очередной ошибки можно вынести в отдельный интерфейс.
	// TODO Но если здесь достаточно одного состояния, то в синтаксическом анализаторе это может быть несколько ошибок за итерацию.
	public SymbolError Error; // Флаг наличия ошибки.
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
		_keywordCount = 0;
		Type = SymbolType.Unknown;
		Error = SymbolError.None;
	}

	/// <summary>
	/// Перевод машины в состояние ошибки.
	/// </summary>
	protected void SetError(SymbolError error, string message)
	{
		Error = error;
		ErrorPosition = _charToken.Position;
		ErrorLine = _charToken.Line;
	}

	/// <summary>
	/// Является ли текущий символ частью идентификатора.
	/// </summary>
	/// <param name="orDigit">Учитывать цифры в середине и конце идентификатора.</param>
	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected bool IsIdentifierLetter(bool orDigit)
	{
		return !_charToken.EndOfStream &&
			_charToken.Type == CharType.Underline ||
			_charToken.IsLatinLetter() || // TODO Можно расширить поддержку идентификаторов.
			(orDigit && _charToken.IsDecimalDigit());
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadIdentifier()
	{
		Type = SymbolType.Identifier;
		Value = 0;
		do
		{ // Считывание всего идентификатора.
			if (Value < Keyword.KEYWORD_ID_SIZE)
			{
				// TODO Заменить на нормальные строки и символьные лексемы.
				Identifier[Value] = _charToken.Value;
				Value++;
			}
			_charToken.ReadChar();
		} while (IsIdentifierLetter(true));
		Identifier[Value] = '\0'; // Терминальный ноль.

		// Поиск совпадений с ключевыми словами.
		Value = 0;
		while (Value < _keywordCount &&
			//string.Compare(Identifier, _keywordTable[Value].Identifier, Keyword.KEYWORD_ID_SIZE) != 0)
			Identifier == _keywordTable[Value].Identifier) // TODO Переписать проверку правильно.
			Value++;
		// Определение типа идентификатора.
		if (Value < _keywordCount)
		{
			Type = _keywordTable[Value].Symbol; // Терминальный символ из таблицы языка.
		}
		else
		{
			Type = SymbolType.Identifier; // Идентификатор считается нетерминальный символ.
		}
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadWhitespace()
	{
		Type = SymbolType.Whitespace;
		Value = 0;
		do
		{
			Value++;
			_charToken.ReadChar();
		} while (_charToken.IsWhitespace());
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadDelimiter()
	{
		Type = SymbolType.Delimiter;
		Value = (long)_charToken.Type;
		_charToken.ReadChar();
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadEndOfLine()
	{
		Type = SymbolType.EndOfLine;
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
		Type = SymbolType.Integer;
		Value = 0;
		do
		{
			if (Value <= (long.MaxValue - (long)_charToken.Type + (long)CharType.Digit0) / 10)
			{
				Value = 10 * Value + (long)_charToken.Type - (long)CharType.Digit0;
			}
			else if (Error != SymbolError.None)
			{
				SetError(SymbolError.NumberOverflow, "Not enough long size to store number.");
			}
			_charToken.ReadChar();
		} while (_charToken.IsDecimalDigit());
	}

	[MethodImpl(MethodImplOptions.AggressiveInlining)]
	protected void ReadUnknown()
	{
		Type = SymbolType.Unknown;
		_charToken.ReadChar();
	}

	/// <summary>
	/// Добавление зарезервированного слова.
	/// </summary>
	public void EnterKeyword(SymbolType symbol, string name) {
		_keywordTable[_keywordCount].Symbol = symbol;
		//memcpy(_keywordTable[_keywordCount].Identifier, name, strlen(name));
		//string.ToString(name, _keywordTable[_keywordCount].Identifier, name.Length);
		//_keywordTable[_keywordCount].Identifier = name; // TODO Переписать присваивание правильно.
		_keywordCount++;
	}

	/// <summary>
	/// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	/// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	/// является ли для него состояние машины приемлемым для следующего шага.
	/// </summary>
	public abstract void ReadToken();
}
