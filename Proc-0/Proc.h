// Внешние заголовочные файлы:
#include <stdio.h>
#include <limits.h>
#include <malloc.h> // malloc.
#include <string.h> // memset.

// Внутренние заголовочные файлы:
#include "Type.h"
#include "Stream.h"
#include "LexicalAnalyzer.h"

// Используемые прототипы Оберон-0:
void OssInit(const char *fileName, long pos); // Файл с исходным кодом и его начальная позиция.
void Oss(const char *fileName); // Файл для записи результатов лексического анализатора.
void Compile(const char *fileName);
