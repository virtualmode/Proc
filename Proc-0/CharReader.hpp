#pragma once

#ifndef CHAR_READER_H
#define CHAR_READER_H

#include "Temp/Dependency.h"

#include "Char.hpp"

/*
	?. Потоки могут кодировать разнообразную информацию. Текст является основной её формой, с которой будут работать
	лексические анализаторы и генераторы, описанные интерфейсами ниже. На данный момент именование интерфейсов не
	подразумевает использование префиксов.
*/

// Интерфейс символьного анализатора.
// TODO Данный класс не должен наследоваться от символа Юникода.
// TODO Необходимо продумать композицию интерфейсов.
class CharReader {
public:

	bool EndOfStream;

	// Чтение следующего символа.
	virtual Char ReadChar() = 0;
};

#endif // CHAR_READER_H
