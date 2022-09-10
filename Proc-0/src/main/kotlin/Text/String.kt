package proc.Text

/**
 * Простая реализация строк.
 */
class String {

	//region Constants

	companion object {
		private val REALLOC_STEP: Int = 32
	}

	//endregion Constants

	//region Fields

	private var _value: IntArray
	private var _length: Int

	//endregion Fields

	//region Constructors

	init {
		_length = 0
		_value = IntArray(REALLOC_STEP)
	}

	constructor(value: String) {
		_length = value._length
		_value = IntArray(_length)
		System.arraycopy(value, 0, _value, 0, _length)
	}

	constructor(value: kotlin.String) {
		_value = IntArray(value.length)
		// Идея интервалов достаточно интересная, но смущает использование булева in для итераций.
		for (_length in 0 until value.length) { // Использование value.Indexes может быть неочевидным.
			_value[_length] = value[_length].code // Надеюсь здесь 4 байта.
		}
	}

	//endregion Constructors

	//region Некрасивый синтаксис

	//public int this[int index]
	//{
	//	get => _value[index]
	//	set => _value[index] = value
	//}

	operator fun get(index: Int): Int {
		return _value[index]
	}

	operator fun set(index: Int, value: Int) {
		_value[index] = value
	}

	override fun equals(other: Any?): Boolean {
		if (other is String) {
			return _value.contentEquals(other._value)
		}
		return super.equals(other)
	}

	/*public static String operator +(String value1, String value2)
	{
		int newLength = value1._length + value2._length
		if (value1._value.Length < newLength)
		{
			int[] newValue = new int[newLength + REALLOC_STEP]
			Array.Copy(value1._value, newValue, value1._length)
			value1._value = newValue
		}
		Array.Copy(value2._value, 0, value1._value, value1._length, value2._length)
		value1._length = newLength
		return value1
	}*/

	/**
	 * Для отладки.
	 */
	fun ToString(): kotlin.String {
		var result: kotlin.String = ""
		for (i in 0 until _value.size)
			result += _value[i] as kotlin.Char

		return result
	}

	//endregion

	/// <summary>
	/// Compares the first bytes of two areas of memory.
	/// Returns zero if they are the same, a value less than zero if first value is
	/// lexically less than second value, or a value greater than zero if first value
	/// is lexically greater than second value.
	/// Note that lexical order is determined as if comparing unsigned char arrays.
	/// </summary>
	//public static int Compare(this String value, String value1, String value2) {
	//	//register const _char* maxptr = value2 + count;
	//	//register const _char* p1 = value1;
	//	//register const _char* p2 = value2;
	//	//while (*p1 && *p1 == *p2 && p2 < maxptr) ++p1, ++p2;
	//	//return (*p1 > *p2) - (*p2 > *p1);
	//	return 0;
	//}

	/// <summary>
	/// Converts ASCII string to internal representation of string.
	/// </summary>
	//static void ToString(const char *source, _char *destination, size_t maxCount) {
	//	register const _char *maxptr = destination + maxCount;
	//	register const char *p1 = source;
	//	register _char *p2 = destination;
	//	while (*p1 && p2 < maxptr) {
	//		*p2 = *p1;
	//		++p1, ++p2;
	//	}
	//	*p2 = 0; // ASCII null character.
	//}
}
