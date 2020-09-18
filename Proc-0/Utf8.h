/*
	Utf8

	3. Исходные коды программ представлены в текстовом виде. Наиболее распространенным сейчас является формат UTF-8.
	Компилятор должен как минимум его поддерживать, чтобы обеспечивать чтение и запись текстовых данных.
*/

#pragma once

#ifndef UTF8_H
#define UTF8_H

#include "Stream.h"

/*
    Very Strict UTF-8 Decoder

    UTF-8 is a multibyte character encoding of Unicode. A character can be
    represented by 1-4 bytes. The bit pattern of the first byte indicates the
    number of continuation bytes.

    Most UTF-8 decoders tend to be lenient, attempting to recover as much
    information as possible, even from badly encoded input. This UTF-8
    decoder is not lenient. It will reject input which does not include
    proper continuation bytes. It will reject aliases (or suboptimal
    codings). It will reject surrogates. (Surrogate encoding should only be
    used with UTF-16.)

    Code     Contination Minimum Maximum
    0xxxxxxx           0       0     127
    10xxxxxx       error
    110xxxxx           1     128    2047
    1110xxxx           2    2048   65535 excluding 55296 - 57343
    11110xxx           3   65536 1114111
    11111xxx       error
*/

#define UTF8_END   -1
#define UTF8_ERROR -2

class Utf8: public Reader, public Writer {
public:

private:

	char _symbol;
	Reader *_reader;
	Writer *_writer;

	void set(char cb);
	int get();
	int cont();

	void utf8_encode_next(int symbol);
	int utf8_decode_next();

public:

	// Здесь еще возможны варианты с Seeker'ом, но очень затратно это описывать вручную и несколькими классами.
	// Теоретически компилятор может создавать реализацию любого интерфейса отдельно от всех реализаций.
	// Необходимо дописать новый синтаксис для конструктора, который явно указывает используемый интерфейс(ы).
	Utf8(Reader *reader);
	Utf8(Writer *writer);

	virtual object Read(Writer *destination);
	virtual object Read(object destination, object base); // TODO Временная заглушка для старых языков.

	virtual object Write(Reader *source);
	virtual object Write(object source, object base); // TODO Временная заглушка для старых языков.

};

#endif
