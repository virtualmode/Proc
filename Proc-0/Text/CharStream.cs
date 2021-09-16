/// <summary>
/// Интерфейс потока символов для работы с текстом.
/// TODO CharReader и CharWriter должны использоваться независимо.
/// TODO Необходимо добавить в язык возможность композиции интерфейсов.
/// TODO А пока придётся наследовать с другими необходимыми интерфейсами.
/// TODO После реализации композиции данный класс не будет иметь смысла.
/// </summary>
class CharStream : Char, CharReader, CharWriter, CharSeeker
{
	public int Value { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

	public CharType Type { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

	public bool EndOfStream { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

	public long Position { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

	public long Character { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

	public long Column { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

	public long Line { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

	public virtual bool IsCapitalLatinLetter()
	{
		throw new NotImplementedException();
	}

	public virtual bool IsDecimalDigit()
	{
		throw new NotImplementedException();
	}

	public virtual bool IsDelimiter()
	{
		throw new NotImplementedException();
	}

	public virtual bool IsEndOfLine()
	{
		throw new NotImplementedException();
	}

	public virtual bool IsLatinLetter()
	{
		throw new NotImplementedException();
	}

	public virtual bool IsSmallLatinLetter()
	{
		throw new NotImplementedException();
	}

	public virtual bool IsWhitespace()
	{
		throw new NotImplementedException();
	}

	public virtual int ReadChar()
	{
		throw new NotImplementedException();
	}

	public virtual bool SeekChar(long offset)
	{
		throw new NotImplementedException();
	}

	public virtual void WriteChar(int character)
	{
		throw new NotImplementedException();
	}
}
