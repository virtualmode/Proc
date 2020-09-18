/*
	Версия не является окончательной.

	2. Универсальная машина не может работать без входных и выходных данных. Мне еще не известно, как эти данные должны выглядеть и
	передаваться. Поэтому необходимо ввести некоторую абстракцию, класс или набор классов для работы с потоками, известными как ленты.
	Каждая клетка ленты может содержать несколько различных значений, как в машине Тьюринга. На разных архитектурах такие клетки могут
	быть основаны на разных физических принципах и могут кодировать различное количество состояний - оснований, а объём данных можно
	выразить через логарифм общего количества состояний по основанию архитектуры. Такое представление объёма, к сожалению, возрастает
	экспоненциально, но полностью отвязывает код от оборудования.

	TODO Подумать о бесконечном рекурсивном представлении состояний.
	TODO Подумать о варианте того, что Stream - это поток не клеток, а состояний в чистом виде.
	TODO Есть рабочий вариант клеток с переменным количеством состояний.
*/

#pragma once

#ifndef STREAM_H
#define STREAM_H

#include "Temp/Type.h"

/*
	IStream - общий поток с возможностью чтения/записи сырых данных.
		ITextStream - поток для работы именно с символами. Лексический анализатор по сути работает с текстом.
			Utf8Stream - основной текстовый поток, который может использоваться для чтения текста.
			AsciiStream и UtfNStream - опциональные, т.к. фактически смысла не имеют, скорее так, в виде расширения.

		ILexicalAnalyzer(Stream) - вообще любые данные, которые преобразуются из одного состояния в другое - похожи.
		Сами процессы похожи. Их можно назвать фильтрами, лексическими анализаторами или даже анализатор можно
		представить как аудио процессор или как обычный поток, который считывает другой поток (текстовый например)
		и меняет свое состояние, ищет лексемы.

		Можно придумать что-то типа локального namespace'а для наследуемых типов:
		Stream - интерфейс (без I, как в других языках).
		Stream.File - файловый поток (если использовать 'use', то без 'Stream.' можно определять File).
		А если есть некий абстрактный класс (интерфейс), то введя точку, можно посмотреть дочерние классы.
		Кажется достаточно удобным, учтывая что мы еще в IntelliSense увидим родительские и дочерние классы
		в алфавитном порядке и порядке зависимости плюс минус.
*/

class Writer;

/*
	Интерфейс потока состояний.
	Под потоком будет пониматься лента, которая также будет являться базовым типом данных.
	Например char 1 байт - это поток из одного элемента из 256 состояний (но может быть представлен и в другом виде).
	Содержимое, например IEEE 754 или целочисленное представление будет вынесено на другой уровень.
*/
class Reader {
public:
	// Считывание ЕДИНИЦЫ информации из текущего потока в другой поток?
	virtual object Read(Writer *destination) = 0;

	virtual object Read(object destination, object base) = 0; // TODO Временная заглушка для старых языков.
};

class Writer {
public:
	// Запись ЕДИНИЦЫ информации из другого потока в текущий поток?
	// Предположительно любая область памяти в Proc будет потоком-лентой.
	virtual object Write(Reader *source) = 0;

	virtual object Write(object source, object base) = 0; // TODO Временная заглушка для старых языков.
};

class Seeker {
public:
	// offset - количество состояний относительно начала потока.
	// Но есть проблема. Из-за использования логарифма, по сути мы можем перемещаться недалеко внутри одного машинного слова.
	// Надо придумать возможность длинного прыжка.
	virtual object Seek(object offset) = 0;
};

// Если использовать interface segregation, то может и не будет смысла в объединённом интерфейсе.
// Также есть идея объединений для безымянных композиций интерфейсов и др. типов.
//class Stream: public Reader, public Writer, public Seeker {
//};

/*
	Интерфейс потока символов.
*/
/*class CharReader {
public:
	virtual void ReadChar(Writer *destination) = 0;
};

class CharWriter {
public:
	virtual void WriteChar(Reader *source) = 0;
};

class CharSeeker {
public:
	// offset - это количество символов относительно начала потока.
	virtual void Seek(object offset) = 0;
};*/

//class CharStream: public CharReader, public CharWriter, public CharSeeker {
//};

/*
	Файловый поток.
*/
class FileStream: public Reader, public Writer {
private:

	int _handle; //!< Low-Level I/O file handle.

#ifdef PROC_OS_WIN
#else
#endif

public:

	bool Open(const char *fileName, int flags = O_BINARY | O_RDONLY | O_BINARY, int mode = _S_IREAD);
	bool Close();

	FileStream(const char *fileName, int flags = O_BINARY | O_RDONLY | O_BINARY, int mode = _S_IREAD);
	virtual ~FileStream();

	// base - основание, количество состояний. В оригинале - количество байт.
	// Пока что тип данных будет выглядеть как base[exponent][exponent][..].
	// destination должен содержать указатель на место, в которое будет записано states состояний.
	virtual object Read(object destination, object base);
	virtual object Write(object source, object base);

	virtual object Read(Writer *destination);
	virtual object Write(Reader *source);
};

class MemoryStream: public Reader, public Writer {
	public:

	MemoryStream(object pointer);
	virtual ~MemoryStream();

	virtual object Read(object destination, object base);
	virtual object Write(object source, object base);
};

#endif
