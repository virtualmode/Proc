#pragma once

#ifndef WRITER_H
#define WRITER_H

#include "Temp/Dependency.h"

// Может получиться ситуация, когда два класса ссылаются друг на друга.
// При этом перекрёстные подключения заголовочных файлов не сработает,
// т.к. компилятор определяет и разрешает их бесконечное включение.
class Reader;

class Writer {
public:
	// Запись ЕДИНИЦЫ информации из другого потока в текущий поток?
	// Предположительно любая область памяти в Proc будет потоком-лентой.
	virtual object Write(Reader *source) = 0;

	virtual object Write(object source, object base) = 0; // TODO Временная заглушка для старых языков.
};

#endif // WRITER_H
