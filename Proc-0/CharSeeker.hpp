#pragma once

#ifndef CHAR_SEEKER_HPP
#define CHAR_SEEKER_HPP

#include "Temp/Dependency.h"

// Интерфейс поиска в символьном потоке.
class CharSeeker {
public:

	// Номер текущего символа.
	long Character;
	// Номер текущего символа в строке.
	long LineCharacter;
	// Номер текущей строки.
	long LineNumber;

	virtual int SeekChar(object offset) = 0;
};

#endif // CHAR_SEEKER_HPP
