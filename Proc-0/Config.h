#pragma once

#ifndef CONFIG_H
#define CONFIG_H

/*
	Software versioning (a.b.c.d):
	a - основная версия (major).
	b - второстепенная (minor).
	c - стадия разработки (service release):
		0 - alpha,
		1 - beta,
		2 - release candidate,
		3 - (final) release,
		4 - для коммерческого распространения (commercial distribution) и т.д. на усмотрение.
	d - патч (patch). Синоним: билд (build).
*/
#define PROC_VERSION_STR "0.0-a" // Версия 1.0.3.1 - это финальный релиз версии 1.0 с исправленной ошибкой. Текстовую форму можно использовать любую, например 1.0rc1.
#define PROC_VERSION 0x00000000 // HEX. Is (major << 24) + (minor << 16) + (service << 8) + patch. Пример: 0x01020304 = 1.2.3.4.
#define PROC_VERSION_CHECK(major, minor, service, patch) ((major<<24)|(minor<<16)|(service<<8)|(patch)) // Can be used like #if (PROC_VERSION >= PROC_VERSION_CHECK(3, 1, 0, 0)).

// IO configuration:
#define PROC_CAST_BUFFER_SIZE 64
#define PROC_STREAM_BUFFER_SIZE 1024 // Размер буфера для считывания данных с потока.


/*
	System resource manipulations.
*/
#define PROC_SAFE_DELETE(pointer) { if (pointer) { delete (pointer); (pointer) = 0; } }
#define PROC_SAFE_DELETE_ARRAY(pointer) { if (pointer) { delete[] (pointer); (pointer) = 0; } }
#define PROC_SAFE_FREE(pointer) { if (pointer) { free(pointer); (pointer) = 0; } }
#define PROC_SAFE_DISPOSE(pointer) { if (pointer) { (pointer)->Dispose(); (pointer) = 0; } }
#define PROC_SAFE_RELEASE(pointer) { if (pointer) { (pointer)->Release(); (pointer) = 0; } }

#endif
