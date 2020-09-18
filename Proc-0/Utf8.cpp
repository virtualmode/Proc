// UTF-8 prelexical analyzer.

#include "Temp/Global.h"
#include "Utf8.h"

/*
	Set the next continuation byte.
	Необходимо учесть, что запись и чтение необходимо выполнять в двоичном режиме,
	чтобы операционная система не меняла EOL.
*/
void Utf8::set(char cb) {
	_writer->Write((ptrdiff_t)(&cb), 256);
}

/*
	Get the next byte. It returns UTF8_END if there are no more bytes.
*/
int Utf8::get() {
	if (_reader->Read((object)&_symbol, 256) <= 0)
		return UTF8_END;

	return _symbol & 0xFF;
}

/*
	Get the 6-bit payload of the next continuation byte.
	Return UTF8_ERROR if it is not a contination byte.
*/
int Utf8::cont() {
	int c = get();
	return ((c & 0xC0) == 0x80)
		? (c & 0x3F)
		: UTF8_ERROR;
}

/*
	Целое заранее содержит 4 байта (октета) для кодирования Unicode-символа.
	В зависимости от значения необходимо понять каким количеством байт кодируется этот символ в UTF-8.
*/
void Utf8::utf8_encode_next(int symbol) {
	int i, offset, count, temp;

	// 0xxxxxxx
	if (symbol <= 0x0000007F) { // Код символа до 127. Требуется 1 октет для кодирования.
		set((char)symbol);
		return;

	// 110xxxxx 10xxxxxx
	} else if (symbol <= 0x000007FF) { // 2047. Требуется 2 октета.
		count = 1;
		offset = 0xC0;

	// 1110xxxx 10xxxxxx 10xxxxxx
	} else if (symbol <= 0x0000FFFF) { // 65535. Требуется 3 октета.
		count = 2;
		offset = 0xE0;

	// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	} else if (symbol <= 0x0010FFFF) { // 1114111. Требуется 4 октета.
		count = 3;
		offset = 0xF0;
	}

	i = 0;
	set((symbol >> (6 * count)) + offset);
	i++;

	while (count > 0) {
		temp = symbol >> (6 * (count - 1));
		set(0x80 | (temp & 0x3f));
		i++;
		count--;
	}
}

/*
	Extract the next character.
	Returns: the character (between 0 and 1114111)
			or  UTF8_END   (the end)
			or  UTF8_ERROR (error)
*/
int Utf8::utf8_decode_next() {
	int c;  /* the first byte of the character */
	int c1; /* the first continuation character */
	int c2; /* the second continuation character */
	int c3; /* the third continuation character */
	int r;  /* the result */

	c = get();
/*
	Zero continuation (0 to 127)
	Считывается первый байт. Если первый бит == 0, то значение байта <= 127.
	Это значит, что символ относится к модифицированной ASCII-таблице и является
	латинским символом. Если значение байта > 127, то символ не ASCII.
*/
	if ((c & 0x80) == 0) {
		return c;
	}
/*
	One continuation (128 to 2047)
	Символ относится к двубайтовым, если первые 3 бита 0xE0 == 110 (0xC0).
*/
	if ((c & 0xE0) == 0xC0) {
		c1 = cont();
		if (c1 >= 0) {
			r = ((c & 0x1F) << 6) | c1;
			if (r >= 128) {
				return r;
			}
		}

/*
	Two continuations (2048 to 55295 and 57344 to 65535)
*/
	} else if ((c & 0xF0) == 0xE0) {
		c1 = cont();
		c2 = cont();
		if ((c1 | c2) >= 0) {
			r = ((c & 0x0F) << 12) | (c1 << 6) | c2;
			if (r >= 2048 && (r < 55296 || r > 57343)) {
				return r;
			}
		}

/*
	Three continuations (65536 to 1114111)
*/
	} else if ((c & 0xF8) == 0xF0) {
		c1 = cont();
		c2 = cont();
		c3 = cont();
		if ((c1 | c2 | c3) >= 0) {
			r = ((c & 0x07) << 18) | (c1 << 12) | (c2 << 6) | c3;
			if (r >= 65536 && r <= 1114111) {
				return r;
			}
		}
	}
	return UTF8_ERROR;
}

/*
	Initialize the UTF-8 decoder.
*/
Utf8::Utf8(Reader *reader) {
	_reader = reader;
}

/*
	Initialize the UTF-8 encoder.
*/
Utf8::Utf8(Writer *writer) {
	_writer = writer;
}

object Utf8::Read(Writer *destination) {
	return utf8_decode_next();
}

object Utf8::Read(object destination, object base) {
	return utf8_decode_next();
}

object Utf8::Write(Reader *source) {
	utf8_encode_next((*((int *)source)));
	return NULL;
}

object Utf8::Write(object source, object base) {
	utf8_encode_next((*((int *)source)));
	return NULL;
}
