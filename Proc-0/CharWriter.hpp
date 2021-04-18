#pragma once

#ifndef CHAR_WRITER_HPP
#define CHAR_WRITER_HPP

#include "Temp/Dependency.h"

// Интерфейс символьного генератора.
class CharWriter {
public:
	virtual void WriteChar(int character) = 0;
};

#endif // CHAR_WRITER_HPP
