#pragma once

#ifndef CHAR_WRITER_H
#define CHAR_WRITER_H

// Интерфейс символьного генератора.
class CharWriter {
public:
	virtual void WriteChar(int character) = 0;
};

#endif // CHAR_WRITER_H
