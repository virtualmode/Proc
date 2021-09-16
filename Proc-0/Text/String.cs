/// <summary>
/// Extension methods must be defined in a static class.
/// </summary>
public static class StringExtension
{
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
