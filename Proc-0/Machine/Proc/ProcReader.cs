/// <summary>
/// Синтаксический анализатор Proc.
/// </summary>
class ProcReader
{
	private Symbol _sourceToken;

	/// <summary>
	/// Основной конструктор.
	/// </summary>
	/// <param name="sourceToken">Поток лексем исходного кода.</param>
	public ProcReader(Symbol sourceToken)
	{
		_sourceToken = sourceToken;
	}
}
