/// <summary>
/// Базовый класс синтаксического анализатора.
/// </summary>
abstract class SyntaxReader // TODO Предполагается, что будет еще генератор SyntaxWriter, и оба будут как часть класса Syntax.
{
	protected readonly Symbol _lexer;

	public SyntaxReader(Symbol lexer)
	{
		_lexer = lexer;
	}

	public abstract void Read();
}
