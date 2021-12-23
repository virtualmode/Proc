//namespace Source.Symbol;

using Source.Symbol;
using String = Text.String;

/// <summary>
/// Запись (или вход), связывающая объявленный идентификатор (символ) с соответствующим объектом и его свойствами.
/// </summary>
class ObjectDescription
{
	/// <summary>
	/// Класс объекта: переменная, константа, тип, процедура.
	/// </summary>
	public ClassMode Class;

	/// <summary>
	/// Уровень объявления, например в параметрах процедуры.
	/// </summary>
	public int Level;

	/// <summary>
	/// Имя объявления.
	/// </summary>
	public String Name;

	/// <summary>
	/// Следующее объявление текущего уровня.
	/// </summary>
	public ObjectDescription Next;

	/// <summary>
	/// Первое объявление предыдущего нисходящего уровня.
	/// </summary>
	public ObjectDescription Descending;

	/// <summary>
	/// Тип объявления.
	/// </summary>
	public TypeDescription Type;

	/// <summary>
	/// Значение?
	/// </summary>
	public long Value;
}
