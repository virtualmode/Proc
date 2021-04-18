/*
	2. Универсальная машина не может работать без входных и выходных данных. Мне еще не известно, как эти данные должны
	выглядеть и передаваться. Поэтому необходимо ввести некоторую абстракцию для работы с потоками, известными как
	ленты. Каждая клетка ленты может содержать несколько различных значений, как в машине Тьюринга. На отдельных
	архитектурах такие клетки могут быть основаны на разных физических принципах и могут кодировать количество
	состояний - оснований, а объём данных можно выразить через логарифм общего количества состояний по основанию
	архитектуры. Такое представление объёма, к сожалению, возрастает экспоненциально, но полностью отвязывает код от
	оборудования.
*/

#pragma once

#ifndef FILE_STREAM_HPP
#define FILE_STREAM_HPP

#include "Temp/Dependency.h"

#include "Reader.hpp"
#include "Writer.hpp"

// Если использовать interface segregation, то может и не будет смысла в объединённом интерфейсе.
// Также есть идея объединений для безымянных композиций интерфейсов и др. типов.
//class Stream: public Reader, public Writer, public Seeker {
//};

// Compiler is not support state logic.
int BaseToBytes(object base) {
	return (int)log2(base) / 8;
}

// Файловый поток.
class FileStream: public Reader, public Writer {
private:

	int _handle; //!< Low-Level I/O file handle.

#ifdef PROC_OS_WIN
#else
#endif

public:

	// Запись: O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE
	// Чтение: O_BINARY | O_RDONLY, _S_IREAD
	bool Open(const char *fileName, int flags = O_BINARY | O_RDONLY | O_BINARY, int mode = _S_IREAD) {
#ifdef PROC_OS_WIN
		if ((_handle = _open(fileName, flags, mode)) <= 0) { // Открытие файла с использованием ANSI пути не удалось:
			wchar_t wFileName[512]; // Буфер для преобразования из UTF-8 в двубайтную строку.
			if (MultiByteToWideChar(CP_UTF8, NULL, fileName, -1, wFileName, 512) <= 0 || (_handle = _wopen(wFileName, flags, mode)) <= 0)
				return false;
		}
#else
		if ((_handle = open(path, flags, mode)) <= 0)
			return false;
#endif
		return true;
	}

	bool Close() {
		int result = 0;
		if (_handle > 0)
#ifdef PROC_OS_WIN
			result = _close(_handle);
#else
			result = close(_handle);
#endif
		_handle = 0;
		return result == 0;
	}

	FileStream(const char *fileName, int flags = O_BINARY | O_RDONLY | O_BINARY, int mode = _S_IREAD) {
		Open(fileName, flags, mode);
	}

	virtual ~FileStream() {
		Close();
	}

	// base - основание, количество состояний. В оригинале - количество байт.
	// Пока что тип данных будет выглядеть как base[exponent][exponent][..].
	// destination должен содержать указатель на место, в которое будет записано states состояний.
	virtual object Read(object destination, object base) {
#ifdef PROC_OS_WIN
		return (object)_read(_handle, (void *)destination, BaseToBytes(base));
#else
		return (object)read(_handle, (void *)destination, BaseToBytes(base));
#endif
	}

	virtual object Write(object source, object base) {
#ifdef PROC_OS_WIN
		return (ptrdiff_t)_write(_handle, (const void *)source, BaseToBytes(base));
#else
		return (ptrdiff_t)write(_handle, source, BaseToBytes(base));
#endif
	}

	virtual object Read(Writer *destination) {
		return NULL;
	}

	virtual object Write(Reader *source) {
		return NULL;
	}
};

#endif // FILE_STREAM_HPP
