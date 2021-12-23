/// <summary>
/// Базовый класс синтаксического анализатора.
/// </summary>
abstract class SyntaxReader // TODO Предполагается, что будет еще генератор SyntaxWriter, и оба будут как часть класса Syntax.
{
	protected readonly Symbol _lexer;

	public Error Error;

	public SyntaxReader(Symbol lexer)
	{
		_lexer = lexer;
	}

	/// <summary>
	/// Основная цель как область видимости.
	/// </summary>
	public abstract void Global();
}

public enum Error
{
	None,
}
