package proc.Text

/**
 * Интерфейс поиска в символьном потоке.
 */
interface CharSeeker {

	/**
	 * Номер текущего символа.
	 */
	var Position: Long
		get
		set // protected

	/**
	 * Номер текущего символа в строке.
	 */
	var Character: Long
		get
		set // protected

	/**
	 * Номер позиции символа в строке.
	 * Табуляция занимает несколько позиций.
	 */
	var Column: Long
		get
		set // protected

	/**
	 * Номер текущей строки.
	 */
	var Line: Long
		get
		set // protected

	fun SeekChar(offset: Long): Boolean
}
