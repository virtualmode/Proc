/// <summary>
/// Базовый класс синтаксического анализатора.
/// </summary>
abstract class SyntaxReader
{
	// Чтение очередной конструкции.
	// Вообще парсер видимо за один вызов должен всё обработать.
	// Причем верхнем узлом будет модуль/листинг.
	// Мне кажется Parse() все равно надо разбить на шаги.
	// @return Количество успешно прочтённых TODO.
	public abstract int ReadSyntax();

	public abstract void ReadBody();
	public abstract void ReadDefinition();
}
