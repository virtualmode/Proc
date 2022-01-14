//namespace Source.Symbol;

using Source.Symbol;

/// <summary>
/// Атрибут синтаксически сворачиваемых символов.
/// </summary>
class Item
{
	/// <summary>
	/// Атрибут-режим соответствует режиму адресации команд компьютера, а диапазон его значений зависит от множества режимов адресации целевого компьютера.
	/// Режим для множителя, слагаемого, или выражения, т.е. определение где хранится его значение и как к нему обратиться.
	/// </summary>
	public ClassMode Mode;

	/// <summary>
	/// Уровень объявления, например в параметрах процедуры.
	/// </summary>
	public int Level;

	/// <summary>
	/// Тип объявления.
	/// </summary>
	public TypeDescription Type;

	/// <summary>
	/// Режим Var, класс Var, значение по адресу A.
	/// Режим Const, класс Const, значение есть константа A.
	/// </summary>
	public long A;

	/// <summary>
	/// ?
	/// </summary>
	public long B;

	/// <summary>
	/// ?
	/// </summary>
	public long C;

	/// <summary>
	/// Режим Reg, класса нет, значение содержится в регистре R.
	/// </summary>
	public long R;
}
