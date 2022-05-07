package proc.Text

/**
 * Интерфейс потока символов для работы с текстом.
 * TODO CharReader и CharWriter должны использоваться независимо.
 * TODO Необходимо добавить в язык возможность композиции интерфейсов.
 * TODO А пока придётся наследовать с другими необходимыми интерфейсами.
 * TODO После реализации композиции данный класс не будет иметь смысла.
 */
@Deprecated("Implement interface composition instead. Allow fields usage?")
abstract class CharStream: Char, CharReader, CharWriter, CharSeeker {

	override var Value: Int
		get() = TODO("Not yet implemented")
		set(value) {}

	override var Type: CharType
		get() = TODO("Not yet implemented")
		set(value) {} // protected

	//override var EndOfStream: Long
	//	get() = TODO("Not yet implemented")
	//	set(value) {}

	override var Position: Long
		get() = TODO("Not yet implemented")
		set(value) {}

	override var Character: Long
		get() = TODO("Not yet implemented")
		set(value) {}

	override var Column: Long
		get() = TODO("Not yet implemented")
		set(value) {}

	override var Line: Long
		get() = TODO("Not yet implemented")
		set(value) {}

	abstract override fun IsSmallLetter(): Boolean
	abstract override fun IsCapitalLetter(): Boolean

	/**
	 * Является ли текущий символ буквой.
	 */
	override fun IsLetter(): Boolean =
		IsSmallLetter() || IsCapitalLetter()

	/**
	 * Является ли текущий символ арабской десятичной цифрой юникода.
	 */
	override fun IsDecimalDigit(): Boolean =
		Type >= CharType.Digit0 && Type <= CharType.Digit9

	/**
	 * Является ли текущий символ строчной латинской буквой.
	 */
	override fun IsSmallLatinLetter(): Boolean =
		Type >= CharType.SmallLetterA && Type <= CharType.SmallLetterZ

	/**
	 * Является ли текущий символ заглавной латинской буквой.
	 */
	override fun IsCapitalLatinLetter(): Boolean =
		Type >= CharType.CapitalLetterA && Type <= CharType.CapitalLetterZ

	/**
	 * Является ли текущий символ латинской буквой.
	 */
	override fun IsLatinLetter(): Boolean =
		IsSmallLatinLetter() || IsCapitalLatinLetter()

	/**
	 * Символ относится к группе допустимых разделителей, используемых в компиляторе.
	 */
	//override fun IsDelimiter(): Boolean =
	//	Type >= CharType.Space && Type <= CharType.Slash ||
	//	Type >= CharType.Colon && Type <= CharType.CommercialAt ||
	//	Type >= CharType.LeftSquareBracket && Type <= CharType.GraveAccent ||
	//	Type >= CharType.LeftCurlyBracket && Type <= CharType.Delete

	/**
	 * Символ является разделителем строк или входит в последовательность разделения.
	 */
	override fun IsEndOfLine(): Boolean =
		Type == CharType.CarriageReturn ||
		Type == CharType.LineFeed ||
		Type == CharType.NextLine ||
		Type == CharType.LineSeparator ||
		Type == CharType.ParagraphSeparator ||
		Type == CharType.VerticalTabulation

	override fun IsWhitespace(): Boolean =
		Type == CharType.HorizontalTabulation ||
		Type == CharType.Space

	abstract override fun ReadChar(): Int
	abstract override fun SeekChar(offset: Long): Boolean
	abstract override fun WriteChar(character: Int)
}
