package proc.Interop

/**
 * Писатель.
 */
interface Writer {

	/**
	 * Запись ЕДИНИЦЫ информации из другого потока в текущий поток?
	 * Предположительно любая область памяти в Proc будет потоком-лентой.
	 */
	fun Write(source: Reader): Object

	fun Write(source: Object, baseObj: Object) // TODO Временная заглушка для старых языков.
}
