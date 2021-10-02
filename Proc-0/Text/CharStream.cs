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

	public bool EndOfStream { get; set; }

	public long Position { get; set; }

	public long Character { get; set; }

	public long Column { get; set; }

	public long Line { get; set; }

	public abstract bool IsSmallLetter();
	public abstract bool IsCapitalLetter();
	public abstract bool IsLetter();

	public abstract bool IsDecimalDigit();

	public abstract bool IsSmallLatinLetter();
	public abstract bool IsCapitalLatinLetter();
	public abstract bool IsLatinLetter();


	public abstract bool IsDelimiter();
	public abstract bool IsEndOfLine();
	public abstract bool IsWhitespace();

	public abstract int ReadChar();
	public abstract void WriteChar(int character);
	public abstract bool SeekChar(long offset);
}
