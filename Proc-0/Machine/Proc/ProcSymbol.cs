using System.Runtime.CompilerServices;

/// <summary>
/// Лексический анализатор Proc.
/// </summary>
class ProcSymbol : Symbol
{
	/// <summary>
	/// Основной конструктор.
	/// </summary>
	/// <param name="charToken">Символьный поток.</param>
	public ProcSymbol(CharStream charToken) : base(charToken)
	{
		EnterKeyword(SymbolType.Class, "class");
		EnterKeyword(SymbolType.Enumeration, "enum");
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
	public override void ReadToken()
	{
		// В зависимости от текущего состояния необходимо определить следующую m-конфигурацию.
		// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		if (_charToken.Type == CharType.EndOfStream)
			Type = SymbolType.EndOfStream;

		else if (IsIdentifierLetter(false))
			ReadIdentifier();

		else if (_charToken.IsWhitespace())
			ReadWhitespace();

		else if (_charToken.IsEndOfLine())
			ReadEndOfLine();

		else if (_charToken.IsDecimalDigit()) // TODO Эта штука уйдет в метод разбора нетерминалов скорее всего, т.к. числа разные могут быть.
			ReadInteger(); // Наверное переделать в считывание числа в принципе любого для языка.

		#region Простые терминалы

		else if (_charToken.Type == CharType.Comma)
		{
			_charToken.ReadChar();
			Type = SymbolType.Comma;
		}

		else if (_charToken.Type == CharType.Colon)
		{
			_charToken.ReadChar();
			Type = SymbolType.Colon;
		}

		else if (_charToken.Type == CharType.Semicolon)
		{
			_charToken.ReadChar();
			Type = SymbolType.Semicolon;
		}

		else if (_charToken.Type == CharType.Tilde)
		{
			_charToken.ReadChar();
			Type = SymbolType.Tilde;
		}

		else if (_charToken.Type == CharType.LeftParenthesis)
		{
			_charToken.ReadChar();
			Type = SymbolType.LeftParenthesis;
		}

		else if (_charToken.Type == CharType.RightParenthesis)
		{
			_charToken.ReadChar();
			Type = SymbolType.RightParenthesis;
		}

		else if (_charToken.Type == CharType.LeftCurlyBracket)
		{
			_charToken.ReadChar();
			Type = SymbolType.LeftCurlyBracket;
		}

		else if (_charToken.Type == CharType.RightCurlyBracket)
		{
			_charToken.ReadChar();
			Type = SymbolType.RightCurlyBracket;
		}

		else if (_charToken.Type == CharType.LeftSquareBracket)
		{
			_charToken.ReadChar();
			Type = SymbolType.LeftSquareBracket;
		}

		else if (_charToken.Type == CharType.RightSquareBracket)
		{
			_charToken.ReadChar();
			Type = SymbolType.RightSquareBracket;
		}

		#endregion Простые терминалы

		else if (_charToken.Type == CharType.Slash)
		{
			_charToken.ReadChar();
			if (_charToken.Type == CharType.EqualsSign)
			{
				_charToken.ReadChar();
				Type = SymbolType.DivideAssignment;
			}
			else
			{
				Type = SymbolType.Slash;
			}
		}

		else if (_charToken.Type == CharType.ExclamationMark)
		{
			_charToken.ReadChar();
			if (_charToken.Type == CharType.EqualsSign)
			{
				_charToken.ReadChar();
				Type = SymbolType.NotEquals;
			}
			else
			{
				Type = SymbolType.ExclamationMark;
			}
		}

		else if (_charToken.Type == CharType.EqualsSign)
		{
			_charToken.ReadChar();
			if (_charToken.Type == CharType.EqualsSign)
			{
				_charToken.ReadChar();
				Type = SymbolType.EqualsPredicate;
			}
			else if (_charToken.Type == CharType.GreaterThanSign)
			else
			{
				Type = SymbolType.ExclamationMark;
			}
		}

		else
		{
			Type = SymbolType.Unknown;
			_charToken.ReadChar();
			
		}
	}
}
