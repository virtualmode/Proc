/*
	Proc(ess(or))-0

	Версия не является окончательной и необходима в учебных целях.

	0. Виртуальный процессор создаётся с целью изучения теории автоматов и вычислимости.
	На момент начала работы предполагалось создать простую универсальную машину, способную
	интерпретировать и компилировать код без использования сторонних разработок.
	Базовые термины и принципы, используемые здесь, рекомендуется изучить в книгах:
		Charles Petzold - The Annotated Turing: A Guided Tour Through Alan Turing's Historic Paper on Computability and the Turing Machine
		Niklaus Wirth - Compiler Construction

	1. Автомату нужен базовый язык или набор языков, которые он будет понимать, и которых будет достаточно для расширения самого себя.
	Чтобы написать его, потребуется существующий компилятор, например для C/C++. Поэтому Proc-0 является временной версией процессора с
	минимальным набором возможностей, необходимых только для его запуска и сборки первой версии самого себя без зависимостей.
	Также решено писать процессор одним листингом, упростив переносимость и подчеркнув необходимость использовать только минимум кода,
	абстрагироваться от файловой системы и прочих сервисов. Машина может только выполняться и выполнять другие машины, а код для работы
	операционной системы, оборудованием и прочее должны быть вынесены за пределы компилируемого ядра вычислителя.
*/


//######################################################################################################################
//#                                                     Зависимости                                                    #
//######################################################################################################################

// Файл предварительно скомпилированных заголовков:
#include "Temp/Global.h"


// Переменная, указывающая на объект и основание должны быть размерности указателя для архитектуры,
// или безразмерного (целого). Указатель очень для этого подходит. IntPtr, IntObj, pointer, object, base.
// Базовый "безразмерный" тип для всех объектов, чисел, структур, enum'ов и прочей фигни.
// Этот тип будет реализовывать простейшие операции над любым объектом, скорее всего
// просто адресация и счёт. В данном языке это может быть основание - количество состояний информации.
//#define object char*
#define object ptrdiff_t

#define bool int
#define false 0
#define true 1

// Unsigned integer types:
typedef unsigned char u8; //!< 1 byte from 0 to 255 (char, bool).
typedef unsigned short u16; //!< 2 bytes from 0 to 65,535 (short).
typedef unsigned int u32; //!< 4 bytes from 0 to 4,294,967,295 (int, long).
typedef unsigned long long u64; //!< 8 bytes from 0 to 18,446,744,073,709,551,615 (long long).
//typedef u64 ul; //!< Largest supported unsigned type.

// Signed integer types:
typedef signed char s8; //!< 1 bytes from –128 to 127.
typedef signed short s16; //!< 2 bytes from –32,768 to 32,767.
typedef signed int s32; //!< 4 bytes from –2,147,483,648 to 2,147,483,647.
typedef signed long long s64; //!< 8 bytes from –9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
//typedef s64 sl; //!< Largest supported signed type.

// Floating point types:
typedef float f32;
typedef double f64;
typedef long double f80; // Rare.

union type {
	bool type::bool_t;
	u8 type::u8;
	u16 type::u16;
	u32 type::u32;
	u64 type::u64;
	s8 type::s8;
	s16 type::s16;
	s32 type::s32;
	s64 type::s64;
	f32 type::f32;
	f64 type::f64;
	f80 type::f80;
	::size_t type::size_t;
	::ptrdiff_t type::ptrdiff_t;
};


//######################################################################################################################
//#                                                     Streams                                                        #
//#   2. Универсальная машина не может работать без входных и выходных данных. Мне еще не известно, как эти данные     #
//#   должны выглядеть и передаваться. Поэтому необходимо ввести некоторую абстракцию, класс или набор классов для     #
//#   работы с потоками, известными как ленты. Каждая клетка ленты может содержать несколько различных значений, как   #
//#   в машине Тьюринга. На разных архитектурах такие клетки могут быть основаны на разных физических принципах и      #
//#   могут кодировать различное количество состояний - оснований, а объём данных можно выразить через логарифм        #
//#   общего количества состояний по основанию архитектуры. Такое представление объёма, к сожалению, возрастает        #
//#   экспоненциально, но полностью отвязывает код от оборудования.                                                    #
//#                                                                                                                    #
//######################################################################################################################

/*
	TODO Подумать о бесконечном рекурсивном представлении состояний.
	TODO Подумать о варианте того, что Stream - это поток не клеток, а состояний в чистом виде.
	TODO Есть рабочий вариант клеток с переменным количеством состояний.

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

// Compiler is not support state logic.
int BaseToBytes(object base) {
	return (int)log2(base) / 8;
}

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

	/*
		Запись: O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE
		Чтение: O_BINARY | O_RDONLY, _S_IREAD
	*/
	bool Open(const char *fileName, int flags = O_BINARY | O_RDONLY | O_BINARY, int mode = _S_IREAD) {
#ifdef PROC_OS_WIN
		if ((_handle = _open(fileName, flags, mode)) <= 0) { // Открытие файла с использованием ANSI пути не удалось:
			wchar_t wFileName[512]; // Буфер для преобразования из UTF-8 в двубайтную строку.
			if (MultiByteToWideChar(CP_UTF8, NULL, fileName, -1, wFileName, 512) <= 0 || (_handle = _wopen(wFileName, flags, mode)) <= 0)
				return false;
		}
#else
		if ((_handle = open(path, flags, mode)) <= 0)
			return false;
#endif
		return true;
	}

	bool Close() {
		int result = 0;
		if (_handle > 0)
#ifdef PROC_OS_WIN
			result = _close(_handle);
#else
			result = close(_handle);
#endif
		_handle = 0;
		return result == 0;
	}

	FileStream(const char *fileName, int flags = O_BINARY | O_RDONLY | O_BINARY, int mode = _S_IREAD) {
		Open(fileName, flags, mode);
	}

	virtual ~FileStream() {
		Close();
	}

	// base - основание, количество состояний. В оригинале - количество байт.
	// Пока что тип данных будет выглядеть как base[exponent][exponent][..].
	// destination должен содержать указатель на место, в которое будет записано states состояний.
	virtual object Read(object destination, object base) {
#ifdef PROC_OS_WIN
		return (object)_read(_handle, (void *)destination, BaseToBytes(base));
#else
		return (object)read(_handle, (void *)destination, BaseToBytes(base));
#endif
	}

	virtual object Write(object source, object base) {
#ifdef PROC_OS_WIN
		return (ptrdiff_t)_write(_handle, (const void *)source, BaseToBytes(base));
#else
		return (ptrdiff_t)write(_handle, source, BaseToBytes(base));
#endif
	}

	virtual object Read(Writer *destination) {
		return NULL;
	}

	virtual object Write(Reader *source) {
		return NULL;
	}
};

class MemoryStream: public Reader, public Writer {
	public:

	MemoryStream(object pointer) {
	}

	virtual ~MemoryStream() {
	}

	virtual object Read(object destination, object base) {
		return NULL;
	}

	virtual object Write(object source, object base) {
		return NULL;
	}
};


//######################################################################################################################
//#                                                       Utf8                                                         #
//#   3. Исходные коды программ представлены в текстовом виде. Наиболее распространенным сейчас является формат        #
//#   UTF-8. Компилятор должен как минимум его поддерживать, чтобы обеспечивать чтение и запись текстовых данных.      #
//#                                                                                                                    #
//######################################################################################################################

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
private:

	char _symbol;
	Reader *_reader;
	Writer *_writer;

	/*
		Set the next continuation byte.
		Необходимо учесть, что запись и чтение необходимо выполнять в двоичном режиме,
		чтобы операционная система не меняла EOL.
	*/
	void set(char cb) {
		_writer->Write((ptrdiff_t)(&cb), 256);
	}

	/*
		Get the next byte. It returns UTF8_END if there are no more bytes.
	*/
	int get() {
		if (_reader->Read((object)&_symbol, 256) <= 0)
			return UTF8_END;

		return _symbol & 0xFF;
	}

	/*
		Get the 6-bit payload of the next continuation byte.
		Return UTF8_ERROR if it is not a contination byte.
	*/
	int cont() {
		int c = get();
		return ((c & 0xC0) == 0x80) ? (c & 0x3F) : UTF8_ERROR;
	}

	/*
		Целое заранее содержит 4 байта (октета) для кодирования Unicode-символа.
		В зависимости от значения необходимо понять каким количеством байт кодируется этот символ в UTF-8.
	*/
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

	/*
		Extract the next character.
		Returns: the character (between 0 and 1114111)
				or  UTF8_END   (the end)
				or  UTF8_ERROR (error)
	*/
	int utf8_decode_next() {
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

public:

	// Здесь еще возможны варианты с Seeker'ом, но очень затратно это описывать вручную и несколькими классами.
	// Теоретически компилятор может создавать реализацию любого интерфейса отдельно от всех реализаций.
	// Необходимо дописать новый синтаксис для конструктора, который явно указывает используемый интерфейс(ы).
	Utf8(Reader *reader) {
		_reader = reader;
	}

	/*
		Initialize the UTF-8 encoder.
	*/
	Utf8(Writer *writer) {
		_writer = writer;
	}

	virtual object Read(Writer *destination) {
		return utf8_decode_next();
	}

	virtual object Read(object destination, object base) { // TODO Временная заглушка для старых языков.
		return utf8_decode_next();
	}

	virtual object Write(Reader *source) {
		utf8_encode_next((*((int *)source)));
		return NULL;
	}

	virtual object Write(object source, object base) { // TODO Временная заглушка для старых языков.
		utf8_encode_next((*((int *)source)));
		return NULL;
	}
};


//######################################################################################################################
//#                                              Лексический анализатор                                                #
//#   4. Основной лексический анализатор Proc.                                                                         #
//#   Первичная обработка исходного кода для компилятора или интерпретатора начинается с лексического анализа. Есть    #
//#   несколько способов реализации: обычная реализация, интерпретатор БНФ или регулярных выражений, или компилятор    #
//#   анализаторов типа Lex. Для базовых языков подойдёт первый вариант, как самый простой и производительный.         #
//#                                                                                                                    #
//######################################################################################################################

/*
	LexicalAnalyzer
	TODO Варианты для переименования: lexical analyzer, lexer, tokenizer, scanner, ProcScanner.
*/
class LexicalAnalyzer {

private:

	Reader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	LexicalAnalyzer(Reader *reader) {
		_reader = reader;

		_writer = new FileStream("debug.txt", O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE);
		_utf8 = new Utf8((Writer*)_writer);
	}

	~LexicalAnalyzer() {
		delete _utf8;
		_writer->Close();
		delete _writer;
	}

	bool Get() {
		int symbol = _reader->Read(NULL); // TODO Temporary crutches.
		if (symbol > 0) {
			// Вывод UTF-8:
			if (symbol < 256)
				printf_s("%c", symbol);
			else
				printf_s("[%u]", symbol);
			// Запись UTF-8:
			_utf8->Write((Reader *)&symbol);

			return true;
		}
		
		return false;
	}
};


//######################################################################################################################
//#                                                 AssemblerScanner                                                   #
//#   5. Здесь будет что-то типа читабельного представления машинного языка, а может сразу нескольких. Как вариант     #
//#   стоит подумать в принципе о наследовании анализаторов от LexicalScanner.                                         #
//#                                                                                                                    #
//######################################################################################################################

/*
	AssemblerScanner
	TODO Варианты для переименования: Amd64AssemblerScanner, т.к. хрен его знает можно ли другие ассемблеры представить одинаково.
*/
class AssemblerScanner {

private:

	Reader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	AssemblerScanner(Reader *reader) {
		_reader = reader;

		_writer = new FileStream("debug.txt", O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE);
		_utf8 = new Utf8((Writer*)_writer);
	}

	~AssemblerScanner() {
		delete _utf8;
		_writer->Close();
		delete _writer;
	}

	bool Get() {
		int symbol = _reader->Read(NULL); // TODO Temporary crutches.
		if (symbol > 0) {
			// Вывод UTF-8:
			if (symbol < 256)
				printf_s("%c", symbol);
			else
				printf_s("[%u]", symbol);
			// Запись UTF-8:
			_utf8->Write((Reader *)&symbol);

			return true;
		}
		
		return false;
	}
};


//######################################################################################################################
//#                                                   Amd64Scanner                                                     #
//#   6. Это лексический анализатор двоичного кода архитектуры AMD64.                                                  #
//#                                                                                                                    #
//######################################################################################################################

class Amd64Scanner {

private:

	Reader *_reader;

	FileStream *_writer;
	Utf8 *_utf8;

public:

	Amd64Scanner(Reader *reader) {
		_reader = reader;

		_writer = new FileStream("debug.txt", O_CREAT | O_WRONLY | O_BINARY, _S_IREAD | _S_IWRITE);
		_utf8 = new Utf8((Writer*)_writer);
	}

	~Amd64Scanner() {
		delete _utf8;
		_writer->Close();
		delete _writer;
	}

	bool Get() {
		int symbol = _reader->Read(NULL); // TODO Temporary crutches.
		if (symbol > 0) {
			// Вывод UTF-8:
			if (symbol < 256)
				printf_s("%c", symbol);
			else
				printf_s("[%u]", symbol);
			// Запись UTF-8:
			_utf8->Write((Reader *)&symbol);

			return true;
		}
		
		return false;
	}
};


//######################################################################################################################
//#                                        Кодогенератор и виртуальная машина                                          #
//######################################################################################################################


//######################################################################################################################
//#                                                   Точка входа                                                      #
//######################################################################################################################

// Используемые прототипы Оберон-0:
extern "C" {
	void OssInit(const char *fileName, long pos); // Файл с исходным кодом и его начальная позиция.
	void Oss(const char *fileName); // Файл для записи результатов лексического анализатора.
	void Compile(const char *fileName);
}

int main(int argc, char **argv)
{
	// Combines several ideas: UTM, VM, Interpreter, Translator, Compiler.

	// Отладка Оберон-0:
	//printf("Oberon-0\r\n\r\n");
	//Compile("debug.mod");

	// Proc-0:
	if (argc <= 1) { // Первым параметром всегда идёт полный путь к исполняемому файлу.
		printf("Usage: proc [--version] [--help] <command>\n\n");
		printf("There are common Proc commands:\n\n");
		printf("-l FILE\t\t\tuse lexical analysis on FILE\n");

	} else if (strcmp(argv[1], "-l") == 0) { // Лексический анализ файла.
		int i = 0;
		FileStream source(argv[2]);
		Utf8 utf8((Reader*)&source);
		LexicalAnalyzer lexer(&utf8);
		while (lexer.Get()) {
			i++;
		}
		printf("Proc lexer ready with %u states.\n", i);
	}

	return 0;
}
