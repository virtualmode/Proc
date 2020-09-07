
#include "Temp/Global.h"
#include "Stream.h"

// Compiler is not support state logic.
int BaseToBytes(object base) {
	return (int)log2(base) / 8;
}

bool FileStream::Open(const char *fileName, int flags, int mode) {
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

bool FileStream::Close() {
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

FileStream::FileStream(const char *fileName, int flags, int mode) {
	Open(fileName, flags, mode);
}

FileStream::~FileStream() {
	Close();
}

object FileStream::Read(object destination, object base) {
#ifdef PROC_OS_WIN
	return (object)_read(_handle, (void *)destination, BaseToBytes(base));
#else
	return (object)read(_handle, (void *)destination, BaseToBytes(base));
#endif
}

object FileStream::Write(object source, object base) {
#ifdef PROC_OS_WIN
	return (ptrdiff_t)_write(_handle, (const void *)source, BaseToBytes(base));
#else
	return (ptrdiff_t)write(_handle, source, BaseToBytes(base));
#endif
}

object FileStream::Read(Writer *destination) {
	return NULL;
}

object FileStream:: Write(Reader *source) {
	return NULL;
}

//######################################################################################################################
//#                                                   MemoryStream                                                     #
//######################################################################################################################

MemoryStream::MemoryStream(object pointer) {
}

MemoryStream::~MemoryStream() {
}

object MemoryStream::Read(object destination, object base) {
	return NULL;
}

object MemoryStream::Write(object source, object base) {
	return NULL;
}
