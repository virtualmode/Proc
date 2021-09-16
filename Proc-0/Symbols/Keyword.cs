/// <summary>
/// Информация о зарезервированном слове.
/// </summary>
class Keyword
{
	public const int KEYWORD_ID_SIZE = 32;

	public SymbolType Symbol;
	public int[] Identifier = new int[KEYWORD_ID_SIZE];
}
