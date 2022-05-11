package proc.Machine.Proc

import proc.Source.SymbolReader
import proc.Source.SyntaxReader
import proc.Source.Error
import proc.Source.Symbol.*

/**
 * Синтаксический анализатор процессора.
 * Proc[]
 * []Proc
 * Pr[]c
 * Pr[][
 */
class ProcSyntax : SyntaxReader {

	//region Fields

	private var _guard: ObjectDescription
	private var _topScope: ObjectDescription
	private var _universe: ObjectDescription

	//endregion

	// OBSOLETE
	// А может сделать как-то общую цепочку для любого языка?
	// stream -> streamN -> lex -> synt

	// Вместо цепочки можно использовать сразу анализатор.
	//ISyntaxAnalyzer syntaxAnalyzer

	constructor(symbolToken: SymbolReader) : super(symbolToken) {
		_guard = ObjectDescription()
		_guard.Class = ClassMode.Variable
		_guard.Type = null // Нужен ли здесь тип из генератора кода?
		_guard.Value = 0
		_universe = ObjectDescription()
		_topScope = ObjectDescription()
		OpenScope()
		Enter(ClassMode.SProc, 1, proc.Text.String("Read"), null)
		Enter(ClassMode.SProc, 2, proc.Text.String("Write"), null)
		Enter(ClassMode.SProc, 3, proc.Text.String("WriteHex"), null)
		Enter(ClassMode.SProc, 4, proc.Text.String("WriteLn"), null)
		_universe = _topScope
	}

	//public Proc(ISyntaxAnalyzer syntaxAnalyzer) { } // Сразу перейти в состояние другого процессора.

	/**
	 * Перевод машины в состояние ошибки.
	 */
	protected fun SetError(error: Error, message: proc.Text.String) {
		Error = error

		// TODO Переделать отладку.
		println("error_file:$_lexer.ErrorLine:$_lexer.ErrorPosition: $message")
	}

	/**
	 * Добавление в начало списка между <see cref="ObjectDescription"/> и <see cref="ObjectDescription.Next"/> нового описателя типа.
	 */
	public fun Enter(classMode: ClassMode, value: Long, name: proc.Text.String, type: TypeDescription?) {
		_topScope.Next = ObjectDescription()
		_topScope.Class = classMode
		_topScope.Value = value
		_topScope.Name = name
		_topScope.Type = type
		_topScope.Descending = null
		_topScope.Next = _topScope.Next
	}

	private fun OpenScope() {
		_topScope = ObjectDescription()
		_topScope.Class = ClassMode.Head
		_topScope.Descending = _topScope
		_topScope.Next = _guard
	}

	private fun CloseScope() {
		_topScope = _topScope.Descending!!
	}

	/**
	 * Определение метода.
	 */
	private fun MethodDeclaration() {
	}

	/**
	 * Аналог Обероновского NewObj.
	 */
	private fun NewObject(accessModifier: AccessModifier, classMode: ClassMode): ObjectDescription? {
		var x: ObjectDescription = _topScope
		//while (x.Next != null && x.Next.Name != _lexer.Identifier) {
		//	x = x.Next
		//}
		if (x.Next == null)
		{
			var newObj: ObjectDescription = ObjectDescription()
			newObj.Name = _lexer.Identifier
			newObj.AccessModifier = accessModifier
			newObj.Class = classMode
			newObj.Next = null
			x.Next = newObj
			return newObj
		}
		else
		{
			SetError(proc.Source.Error.None, proc.Text.String("Multiple definition."))
			return x.Next
		}
	}

	private fun CheckInt(x: Item) {
	}

	private fun CheckBool(x: Item) {
	}

	private fun Factor(x: Item) {
	}

	private fun Term(x: Item) {
		var y = Item()
		Factor(x)
		while (_lexer.Type >= Type.Asterisk && _lexer.Type <= Type.AndPredicate)
		{
			var op: Type = _lexer.Type
			_lexer.Read()
			if (op == Type.Asterisk)
			{
				CheckInt(x)
				Factor(y)
				CheckInt(y)
				//OSG.MulOp(x, y)
			}
			else if (op == Type.Slash || op == Type.PercentSign)
			{
				CheckInt(x)
				Factor(y)
				CheckInt(y)
				//OSG.DivOp(op, x, y)
			}
			else // op == and
			{
				CheckBool(x)
				//OSG.And1(x)
				Factor(y)
				CheckBool(y)
				//OSG.And2(x, y)
			}
		}
	}

	private fun SimpleExpression(): Item {
		var x = Item()
		var y = Item()

		if (_lexer.Type == Type.PlusSign) {
			_lexer.Read()
			Term(x)
			CheckInt(x)
		} else if (_lexer.Type == Type.HyphenMinus) {
			_lexer.Read()
			Term(x)
			CheckInt(x)
			//OSG.Neg(x)
		} else {
			Term(x)
		}

		// TODO Исправить условие.
		while ((_lexer.Type as Int >= Type.PlusSign as Int) && (_lexer.Type as Int <= Type.OrPredicate as Int)) {
			var op: Type = _lexer.Type
			_lexer.Read()
			if (op == Type.OrPredicate) {
				//OSG.Or1(x)
				CheckBool(x)
				Term(y)
				CheckBool(y)
				//OSG.Or2(x, y)
			} else {
				CheckInt(x)
				Term(y)
				CheckInt(y)
				//OSG.AddOp(op, x, y)
			}
		}

		return x
	}

	private fun Expression(): Item {
		var x: Item = SimpleExpression()

		// TODO Переписать условие EQL и GEQ.
		if ((_lexer.Type as Int >= Type.EqualsPredicate as Int) && (_lexer.Type as Int <= Type.GreaterThanOrEqualPredicate as Int)) {
			var op: Type = _lexer.Type
			_lexer.Read()
			var y: Item = SimpleExpression()
			//if (x.Type == y.Type) OSG.Relation(op, x, y); else SetError(Error.None, "Incompatible types.");
			//x.Type = OSG.boolType
		}

		return x
	}

	/**
	 * Разбор сразу нескольких объявлений.
	 */
	private fun Declarations() {
		var modifier = AccessModifier.Private
		//ObjectDescription declaration = null

		// Синхронизация.
		// TODO Исправить условия синхронизации.
		if (_lexer.Type < Type.Constant && _lexer.Type != Type.EndOfStream) {
			SetError(proc.Source.Error.None, proc.Text.String("Is a declaration?"))
			do {
				_lexer.Read()
			} while (!(_lexer.Type >= Type.Constant || _lexer.Type == Type.EndOfStream)) // Поиск терминала, который понимает компилятор.
		}

		// Определение модификатора доступа:
		when (_lexer.Type) {
			Type.Private -> _lexer.Read()
			Type.Protected -> {
				modifier = AccessModifier.Protected
				_lexer.Read()
			}
			Type.Public -> {
				modifier = AccessModifier.Public
				_lexer.Read()
			}
			else -> {
			}
		}

		// Описание константы.
		if (_lexer.Type == Type.Constant) {
			_lexer.Read()
			while (_lexer.Type == Type.Identifier) {
				var obj = NewObject(modifier, ClassMode.Constant)
				_lexer.Read()
				if (_lexer.Type == Type.EqualsPredicate)
					_lexer.Read()
				else
					SetError(proc.Source.Error.None, proc.Text.String("=?"))
				var x: Item = Expression()
				if (x.Mode == ClassMode.Constant && obj != null) {
					obj.Value = x.A
					obj.Type = x.Type
				} else {
					SetError(proc.Source.Error.None, proc.Text.String("Expression is not a constant."))
				}
			}
		} else if (_lexer.Type == Type.Static) {
			// TODO Реализовать статические поля.
		}


	}

	/**
	 * Проверка того, что объект определён выше.
	 * @param classMode Класс объекта.
	 * @param name Идентификатор объекта.
	 */
	private fun IsDeclared(classMode: ClassMode, name: proc.Text.String): Boolean {
		var level: ObjectDescription? = _topScope
		while (level != null) {
			var current: ObjectDescription? = level
			while (current != null) {
				if (current.Name == name && current.Class == classMode)
					return true

				current = current.Next
			}
			level = level.Descending
		}

		return false
	}

	/**
	 * Начальное состояние машины.
	 * Альтернативный пример: roslyn\src\Compilers\CSharp\Portable\Parser\LanguageParser.cs (406)
	 */
	public override fun Global() {
		Scope()

		if (Error == proc.Source.Error.None) {
			println("Syntax tree has been generated.")
		}
	}

	/**
	 * Очередная область видимости.
	 */
	private fun Scope() {
		OpenScope() // Новая область видимости.

		_lexer.Read() // Считывание следующей лексемы.

		while (_lexer.Type != Type.EndOfStream)
		{
			Statement()
		}

		CloseScope()
	}

	/**
	 * Базовая конструкция языка.
	 */
	private fun Statement() {
		// Возможные очередные продукции.
		when (_lexer.Type) {
			// Определение переменной, константы, поля, функции и т.п.
			Type.Private,
			Type.Protected,
			Type.Public,
			Type.Constant,
			Type.Static,
			Type.Integer -> Declarations()

			Type.Identifier -> {
				if (IsDeclared(ClassMode.Type, _lexer.Identifier))
					Declarations()
			}

			/*case Type.Identifier:
				break
			case Type.LeftParenthesis:
				break
			case Type.LeftSquareBracket:
				break

			case Type.Class:
				break
			case Type.Enumeration:
				break
			case Type.Comment:*/

			else -> {
			}
		}

		//int i = 0
		//do
		//{
		//	_lexer.Read()
		//	i++
		//} while (_lexer.Type != Type.EndOfStream)
		//Console.WriteLine($"Proc lexer ready with {i} states.")

		//// Отладочная информация.
		//if (unicode < 256)
		//	printf_s("%c", unicode)
		//else
		//	printf_s("[%u]", unicode)

		//
		//OpenScope()
		//varsize = 0
		//if (sym == IDENT)
		//{
		//	idCpy(modid, id)
		//	Get() // Точка с запятой после идентификатора.
		//	fprintf(writerOut, "Compilation of '%s' module...\n\n", modid)
		//	// Лог Оберона: Texts.Append(Oberon.Log, W.buf)
		//}
		//else
		//{
		//	Mark("is an identifier?")
		//}
		//if (sym == SEMICOLON)
		//{
		//	Get()
		//}
		//else
		//{
		//	Mark("; ?")
		//}
		//Declarations(varsize)
		//while (sym == PROCEDURE)
		//{
		//	ProcedureDecl()
		//	if (sym == SEMICOLON)
		//	{
		//		Get()
		//	}
		//	else
		//	{
		//		Mark("; ?")
		//	}
		//}
		//Header(varsize)
		//if (sym == BEGIN)
		//{
		//	Get()
		//	StatSequence()
		//}
		//if (sym == END)
		//{
		//	Get()
		//}
		//else
		//{
		//	Mark("END?")
		//}
		//if (sym == IDENT)
		//{
		//	if (strcmp(modid, id) != 0)
		//	{
		//		Mark("is not fit.")
		//	}
		//	Get()
		//}
		//else
		//{
		//	Mark("is an identifier?")
		//}
		//if (sym != PERIOD)
		//{
		//	Mark(". ?")
		//}
		//CloseScope()
		//if (!error)
		//{
		//	// TODO Установка обработанного модуля idCpy(modid, s)
		//	// TODO Close(s, varsize)
		//	fprintf(writerOut, "Code has been generated %u\n", pc)
		//}
	}

	//public void ReadBody()
	//{
	//	throw new NotImplementedException()
	//}

	//public void ReadDefinition()
	//{
	//	throw new NotImplementedException()
	//}

	//// Чтение очередной конструкции.
	//// Вообще парсер видимо за один вызов должен всё обработать.
	//// Причем верхнем узлом будет модуль/листинг.
	//// Мне кажется Parse() все равно надо разбить на шаги.
	//// @return Количество успешно прочтённых TODO.
	//public int ReadSyntax()
	//{
	//	throw new NotImplementedException()
	//}
}
