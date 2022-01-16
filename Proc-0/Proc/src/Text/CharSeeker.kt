package Text

/**
 * Интерфейс поиска в символьном потоке.
 */
interface CharSeeker {

	/**
	 * Номер текущего символа.
	 */
	var Position: Long
		get
		set

	/**
	 * Номер текущего символа в строке.
	 */
	var Character: Long
		get
		set

	/**
	 * Номер позиции символа в строке.
	 * Табуляция занимает несколько позиций.
	 */
	var Column: Long
		get
		set

	/**
	 * Номер текущей строки.
	 */
	var Line: Long
		get
		set

	fun SeekChar(offset: Long): Boolean
}
