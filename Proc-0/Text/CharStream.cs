/// <summary>
/// Интерфейс потока символов для работы с текстом.
/// TODO CharReader и CharWriter должны использоваться независимо.
/// TODO Необходимо добавить в язык возможность композиции интерфейсов.
/// TODO А пока придётся наследовать с другими необходимыми интерфейсами.
/// TODO После реализации композиции данный класс не будет иметь смысла.
/// </summary>
[Obsolete("Implement interface composition instead. Allow fields usage?")]
abstract class CharStream : Char, CharReader, CharWriter, CharSeeker
{
	public int Value { get; set; }

	public abstract CharType Type { get; protected set; }

	//public bool EndOfStream { get; set; }

	public long Position { get; set; }

	public long Character { get; set; }

	public long Column { get; set; }

	public long Line { get; set; }

	public abstract bool IsSmallLetter();
	public abstract bool IsCapitalLetter();

	// Является ли текущий символ буквой.
	public bool IsLetter()
	{
		return IsSmallLetter() || IsCapitalLetter();
	}

	// Является ли текущий символ арабской десятичной цифрой юникода.
	public bool IsDecimalDigit()
	{
		return Type >= CharType.Digit0 && Type <= CharType.Digit9;
	}

	// Является ли текущий символ строчной латинской буквой.
	public bool IsSmallLatinLetter()
	{
		return Type >= CharType.SmallLetterA && Type <= CharType.SmallLetterZ;
	}

	// Является ли текущий символ заглавной латинской буквой.
	public bool IsCapitalLatinLetter()
	{
		return Type >= CharType.CapitalLetterA && Type <= CharType.CapitalLetterZ;
	}

	// Является ли текущий символ латинской буквой.
	public bool IsLatinLetter()
	{
		return IsSmallLatinLetter() || IsCapitalLatinLetter();
	}

	// Символ относится к группе допустимых разделителей, используемых в компиляторе.
	// @deprecated Достаточно специфическая реализация для использования в таком виде.
	/*public bool IsDelimiter()
	{
		return (Type >= CharType.Space && Type <= CharType.Slash ||
			Type >= CharType.Colon && Type <= CharType.CommercialAt ||
			Type >= CharType.LeftSquareBracket && Type <= CharType.GraveAccent ||
			Type >= CharType.LeftCurlyBracket && Type <= CharType.Delete);
	}*/

	// Символ является разделителем строк или входит в последовательность разделения.
	// @deprecated Название не совсем соответствует действительности.
	public bool IsEndOfLine()
	{
		return Type == CharType.CarriageReturn ||
			Type == CharType.LineFeed ||
			Type == CharType.NextLine ||
			Type == CharType.LineSeparator ||
			Type == CharType.ParagraphSeparator ||
			Type == CharType.VerticalTabulation;
	}

	// Символ является отступом.
	// @deprecated Достаточно специфическая реализация для использования в таком виде.
	public bool IsWhitespace()
	{
		return Type == CharType.HorizontalTabulation ||
			Type == CharType.Space;
	}

	public abstract int ReadChar();
	public abstract void WriteChar(int character);
	public abstract bool SeekChar(long offset);
}
