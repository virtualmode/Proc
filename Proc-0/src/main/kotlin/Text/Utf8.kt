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

	Code     Continuation Minimum Maximum
	0xxxxxxx            0       0     127
	10xxxxxx        error
	110xxxxx            1     128    2047
	1110xxxx            2    2048   65535 excluding 55296 - 57343
	11110xxx            3   65536 1114111
	11111xxx        error
*/

/*
	Conjunction (and)			a & b		a and b
	Disjunction (or)			a | b		a or b
	Exclusive disjunction (xor)	a ^ b		a xor b
	Inversion					~ a			a.inv()
	Shift Left					a << bits	a shl bits
	Shift Right					a >> bits	a shr bits
	Unsigned Shift Right		a >>> bits	a ushr bits
*/

package proc.Text

import proc.Interop.Reader
import proc.Interop.Writer

/**
 * Поток символов UTF-8.
 */
class Utf8 : CharStream {

	//region Constants

	companion object {
		private const val UTF8_BUFFER_SIZE: Int = 4

		public const val UTF8_END: Int = -1
		public const val UTF8_ERROR: Int = -2

		public const val UTF8_SMALL_CYRILLIC_LETTER_FROM: Int = 0x0430
		public const val UTF8_SMALL_CYRILLIC_LETTER_TO: Int = 0x044F
		public const val UTF8_CAPITAL_CYRILLIC_LETTER_FROM: Int = 0x0410
		public const val UTF8_CAPITAL_CYRILLIC_LETTER_TO: Int = 0x042F
	}

	//endregion Constants

	//region Fields

	private var _symbol: Byte // Очередной прочитанный байт.
	private var _buffer: ByteArray
	private var _reader: Reader
	private var _writer: Writer

	// Предыдущий символ последовательности перевода на новую строку.
	private var _eolSequence: CharType

	//endregion Fields

	//region Properties

	override var Type: CharType
		get
		set

	//endregion Properties

	//region Constructors

	init {
		// Выглядит ненужной конструкцией для языка.
		//_reader = null
		//_writer = null

		_symbol = 0
		_buffer = ByteArray(UTF8_BUFFER_SIZE)
		_eolSequence = CharType.Unknown
		Type = CharType.Unknown
		//EndOfStream = false
		Position = 0
		Character = 0
		Column = 0
		Line = 0
	}

	/**
	 * Основной конструктор.
	 * TODO Если будут введены отдельные реализации интерфейсов, необходимо рассмотреть возможность языка
	 * TODO комбинировать несколько интерфейсов и не писать каждый раз отдельные конструкторы.
	 * @param reader Входящий поток состояний.
	 * @param writer Исходящий поток состояний.
	 */
	constructor(reader: Reader, writer: Writer) {
		_reader = reader
		_writer = writer
	}

	/**
	 * Здесь еще возможны варианты с Seeker'ом, но очень затратно это описывать вручную и несколькими классами.
	 * Теоретически компилятор может создавать реализацию любого интерфейса отдельно от общей реализации.
	 * Необходимо дописать новый синтаксис для конструктора, который явно указывает используемый интерфейс(ы).
	 * Конструктор для Proc будет содержать в конструкторе интерфейс SourceToken.UnicodeReader и реализовывать часть класса.
	 */
	//constructor(reader: Reader) {
	//	_reader = reader
	//}

	/**
	 * Initialize the UTF-8 encoder.
	 * Конструктор для Proc будет содержать в конструкторе интерфейс SourceToken.UnicodeWriter и реализовывать часть класса.
	 */
	//constructor(writer: Writer) {
	//	_writer = writer
	//}

	//endregion Constructors

	//region Methods

	/**
	 * Set the next continuation byte.
	 * Необходимо учесть, что запись и чтение необходимо выполнять в двоичном режиме,
	 * чтобы операционная система не меняла EOL.
	 */
	private fun set(cb: Byte)
	{
		_buffer[0] = cb
		_writer.Write(_buffer, 256)
	}

	// Get the next byte. It returns UTF8_END if there are no more bytes.
	private fun get(): Int
	{
		if (_reader?.Read(_buffer, 256) as Int <= 0)
		return UTF8_END

		_symbol = _buffer[0]

		return _symbol.toInt() and 0xff
	}

	/**
	 * Get the 6-bit payload of the next continuation byte.
	 * @return UTF8_ERROR if it is not a continuation byte.
	 */
	private fun cont(): Int {
		var c: Int = get()

		// Интересная реализация тернарного оператора.
		return if ((c and 0xC0) == 0x80) (c and 0x3F) else UTF8_ERROR
	}

	/**
	 * Целое заранее содержит 4 байта (октета) для кодирования Unicode-символа.
	 * В зависимости от значения необходимо понять каким количеством байт кодируется этот символ в UTF-8.
	 */
	private fun utf8_encode_next(symbol: Int) {
		var i: Int
		var temp: Int
		var offset: Int = 0
		var count: Int = 0

		// 0xxxxxxx
		if (symbol <= 0x0000007F) {
			// Код символа до 127. Требуется 1 октет для кодирования.
			set(symbol as Byte)
			return

			// 110xxxxx 10xxxxxx
		} else if (symbol <= 0x000007FF) {
			// 2047. Требуется 2 октета.
			count = 1
			offset = 0xC0

			// 1110xxxx 10xxxxxx 10xxxxxx
		} else if (symbol <= 0x0000FFFF) {
			// 65535. Требуется 3 октета.
			count = 2
			offset = 0xE0

			// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		} else if (symbol <= 0x0010FFFF) {
			// 1114111. Требуется 4 октета.
			count = 3
			offset = 0xF0
		}

		i = 0
		set(((symbol shr (6 * count)) + offset) as Byte)
		i++

		while (count > 0) {
			temp = symbol shr (6 * (count - 1))
			set((0x80 or (temp and 0x3f)) as Byte)
			i++
			count--
		}
	}

	// Extract the next character.
	// @return The character (between 0 and 1114111) or UTF8_END or UTF8_ERROR.
	private fun utf8_decode_next(): Int {
		var c: Int  // The first byte of the character.
		var c1: Int // The first continuation character.
		var c2: Int // The second continuation character.
		var c3: Int // The third continuation character.
		var r: Int  // The result.

		c = get()

		if (c < 0)
			return c

		// Zero continuation (0 to 127).
		// Считывается первый байт. Если первый бит == 0, то значение байта <= 127.
		// Это значит, что символ относится к модифицированной ASCII-таблице и является
		// латинским символом. Если значение байта > 127, то символ не ASCII.
		if ((c and 0x80) == 0) {
			return c
		}

		// One continuation (128 to 2047).
		// Символ относится к двубайтовым, если первые 3 бита 0xE0 == 110 (0xC0).
		if ((c and 0xE0) == 0xC0) {
			c1 = cont()
			if (c1 >= 0) {
				r = ((c and 0x1F) shl 6) or c1
				if (r >= 128) {
					return r
				}
			}

			// Two continuations (2048 to 55295 and 57344 to 65535).
		} else if ((c and 0xF0) == 0xE0) {
			c1 = cont()
			c2 = cont()
			if ((c1 or c2) >= 0) {
				r = ((c and 0x0F) shl 12) or (c1 shl 6) or c2
				if (r >= 2048 && (r < 55296 || r > 57343)) {
					return r
				}
			}

			// Three continuations (65536 to 1114111).
		} else if ((c and 0xF8) == 0xF0) {
			c1 = cont()
			c2 = cont()
			c3 = cont()
			if ((c1 or c2 or c3) >= 0) {
				r = ((c and 0x07) shl 18) or (c1 shl 12) or (c2 shl 6) or c3
				if (r >= 65536 && r <= 1114111) {
					return r
				}
			}
		}
		return UTF8_ERROR
	}

	// Обновление лексемы в соответствии с текущим кодом символа.
	fun UpdateType() {
		var value: Int = Value + CharType.Null as Int // Отвязывание Юникода от значения.
		if (Value < 0)
		{
			Type = CharType.EndOfStream
			//EndOfStream = true
		} else if (value <= CharType.Delete as Int) {
			Type = value as CharType

			// Отладка.
			//print(Value as Char)
		} else {
			// TODO Реализовать определение других символов при необходимости.
			Type = CharType.Unknown

			// Отладка.
			//print(Value as Char)
		}
	}

	// Состояние новой строки.
	fun NextLine() {
		Line++
		Character = 0
		Column = 0
	}

	// Вычисление курсора, номера символа в строке, колонки, номера строки.
	private fun UpdateCounters() {
		if (Type == CharType.EndOfStream)
			return

		Position++
		Character++
		Column++ // TODO Необходимо учитывать, что символы типа табуляции занимают несколько позиций.

		if (IsEndOfLine()) {
			if (_eolSequence != CharType.CarriageReturn || Type != CharType.LineFeed)
				NextLine()

			_eolSequence = Type
		} else {
			if (_eolSequence != CharType.Unknown)
				NextLine()

			_eolSequence = CharType.Unknown
		}
	}

	public fun IsSmallCyrillicLetter(): Boolean
	{
		// Source: Value >= UTF8_SMALL_CYRILLIC_LETTER_FROM && Value <= UTF8_SMALL_CYRILLIC_LETTER_TO
		return Value in UTF8_SMALL_CYRILLIC_LETTER_FROM..UTF8_SMALL_CYRILLIC_LETTER_TO
	}

	public fun IsCapitalCyrillicLetter(): Boolean
	{
		// Source: Value >= UTF8_CAPITAL_CYRILLIC_LETTER_FROM && Value <= UTF8_CAPITAL_CYRILLIC_LETTER_TO
		return Value in UTF8_CAPITAL_CYRILLIC_LETTER_FROM..UTF8_CAPITAL_CYRILLIC_LETTER_TO
	}

	// Является ли текущий символ строчной буквой.
	override fun IsSmallLetter(): Boolean {
		return IsSmallLatinLetter() ||
			IsSmallCyrillicLetter()
	}

	// Является ли текущий символ заглавной буквой.
	override fun IsCapitalLetter(): Boolean {
		return IsCapitalLatinLetter() ||
			IsCapitalCyrillicLetter()
	}

	override fun ReadChar(): Int {
		Value = utf8_decode_next()
		UpdateType()
		UpdateCounters()
		return Value
	}

	override fun SeekChar(offset: Long): Boolean {
		// TODO Необходимо реализовать переход машины состояний вперед и назад на несколько шагов.
		// TODO Также надо подумать о возможности в принципе перехода назад.
		return false
	}

	override fun WriteChar(character: Int) {
		utf8_encode_next(character)
		Value = character
		UpdateType()
		UpdateCounters()
		Position++
	}

	//endregion Methods
}
