//namespace Source.Symbol;

/// <summary>
/// В языках, имеющих типы данных, проверка их совместимости является одной из важнейших задач компилятора.
/// Проверка основана на атрибуте <see cref="ObjectDescription.Type"/>, вносимом в каждую запись таблицы символов.
/// </summary>
class TypeDescription
{
	/// <summary>
	/// Представление типа.
	/// </summary>
	public enum TypeForm
	{
		Class,
		Array,
		Boolean,
		Integer,
	}

	/// <summary>
	/// Тип описываемого объекта.
	/// </summary>
	public TypeForm Form;

	/// <summary>
	/// Размер элементарного типа, определяемого архитектурой?
	/// </summary>
	public int Size;

	/// <summary>
	/// Количество элементов массива.
	/// </summary>
	public int Length;

	/// <summary>
	/// Элементы класса.
	/// </summary>
	public List<ObjectDescription> Fields;

	/// <summary>
	/// Тип элементов массива.
	/// </summary>
	public TypeDescription Base;
}
