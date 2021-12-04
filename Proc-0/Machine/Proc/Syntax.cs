using Source.Symbol;

using String = Text.String;
using Type = Source.Symbol.Type;

/// <summary>
/// Синтаксический анализатор процессора.
/// Proc[]
/// []Proc
/// Pr[]c
/// Pr[][
/// </summary>
class ProcSyntax : SyntaxReader
{

	#region Fields

	private ObjectDescription _guard;
	private ObjectDescription _topScope;
	private ObjectDescription _universe;

	#endregion

	// OBSOLETE
	// А может сделать как-то общую цепочку для любого языка?
	// stream -> streamN -> lex -> synt

	// Вместо цепочки можно использовать сразу анализатор.
	//ISyntaxAnalyzer syntaxAnalyzer

	/// <summary>
	/// 
	/// </summary>
	public ProcSyntax(Symbol symbolToken) : base(symbolToken)
	{
		_guard = new ObjectDescription()
		{
			Class = ClassMode.Variable,
			Type = null, // Нужен ли здесь тип из генератора кода?
			Value = 0
		};
		_universe = null;
		_topScope = null;
		OpenScope();
		Enter(ClassMode.SProc, 1, "Read", null);
		Enter(ClassMode.SProc, 2, "Write", null);
		Enter(ClassMode.SProc, 3, "WriteHex", null);
		Enter(ClassMode.SProc, 4, "WriteLn", null);
		_universe = _topScope;
	}

	//public Proc(ISyntaxAnalyzer syntaxAnalyzer) { } // Сразу перейти в состояние другого процессора.

	/// <summary>
	/// Добавление в начало списка между <see cref="ObjectDescription"/> и <see cref="ObjectDescription.Next"/> нового описателя типа.
	/// </summary>
	/// <param name="classMode"></param>
	/// <param name="value"></param>
	/// <param name="name"></param>
	/// <param name="type"></param>
	public void Enter(ClassMode classMode, long value, String name, TypeDescription type)
	{
		_topScope.Next = new ObjectDescription()
		{
			Class = classMode,
			Value = value,
			Name = name,
			Type = type,
			Dsc = null,
			Next = _topScope.Next
		};
	}

	private void OpenScope()
	{
		_topScope = new ObjectDescription()
		{
			Class = ClassMode.Head,
			Dsc = _topScope,
			Next = _guard
		};
	}

	private void CloseScope()
	{
		_topScope = _topScope.Dsc;
	}

	/// <summary>
	/// Определение метода.
	/// </summary>
	private void MethodDeclaration()
	{

	}

	/// <summary>
	/// Начальное состояние машины.
	/// </summary>
	public override void Global()
	{
		// Альтернативный пример: roslyn\src\Compilers\CSharp\Portable\Parser\LanguageParser.cs (406)

		_lexer.Read(); // Считывание следующей лексемы.

		OpenScope(); // Новая область видимости.

		// Возможные очередные терминалы.
		switch (_lexer.Type)
		{
			case Type.Identifier:
				break;



			// Определение переменной, функции, метода и т.п.
			case Type.Integer:
				break;
			case Type.LeftParenthesis:
				break;
			case Type.LeftSquareBracket:
				break;



			//case Type.Comment:
			default:
				break;
		}

		int a = 0x001001;

		//int i = 0;
		//do
		//{
		//	_lexer.Read();
		//	i++;
		//} while (_lexer.Type != Type.EndOfStream);
		//Console.WriteLine($"Proc lexer ready with {i} states.");

		//// Отладочная информация.
		//if (unicode < 256)
		//	printf_s("%c", unicode);
		//else
		//	printf_s("[%u]", unicode);

		//
		//OpenScope();
		//varsize = 0;
		//if (sym == IDENT)
		//{
		//	idCpy(modid, id);
		//	Get(); // Точка с запятой после идентификатора.
		//	fprintf(writerOut, "Compilation of '%s' module...\n\n", modid);
		//	// Лог Оберона: Texts.Append(Oberon.Log, W.buf);
		//}
		//else
		//{
		//	Mark("is an identifier?");
		//}
		//if (sym == SEMICOLON)
		//{
		//	Get();
		//}
		//else
		//{
		//	Mark("; ?");
		//}
		//Declarations(varsize);
		//while (sym == PROCEDURE)
		//{
		//	ProcedureDecl();
		//	if (sym == SEMICOLON)
		//	{
		//		Get();
		//	}
		//	else
		//	{
		//		Mark("; ?");
		//	}
		//}
		//Header(varsize);
		//if (sym == BEGIN)
		//{
		//	Get();
		//	StatSequence();
		//}
		//if (sym == END)
		//{
		//	Get();
		//}
		//else
		//{
		//	Mark("END?");
		//}
		//if (sym == IDENT)
		//{
		//	if (strcmp(modid, id) != 0)
		//	{
		//		Mark("is not fit.");
		//	}
		//	Get();
		//}
		//else
		//{
		//	Mark("is an identifier?");
		//}
		//if (sym != PERIOD)
		//{
		//	Mark(". ?");
		//}
		//CloseScope();
		//if (!error)
		//{
		//	// TODO Установка обработанного модуля idCpy(modid, s);
		//	// TODO Close(s, varsize);
		//	fprintf(writerOut, "Code has been generated %u\n", pc);
		//}
	}

	//public void ReadBody()
	//{
	//	throw new NotImplementedException();
	//}

	//public void ReadDefinition()
	//{
	//	throw new NotImplementedException();
	//}

	//// Чтение очередной конструкции.
	//// Вообще парсер видимо за один вызов должен всё обработать.
	//// Причем верхнем узлом будет модуль/листинг.
	//// Мне кажется Parse() все равно надо разбить на шаги.
	//// @return Количество успешно прочтённых TODO.
	//public int ReadSyntax()
	//{
	//	throw new NotImplementedException();
	//}
}
