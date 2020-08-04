#pragma once

#ifndef STREAM_H
#define STREAM_H

/*
	Все данные представлены в виде ленты, каждая клетка которой может содержать несколько различных значений, как в машине
	Тьюринга. На разных архитектурах такие клетки могут быть основаны на разных физических принципах и могут кодировать
	различное количество состояний - оснований, а объём данных можно выразить через логарифм общего количества состояний
	по основанию архитектуры. К сожалению такое представление объёма возрастает экспоненциально, но полностью отвязывает
	код от оборудования.
	TODO Может есть смысл подумать о бесконечном рекурсивном представлении состояний.
	TODO А может stream - это поток не клеток, а состояний в чистом виде.
*/

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

/*
	Интерфейс потока состояний.
*/
/*class Stream {

public:

	virtual void Read(object destination, object base) = 0;

	virtual void Write(object source, object base) = 0;
};*/

class Reader {
public:
	virtual void Read(object destination, object base) = 0;
};

class Writer {
public:
	virtual void Write(object source, object base) = 0;
};

class Seeker {
public:
	// offset - количество состояний относительно начала потока.
	// Но есть проблема. Из-за использования логарифма, по сути мы можем перемещаться недалеко внутри одного машинного слова.
	// Надо придумать возможность длинного прыжка.
	virtual void Seek(object offset) = 0;
};

// Если использовать interface segregation, то может и не будет смысла в объединённом интерфейсе.
// Также есть идея объединений для безымянных композиций интерфейсов и др. типов.
class Stream: public Reader, public Writer, public Seeker {
};

/*
	Интерфейс потока символов.
*/
class CharReader {
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
};

class CharStream: public CharReader, public CharWriter, public CharSeeker {
};

/*
	Файловый поток.
*/
class FileStream: public Reader, public Writer {
public:

	FileStream(const char *fileName);

	// base - основание, количество состояний.
	// Пока что тип данных будет выглядеть как base[exponent][exponent][..].
	// destination должен содержать указатель на место, в которое будет записано states состояний.
	void Read(object destination, object base);
	void Write(object source, object base);
};

class MemoryStream: public Reader, public Writer {
	public:

	MemoryStream(object pointer);

	void Read(object destination, object base);
	void Write(object source, object base);
};

#endif
