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
	/// Перевод машины в состояние ошибки.
	/// </summary>
	protected void SetError(Error error, String message)
	{
		Error = error;

		// TODO Переделать отладку.
		Console.WriteLine($"error_file:{_lexer.ErrorLine}:{_lexer.ErrorPosition}: {message}");
	}

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
			Descending = null,
			Next = _topScope.Next
		};
	}

	private void OpenScope()
	{
		_topScope = new ObjectDescription()
		{
			Class = ClassMode.Head,
			Descending = _topScope,
			Next = _guard
		};
	}

	private void CloseScope()
	{
		_topScope = _topScope.Descending;
	}

	/// <summary>
	/// Определение метода.
	/// </summary>
	private void MethodDeclaration()
	{

	}

	//PROCEDURE NewObj(VAR obj: OSG.Object; class: INTEGER);
	//  VAR new, x: OSG.Object;
	//BEGIN x := topScope;
	//  WHILE (x.next # NIL) & (x.next.name # OSS.id) DO x := x.next END ;
	//  IF x.next = NIL THEN
	//    NEW(new); new.name := OSS.id; new.class := class; new.next := NIL;
	//    x.next := new; obj := new
	//  ELSE obj := x.next; OSS.Mark("mult def")
	//  END
	//END NewObj;


	private void NewObject(ObjectDescription obj, ClassMode classMode)
	{
		var x = _topScope;
		while (x.Next != null && x.Next.Name != _lexer.Identifier)
		{
			x = x.Next;
		}
		if (x.Next == null)
		{

		}
		else
		{
			obj = x.Next;
			SetError(Error.None, "Mult def");
		}
	}

	/// <summary>
	/// Разбор сразу нескольких объявлений.
	/// </summary>
	private void Declarations()
	{
		ObjectDescription declaration = null;

		// Синхронизация.
		// TODO Исправить условия синхронизации.
		if (_lexer.Type < Type.Constant && _lexer.Type != Type.EndOfStream)
		{
			SetError(Error.None, "Is a declaration?");
			do
			{
				_lexer.Read();
			} while (!(_lexer.Type >= Type.Constant || _lexer.Type == Type.EndOfStream)); // Поиск терминала, который понимает компилятор.
		}

		while (true)
		{

		}

		if (_lexer.Type == Type.Constant)
		{
			_lexer.Read();

		}


		ObjectDescription newObj, x;
		x = _topScope;
		_guard.Name = _lexer.Identifier;
		while (x.Next.Name != _lexer.Identifier)
		{

		}

		var obj = new ObjectDescription()
		{
			Class = ClassMode.Constant,
			Name = _lexer.Identifier,

		};

		//struct ObjDesc *newObj, *x;
		//x = topScope;
		//idCpy(guard->name, id);
		//while (strcmp(x->next->name, id) != 0) {
		//	x = x->next;
		//}
		//if (objEql(x->next, guard)) {
		//	newObj = objNew();
		//	idCpy(newObj->name, id);
		//	newObj->class = class;
		//	newObj->next = guard;
		//	x->next = newObj;
		//	return newObj;
		//} else {
		//	Mark("redefinition.");
		//	return x->next;
		//}

	}

	/// <summary>
	/// Проверка того, что объект определён выше.
	/// </summary>
	/// <param name="classMode">Класс объекта.</param>
	/// <param name="name">Идентификатор объекта.</param>
	/// <returns></returns>
	private bool IsDeclared(ClassMode classMode, String name)
	{
		ObjectDescription level = _topScope;
		while (level != null)
		{
			ObjectDescription current = level;
			while (current != null)
			{
				if (current.Name == name && current.Class == classMode)
					return true;

				current = current.Next;
			}
			level = level.Descending;
		}

		return false;
	}

	/// <summary>
	/// Начальное состояние машины.
	/// Альтернативный пример: roslyn\src\Compilers\CSharp\Portable\Parser\LanguageParser.cs (406)
	/// </summary>
	public override void Global()
	{
		Scope();

		if (Error == Error.None)
		{
			Console.WriteLine("Syntax tree has been generated.");
		}
	}

	/// <summary>
	/// Очередная область видимости.
	/// </summary>
	private void Scope()
	{
		OpenScope(); // Новая область видимости.

		_lexer.Read(); // Считывание следующей лексемы.

		while (_lexer.Type != Type.EndOfStream)
		{
			Statement();
		}

		CloseScope();
	}

	/// <summary>
	/// Базовая конструкция языка.
	/// </summary>
	private void Statement()
	{
		// Возможные очередные продукции.
		switch (_lexer.Type)
		{
			// Определение переменной, константы, поля, функции и т.п.
			case Type.Private:
			case Type.Protected:
			case Type.Public:
			case Type.Constant:
			case Type.Static:
			case Type.Integer:
				Declarations();
				break;

			case Type.Identifier:
				if (IsDeclared(ClassMode.Type, _lexer.Identifier))
					Declarations();
				break;

			/*case Type.Identifier:
				break;
			case Type.LeftParenthesis:
				break;
			case Type.LeftSquareBracket:
				break;

			case Type.Class:
				break;
			case Type.Enumeration:
				break;*/

			//case Type.Comment:
			default:
				break;
		}

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
