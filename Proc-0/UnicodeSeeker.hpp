#pragma once

#ifndef UNICODE_SEEKER_H
#define UNICODE_SEEKER_H

#include "Temp/Dependency.h"

// Интерфейс поиска в символьном потоке.
class UnicodeSeeker {
public:
	virtual int SeekChar(object offset) = 0;
};

#endif // UNICODE_SEEKER_H
