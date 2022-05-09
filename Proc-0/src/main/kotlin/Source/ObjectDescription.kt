package proc.Source.Symbol

/**
 * Запись (или вход), связывающая объявленный идентификатор (символ) с соответствующим объектом и его свойствами.
 */
class ObjectDescription {

	/**
	 * Класс объекта: переменная, константа, тип, процедура.
	 */
	public var Class: ClassMode

	/**
	 * Модификатор доступа.
	 */
	public var AccessModifier: AccessModifier

	/**
	 * Уровень объявления, например в параметрах процедуры.
	 */
	public var Level: Int

	/**
	 * Имя объявления.
	 */
	public var Name: proc.Text.String

	/**
	 * Следующее объявление текущего уровня.
	 */
	public var Next: ObjectDescription?

	/**
	 * Первое объявление предыдущего нисходящего уровня.
	 */
	public var Descending: ObjectDescription?

	/**
	 * Тип объявления.
	 */
	public var Type: TypeDescription?

	/**
	 * Значение?
	 */
	public var Value: Long

	init {
		Class = ClassMode.Head
		AccessModifier = proc.Source.Symbol.AccessModifier.Private
		Level = 0
		Name = proc.Text.String("")
		Next = null
		Descending = null
		Type = null
		Value = 0
	}
}
