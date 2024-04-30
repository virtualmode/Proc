/*
	Proc(ess(or))
*/

#include <stdio.h>

// Тип литеры (лексемы), представляющий значение символа, а не его числовое представление в конкретной кодировке.
// Все значения строго отсортированы и сгруппированы в соответствии с интервалами кодировок без учёта самих кодов.
// Такая организация позволяет оптимизировать работу с некоторыми кодировками и сохранить при этом универсальность.
enum CharType {
	//#region ASCII

	// ASCII управляющие символы 0x0000-0x001f.
	Null, // Пустой символ ^@ (NUL).
	StartOfHeading, // Начало заголовка ^A (SOH).
	StartOfText, // Начало текста ^B (STX).
	EndOfText, // Сигнал прерывания в терминале ^C (ETX).
	EndOfTransmission, // Конец вводимых данных ^D (EOT).
	Enquiry, // Запрос ^E (ENQ).
	Acknowledge, // Подтверждение ^F (ACK).
	Bell, // Звуковой сигнал ^G, \a (BEL).
	Backspace, // Возврат на один шаг ^H, \b (BS).
	HorizontalTabulation, // Горизонтальная табуляция ^I, \t (HT, TAB).
	LineFeed, // Подача строки, конец строки, новая строка ^J, \n (LF, EOL, NL).
	VerticalTabulation, // Вертикальная табуляция ^K, \v (VT).
	FormFeed, // Прогон страницы ^L, \f (FF).
	CarriageReturn, // Возврат каретки ^M, \r (CR).
	ShiftOut, // Режим национальных символов ^N (SO).
	ShiftIn, // Режим ASCII ^O (SI).
	DataLinkEscape, // Экранирование управляющих символов в обычный текст ^P (DLE).
	DeviceControl1, // Первый код управления устройством ^Q (DC1).
	DeviceControl2, // Второй код управления устройством ^R (DC2).
	DeviceControl3, // Третий код управления устройством ^S (DC3).
	DeviceControl4, // Четвёртый код управления устройством ^T (DC4).
	NegativeAcknowledge, // Отрицательное подтверждение ^U (NAK).
	SynchronousIdle, // Пустой символ для синхронного режима передачи ^V (SYN).
	EndOfTransmissionBlock, // Конец блока передаваемых данных ^W (ETB).
	Cancel, // Отмена предыдущих данных строки ^X (CAN).
	EndOfMedium, // Конец носителя ^Y (EM).
	SubstituteCharacter, // Символ замены потерянного во время передачи символа ^Z (SUB).
	Escape, // Альтернативный регистр для следующих символов, считающихся уже не ASCII ^[, \e (ESC).
	FileSeparator, // Разделитель файлов ^\ (FS).
	GroupSeparator, // Разделитель групп ^] (GS).
	RecordSeparator, // Разделитель записей ^^ (RS).
	UnitSeparator, // Разделитель полей ^_ (US).

	// ASCII 0x0020-0x002f.
	Space, // Пробел (SP).
	ExclamationMark, // !
	QuotationMark, // "
	NumberSign, // #
	DollarSign, // $
	PercentSign, // %
	Ampersand, // &
	Apostrophe, // '
	LeftParenthesis, // (
	RightParenthesis, // )
	Asterisk, // *
	PlusSign, // +
	Comma, // ,
	HyphenMinus, // Hyphen -
	FullStop, // .
	Slash, // Solidus /

	// ASCII индо-арабские десятичные цифры 0x0030-0x0039.
	Digit0,
	Digit1,
	Digit2,
	Digit3,
	Digit4,
	Digit5,
	Digit6,
	Digit7,
	Digit8,
	Digit9,

	// ASCII 0x003a-0x0040.
	Colon, // :
	Semicolon, // ;
	LessThanSign, // <
	EqualsSign, // =
	GreaterThanSign, // >
	QuestionMark, // ?
	CommercialAt, // @

	// ASCII латинские заглавные буквы 0x0041-0x005a.
	CapitalLetterA,
	CapitalLetterB,
	CapitalLetterC,
	CapitalLetterD,
	CapitalLetterE,
	CapitalLetterF,
	CapitalLetterG,
	CapitalLetterH,
	CapitalLetterI,
	CapitalLetterJ,
	CapitalLetterK,
	CapitalLetterL,
	CapitalLetterM,
	CapitalLetterN,
	CapitalLetterO,
	CapitalLetterP,
	CapitalLetterQ,
	CapitalLetterR,
	CapitalLetterS,
	CapitalLetterT,
	CapitalLetterU,
	CapitalLetterV,
	CapitalLetterW,
	CapitalLetterX,
	CapitalLetterY,
	CapitalLetterZ,

	// ASCII 0x005b-0x0060.
	LeftSquareBracket, // [
	Backslash, // \ :)
	RightSquareBracket, // ]
	CircumflexAccent, // ^
	Underline, // _
	GraveAccent, // `

	// ASCII латинские строчные буквы 0x0061-0x007a.
	SmallLetterA,
	SmallLetterB,
	SmallLetterC,
	SmallLetterD,
	SmallLetterE,
	SmallLetterF,
	SmallLetterG,
	SmallLetterH,
	SmallLetterI,
	SmallLetterJ,
	SmallLetterK,
	SmallLetterL,
	SmallLetterM,
	SmallLetterN,
	SmallLetterO,
	SmallLetterP,
	SmallLetterQ,
	SmallLetterR,
	SmallLetterS,
	SmallLetterT,
	SmallLetterU,
	SmallLetterV,
	SmallLetterW,
	SmallLetterX,
	SmallLetterY,
	SmallLetterZ,

	// ASCII 0x007b-0x007f.
	LeftCurlyBracket, // {
	VerticalLine, // |
	RightCurlyBracket, // }
	Tilde, // ~
	Delete, // Управляющий символ удаления ^? (DEL).

	//#endregion ASCII

	//#region Proc

	// Область других символов.
	Unknown, // Символ неизвестного назначения.
	EndOfStream, // Признак окончания потока, не относящийся к какому-либо символу.

	//#endregion Proc

	//#region Unicode

	NextLine, // Переход на следующую строку 0x0085 (NEL).
	NoBreakSpace, // Неразрывный пробел 0x00a0 (NBSP).
	NonBreakingHyphen, // Неразрывный дефис 0x2011 (NBHYPHEN).
	LineSeparator, // Разделитель строк 0x2028 (LS).
	ParagraphSeparator, // Разделитель абзацев 0x2029 (PS).

	//#endregion Unicode
};

// Интерфейс работы с токеном символа определённой кодировки.
struct Char {
	// Поток состояний со значением кода символа в реализуемой кодировке.
	// Код символа фиксированного размера для внутреннего использования.
	int Value;

	// Тип токена.
	enum CharType Type;
};

// Интерфейс потока символов для работы с текстом.
// TODO CharReader и CharWriter должны использоваться независимо.
// TODO Необходимо добавить в язык возможность композиции интерфейсов.
// TODO А пока придётся наследовать с другими необходимыми интерфейсами.
// TODO После реализации композиции данный класс не будет иметь смысла.
//[Obsolete("Implement interface composition instead. Allow fields usage?")]
struct CharStream {
	struct Char Char; // TODO После реализации ООП необходимо заменить композицию на наследование.
	long Position;
	long Character;
	long Column;
	long Line;
};

struct FileStream {
	FILE *_file;
};

int FileStreamOpen(struct FileStream *fileStream, const char *fileName) {
	fileStream->_file = fopen(fileName, "rb");
	return fileStream->_file;
}

int FileStreamClose(struct FileStream *fileStream)
{
	return fclose(fileStream->_file);
}

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

	Code     Continuation Minimum Maximum
	0xxxxxxx            0       0     127
	10xxxxxx        error
	110xxxxx            1     128    2047
	1110xxxx            2    2048   65535 excluding 55296 - 57343
	11110xxx            3   65536 1114111
	11111xxx        error
*/
const int UTF8_BUFFER_SIZE = 4;

const int UTF8_END = -1;
const int UTF8_ERROR = -2;

const int UTF8_SMALL_CYRILLIC_LETTER_FROM = 0x0430;
const int UTF8_SMALL_CYRILLIC_LETTER_TO = 0x044F;
const int UTF8_CAPITAL_CYRILLIC_LETTER_FROM = 0x0410;
const int UTF8_CAPITAL_CYRILLIC_LETTER_TO = 0x042F;

struct Utf8 {
	struct CharStream CharStream; // TODO После реализации ООП необходимо заменить композицию на наследование.
	struct FileStream *FileStream;
	//char _symbol; // Очередной прочитанный байт.
	//char *_buffer;

	// Предыдущий символ последовательности перевода на новую строку.
	//enum CharType _eolSequence;
};

void Utf8Init(struct Utf8 *utf8, struct FileStream *fileStream) {
	utf8->CharStream.Position = 0;
	utf8->FileStream = fileStream;
	//utf8->_buffer = p;
	//the_length = length;
	utf8->CharStream.Character = 0;
	//the_byte = 0;
}

int get(struct Utf8 *utf8) {
	int c;
	if (feof(utf8->FileStream->_file)) {
		return UTF8_END;
	}
	//c = utf8->_buffer[utf8->CharStream.Position] & 0xFF;
	c = fgetc(utf8->FileStream->_file) & 0xFF;
	utf8->CharStream.Position += 1;
	return c;
}

static int cont(struct Utf8 *utf8) {
	int c = get(utf8);
	return ((c & 0xC0) == 0x80)
		? (c & 0x3F)
		: UTF8_ERROR;
}

int Utf8DecodeNext(struct Utf8 *utf8) {
	int c;  /* the first byte of the character */
	int c1; /* the first continuation character */
	int c2; /* the second continuation character */
	int c3; /* the third continuation character */
	int r;  /* the result */

	//if (utf8->CharStream.Position >= the_length) {
	//	return utf8->CharStream.Position == the_length ? UTF8_END : UTF8_ERROR;
	//}
	if (feof(utf8->FileStream->_file)) {
		return UTF8_END;
	}

	//the_byte = utf8->CharStream.Position;
	utf8->CharStream.Character += 1;
	c = get(utf8);
	// Zero continuation (0 to 127)
	if ((c & 0x80) == 0) {
		return c;
	}

	// One continuation (128 to 2047)
	if ((c & 0xE0) == 0xC0) {
		c1 = cont(utf8);
		if (c1 >= 0) {
			r = ((c & 0x1F) << 6) | c1;
			if (r >= 128) {
				return r;
			}
		}

	// Two continuations (2048 to 55295 and 57344 to 65535)
	} else if ((c & 0xF0) == 0xE0) {
		c1 = cont(utf8);
		c2 = cont(utf8);
		if ((c1 | c2) >= 0) {
			r = ((c & 0x0F) << 12) | (c1 << 6) | c2;
			if (r >= 2048 && (r < 55296 || r > 57343)) {
				return r;
			}
		}

	// Three continuations (65536 to 1114111)
	} else if ((c & 0xF8) == 0xF0) {
		c1 = cont(utf8);
		c2 = cont(utf8);
		c3 = cont(utf8);
		if ((c1 | c2 | c3) >= 0) {
			r = ((c & 0x07) << 18) | (c1 << 12) | (c2 << 6) | c3;
			if (r >= 65536 && r <= 1114111) {
				return r;
			}
		}
	}
	return UTF8_ERROR;
}

// Процессор.
struct Proc {
	struct FileStream FileStream;
	struct Utf8 Utf8;
};

int main(int argc, char **argv)
{
	// Побитовый вывод для отладки.
	char byte = 255;
	for (int i = 0; i < 8; i++)
	{
		printf("%u", (byte >> i) & 0x1);
	}
	printf("\n");
	//  255 = 11111111
	//  129 = 10000001
	//  128 = 00000001
	//  127 = 11111110
	//    1 = 10000000
	//    0 = 00000000
	//   -1 = 11111111
	// -127 = 10000001
	// -128 = 00000001
	// -129 = 11111110

	// Компиляция исходников.
	struct Proc state;
	FileStreamOpen(&state.FileStream, "Example.proc");
	Utf8Init(&state.Utf8, &state.FileStream);
	int symbol = 0;
	while ((symbol = Utf8DecodeNext(&state.Utf8)) >= 0) {
		if (symbol > 255)
			printf("[%u]", symbol);
		else
			printf("%c", symbol);
	}
	//Compile(&state, "Proc1.proc");
	FileStreamClose(&state.FileStream);
	return 0;
}
