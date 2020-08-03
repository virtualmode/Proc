// Внешние заголовочные файлы:
#include <stdio.h>
#include <stdlib.h> // malloc.
#include <limits.h>
#include <string.h> // memset.

// Внутренние заголовочные файлы:
#include "Type.h"
#include "Stream.h"
#include "Utf8.h"
#include "LexicalAnalyzer.h"

// Используемые прототипы Оберон-0:
extern "C" {
	void OssInit(const char *fileName, long pos); // Файл с исходным кодом и его начальная позиция.
	void Oss(const char *fileName); // Файл для записи результатов лексического анализатора.
	void Compile(const char *fileName);
}
