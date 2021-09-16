#pragma once

#ifndef STRING_HPP
#define STRING_HPP

#include "Temp/Dependency.h"

#include "Char.hpp"
#include "CharReader.hpp"
#include "CharWriter.hpp"
#include "CharSeeker.hpp"

class String {
private:
public:

	// Compares the first bytes of two areas of memory.
	// Returns zero if they are the same, a value less than zero if first value is
	// lexically less than second value, or a value greater than zero if first value
	// is lexically greater than second value.
	// Note that lexical order is determined as if comparing unsigned char arrays.
	static int Compare(const _char *value1, const _char *value2, size_t count) {
		register const _char *maxptr = value2 + count;
		register const _char *p1 = value1;
		register const _char *p2 = value2;
		while (*p1 && *p1 == *p2 && p2 < maxptr) ++p1, ++p2;
		return (*p1 > *p2) - (*p2 > *p1);
	}

	// Converts ASCII string to internal representation of string.
	static void ToString(const char *source, _char *destination, size_t maxCount) {
		register const _char *maxptr = destination + maxCount;
		register const char *p1 = source;
		register _char *p2 = destination;
		while (*p1 && p2 < maxptr) {
			*p2 = *p1;
			++p1, ++p2;
		}
		*p2 = 0; // ASCII null character.
	}
};

#define string String

#endif // STRING_HPP
