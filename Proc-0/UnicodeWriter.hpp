#pragma once

#ifndef UNICODE_WRITER_H
#define UNICODE_WRITER_H

// Интерфейс символьного генератора.
class UnicodeWriter {
public:
	virtual void WriteChar(int character) = 0;
};

#endif // UNICODE_WRITER_H
