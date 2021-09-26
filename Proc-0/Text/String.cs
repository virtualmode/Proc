
namespace Text;

//#nullable enable

/// <summary>
/// Простая реализация строк.
/// </summary>
public class String
{
	private const int REALLOC_STEP = 32;

	private int[] _value;
	private int _length;

	public String()
	{
		_length = 0;
		_value = new int[REALLOC_STEP];
	}

	public String(String value)
	{
		_length = value._length;
		_value = new int[_length];
		Array.Copy(value._value, _value, _length);
	}

	public String(string value)
	{
		_value = new int[value.Length];
		for (_length = 0; _length < value.Length; _length++)
		{
			_value[_length] = (int)value[_length];
		}
	}

	#region Некрасивый синтаксис

	public int this[int index]
	{
		get => _value[index];
		set => _value[index] = value;
	}

	public int this[long index]
	{
		get => _value[index];
		set => _value[index] = value;
	}

	/// <summary>
	/// Преобразование ко встроенному типу строк.
	/// </summary>
	public static implicit operator String(string value) => new String(value);

	public static bool operator ==(String value1, String value2) => Array.Equals(value1._value, value2._value);

	public static bool operator !=(String value1, String value2) => !Array.Equals(value1._value, value2._value);

	public static String operator +(String value1, String value2)
	{
		int newLength = value1._length + value2._length;
		if (value1._value.Length < newLength)
		{
			int[] newValue = new int[newLength + REALLOC_STEP];
			Array.Copy(value1._value, newValue, value1._length);
			value1._value = newValue;
		}
		Array.Copy(value2._value, 0, value1._value, value1._length, value2._length);
		return value1;
	}

	#endregion

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
