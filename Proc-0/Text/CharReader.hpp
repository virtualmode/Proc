#pragma once

#ifndef CHAR_READER_HPP
#define CHAR_READER_HPP

#include "Temp/Dependency.h"

/*
	?. Потоки могут кодировать разнообразную информацию. Текст является основной её формой, с которой будут работать
	лексические анализаторы и генераторы, описанные интерфейсами ниже. На данный момент именование интерфейсов не
	подразумевает использование префиксов.
*/

// Интерфейс символьного анализатора.
class CharReader {
public:

	bool EndOfStream;

	// Чтение следующего символа.
	virtual int ReadChar() = 0;
};

#endif // CHAR_READER_HPP
