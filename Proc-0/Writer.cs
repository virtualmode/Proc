/// <summary>
/// Писатель.
/// </summary>
interface Writer
{
	/// <summary>
	/// Запись ЕДИНИЦЫ информации из другого потока в текущий поток?
	/// Предположительно любая область памяти в Proc будет потоком-лентой.
	/// </summary>
	object Write(Reader source);

	object Write(object source, object baseobj); // TODO Временная заглушка для старых языков.
}
