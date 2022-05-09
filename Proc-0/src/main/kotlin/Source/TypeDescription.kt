package proc.Source.Symbol

/**
 * В языках, имеющих типы данных, проверка их совместимости является одной из важнейших задач компилятора.
 * Проверка основана на атрибуте `ObjectDescription.Type`, вносимом в каждую запись таблицы символов.
 */
class TypeDescription {

	/**
	 * Представление типа.
	 */
	public enum class TypeForm
	{
		Class,
		Array,
		Boolean,
		Integer,
	}

	/**
	 * Тип описываемого объекта.
	 */
	public var Form: TypeForm

	/**
	 * Размер элементарного типа, определяемого архитектурой?
	 */
	public var Size: Int

	/**
	 * Количество элементов массива.
	 */
	public var Length: Int

	/// <summary>
	/// Элементы класса.
	/// </summary>
	public var Fields: List<ObjectDescription>

	/// <summary>
	/// Тип элементов массива.
	/// </summary>
	public var Base: TypeDescription?

	init {
		Form = TypeForm.Class
		Size = 0
		Length = 0
		Base = null
		Fields = listOf<ObjectDescription>()
	}
}
