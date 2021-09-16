#pragma once

#ifndef CHAR_SEEKER_HPP
#define CHAR_SEEKER_HPP

#include "Temp/Dependency.h"

// Интерфейс поиска в символьном потоке.
class CharSeeker {
public:

	// Номер текущего символа.
	long Position;

	// Номер текущего символа в строке.
	long Character;

	// Номер позиции символа в строке.
	// Табуляция занимает несколько позиций.
	long Column;

	// Номер текущей строки.
	long Line;

	virtual bool SeekChar(long offset) = 0;
};

#endif // CHAR_SEEKER_HPP
