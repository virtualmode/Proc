#pragma once

#ifndef UTF8_HPP
#define UTF8_HPP

#include "CharToken.hpp"
#include "Reader.hpp"
#include "Writer.hpp"


/*
	3. Исходные коды программ представлены в текстовом виде. Наиболее распространенным сейчас является формат UTF-8.
	Компилятор должен как минимум его поддерживать, чтобы обеспечивать чтение и запись текстовых данных.
*/

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

class Utf8: public CharToken {
private:

	char _symbol; // Очередной прочитанный символ.
	Reader *_reader;
	Writer *_writer;

	// Предыдущий символ последовательности перевода на новую строку.
	Char _eolSequence;

	// Статический конструктор.
	/*friend class CharTokenStatic;
	struct CharTokenStatic {
		CharTokenStatic() {
		}
	} _constructor;*/

	// Set the next continuation byte.
	// Необходимо учесть, что запись и чтение необходимо выполнять в двоичном режиме,
	// чтобы операционная система не меняла EOL.
	void set(char cb) {
		_writer->Write((ptrdiff_t)(&cb), 256);
	}

	// Get the next byte. It returns UTF8_END if there are no more bytes.
	int get() {
		if (_reader->Read((object)&_symbol, 256) <= 0)
			return UTF8_END;

		return _symbol & 0xFF;
	}

	// Get the 6-bit payload of the next continuation byte.
	// @return UTF8_ERROR if it is not a contination byte.
	int cont() {
		int c = get();
		return ((c & 0xC0) == 0x80) ? (c & 0x3F) : UTF8_ERROR;
	}

	// Целое заранее содержит 4 байта (октета) для кодирования Unicode-символа.
	// В зависимости от значения необходимо понять каким количеством байт кодируется этот символ в UTF-8.
	void utf8_encode_next(int symbol) {
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

	// Extract the next character.
	// @return The character (between 0 and 1114111) or UTF8_END or UTF8_ERROR.
	int utf8_decode_next() {
		int c;  // The first byte of the character.
		int c1; // The first continuation character.
		int c2; // The second continuation character.
		int c3; // The third continuation character.
		int r;  // The result.

		c = get();

		// Zero continuation (0 to 127).
		// Считывается первый байт. Если первый бит == 0, то значение байта <= 127.
		// Это значит, что символ относится к модифицированной ASCII-таблице и является
		// латинским символом. Если значение байта > 127, то символ не ASCII.
		if ((c & 0x80) == 0) {
			return c;
		}

		// One continuation (128 to 2047).
		// Символ относится к двубайтовым, если первые 3 бита 0xE0 == 110 (0xC0).
		if ((c & 0xE0) == 0xC0) {
			c1 = cont();
			if (c1 >= 0) {
				r = ((c & 0x1F) << 6) | c1;
				if (r >= 128) {
					return r;
				}
			}

		// Two continuations (2048 to 55295 and 57344 to 65535).
		} else if ((c & 0xF0) == 0xE0) {
			c1 = cont();
			c2 = cont();
			if ((c1 | c2) >= 0) {
				r = ((c & 0x0F) << 12) | (c1 << 6) | c2;
				if (r >= 2048 && (r < 55296 || r > 57343)) {
					return r;
				}
			}

		// Three continuations (65536 to 1114111).
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

	// Обновление лексемы в соответствии с текущим кодом символа.
	inline void UpdateType() {
		if (Value <= (int)Char::Delete) {
			Type = (Char)Value;
		} else {
			// TODO Реализовать определение других символов при необходимости.
			Type = Char::Unknown;
		}
	}

	// Состояние новой строки.
	inline void NextLine() {
		Line++;
		Character = 0;
		Column = 0;
	}

	// Вычисление курсора, номера символа в строке, колонки, номера строки.
	void UpdateCounters() {
		Position++;
		Character++;
		Column++; // TODO Необходимо учитывать, что символы типа табуляции занимают несколько позиций.
		if (IsEndOfLine()) {
			if (_eolSequence != Char::CarriageReturn || Type != Char::LineFeed)
				 NextLine();

			_eolSequence = Type;
		} else {
			if (_eolSequence != Char::Unknown)
				NextLine();

			_eolSequence = Char::Unknown;
		}
	}

	Utf8() {
		_eolSequence = Char::Unknown;
		Type = Char::Unknown;
		EndOfStream = false;
		Position = 0;
		Character = 0;
		Column = 0;
		Line = 0;
	}

public:

	int Value; // Код текущего символа.

	// Основной конструктор.
	// TODO Если будут введены отдельные реализации интерфейсов, необходимо рассмотреть возможность языка
	// TODO комбинировать несколько интерфейсов и не писать каждый раз отдельные конструкторы.
	// @param reader Входящий поток состояний.
	// @param writer Исходящий поток состояний.
	Utf8(Reader *reader, Writer *writer): Utf8() {
		_reader = reader;
		_writer = writer;
	}

	// Здесь еще возможны варианты с Seeker'ом, но очень затратно это описывать вручную и несколькими классами.
	// Теоретически компилятор может создавать реализацию любого интерфейса отдельно от общей реализации.
	// Необходимо дописать новый синтаксис для конструктора, который явно указывает используемый интерфейс(ы).
	// Конструктор для Proc будет содержать в конструкторе интерфейс SourceToken.UnicodeReader и реализовывать часть класса.
	Utf8(Reader *reader): Utf8() {
		_reader = reader;
	}

	// Initialize the UTF-8 encoder.
	// Конструктор для Proc будет содержать в конструкторе интерфейс SourceToken.UnicodeWriter и реализовывать часть класса.
	Utf8(Writer *writer): Utf8() {
		_writer = writer;
	}

	// Деструкторы аналогично можно писать для разных реализаций.
	virtual ~Utf8() {
	}

	virtual int ReadChar() {
		Value = utf8_decode_next();
		UpdateType();
		UpdateCounters();
		return Value;
	}

	virtual void WriteChar(int character) {
		utf8_encode_next(character);
		Value = character;
		UpdateType();
		UpdateCounters();
		Position++;
	}

	virtual bool SeekChar(long offset) {
		// TODO Необходимо реализовать переход машины состояний вперед и назад на несколько шагов.
		// TODO Также надо подумать о возможности в принципе перехода назад.
		return false;
	}

	// Является ли текущий символ арабской десятичной цифрой юникода.
	virtual bool IsDecimalDigit() {
		return Type >= Char::Digit0 && Type <= Char::Digit9;
	}

	// Является ли текущий символ строчной латинской буквой.
	virtual bool IsSmallLatinLetter() {
		return Type >= Char::SmallLetterA && Type <= Char::SmallLetterZ;
	}

	// Является ли текущий символ заглавной латинской буквой.
	virtual bool IsCapitalLatinLetter() {
		return Type >= Char::CapitalLetterA && Type <= Char::CapitalLetterZ;
	}

	// Является ли текущий символ латинской буквой.
	virtual bool IsLatinLetter() {
		return IsSmallLatinLetter() || IsCapitalLatinLetter();
	}

	// Символ является отступом.
	// @deprecated Достаточно специфическая реализация для использования в таком виде.
	virtual bool IsWhitespace() {
		return Type == Char::HorizontalTabulation ||
			Type == Char::Space;
	}

	// Символ относится к группе допустимых разделителей, используемых в компиляторе.
	// @deprecated Достаточно специфическая реализация для использования в таком виде.
	virtual bool IsDelimiter() {
		return Type >= Char::Space && Type <= Char::Slash ||
			Type >= Char::Colon && Type <= Char::CommercialAt ||
			Type >= Char::LeftSquareBracket && Type <= Char::GraveAccent ||
			Type >= Char::LeftCurlyBracket && Type <= Char::Delete;
	}

	// Символ является разделителем строк или входит в последовательность разделения.
	// @deprecated Название не совсем соответствует действительности.
	virtual bool IsEndOfLine() {
		return Type == Char::CarriageReturn ||
			Type == Char::LineFeed ||
			Type == Char::NextLine ||
			Type == Char::LineSeparator ||
			Type == Char::ParagraphSeparator ||
			Type == Char::VerticalTabulation;
	}
};

#endif // UTF8_HPP
