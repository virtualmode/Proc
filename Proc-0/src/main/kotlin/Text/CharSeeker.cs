/// <summary>
/// Интерфейс поиска в символьном потоке.
/// </summary>
interface CharSeeker
{
	/// <summary>
	/// Номер текущего символа.
	/// </summary>
	long Position { get; protected set; }

	/// <summary>
	/// Номер текущего символа в строке.
	/// </summary>
	long Character { get; protected set; }

	/// <summary>
	/// Номер позиции символа в строке.
	/// Табуляция занимает несколько позиций.
	/// </summary>
	long Column { get; protected set; }

	/// <summary>
	/// Номер текущей строки.
	/// </summary>
	long Line { get; protected set; }

	bool SeekChar(long offset);
}
