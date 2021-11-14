using Source.Symbol;

/// <summary>
/// Генератор кода.
/// </summary>
class Generator
{
	private TypeDescription _boolType;
	private TypeDescription _integerType;

	private Writer _writer;
	private ProcSyntax _syntax;

	public Generator(Writer writer, ProcSyntax syntax)
	{
		_writer = writer;
		_syntax = syntax;

		_boolType = new TypeDescription()
		{
			Form = TypeDescription.TypeForm.Boolean,
			Size = 1
		};

		_integerType = new TypeDescription()
		{
			Form = TypeDescription.TypeForm.Integer,
			Size = 4
		};

		_syntax.Enter(ClassMode.Type, 1, "bool", _boolType);
		_syntax.Enter(ClassMode.Type, 2, "int", _integerType);
		_syntax.Enter(ClassMode.Constant, 1, "true", _boolType);
		_syntax.Enter(ClassMode.Constant, 0, "false", _boolType);

		// TODO Добавить регистрацию инструкций процессора.
	}

	public void Emit()
	{
		_syntax.Global(); // Основная цель синтаксического разбора.
	}
}
