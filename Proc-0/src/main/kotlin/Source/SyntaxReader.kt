package proc.Source

/**
 * Базовый класс синтаксического анализатора.
 */
abstract class SyntaxReader { // TODO Предполагается, что будет еще генератор SyntaxWriter, и оба будут как часть класса Syntax.

	protected val _lexer: SymbolReader

	public var Error: Error

	init {
		Error = proc.Source.Error.None
	}

	constructor(lexer: SymbolReader)
	{
		_lexer = lexer;
	}

	/**
	 * Основная цель как область видимости.
	 */
	public abstract fun Global()
}

public enum class Error
{
	None,
}
