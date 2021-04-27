#pragma once

#ifndef CHAR_HPP
#define CHAR_HPP

// Мнемоники символов доступных алфавитов, представляющие их смысл, а не числовое значение в конкретной кодировке.
// Все символы строго сгруппированы для оптимизации обращений лексических анализаторов.
enum class Char {
	Unknown, // Символ неизвестного назначения.

	// Символы управления.
	EndOfText, // Inform the receiving computer that the end of a record has been reached, ^C.

	// Символы отступов.
	CharacterTabulation, // Горизонтальная табуляция, HT, TAB.
	Space,

	// Символы манипуляций со строками.
	CarriageReturn, // Возврат каретки, CR.
	EndOfLine, // Конец строки, EOL, LF, NL.
	LineFeed, // Подача строки, LF.
	LineSeparator, // Разделитель строк, LS.
	NextLine, // Переход на следующую строку, NEL.
	ParagraphSeparator, // Разделитель абзацев, PS.
	VerticalTabulation, // Вертикальная табуляция, VT.

	// Символы разделителей.
	Ampersand, // &
	Apostrophe, // '
	Asterisk, // *
	Backslash, // \ :)
	CircumflexAccent, // ^
	Colon, // :
	Comma, // ,
	CommercialAt, // @
	DollarSign, // $
	EqualsSign, // =
	ExclamationMark, // !
	FullStop, // .
	GraveAccent, // `
	HyphenMinus, // -
	LowLine, // _
	NumberSign, // #
	PercentSign, // %
	PlusSign, // +
	QuestionMark, // ?
	QuotationMark, // "
	Semicolon, // ;
	Slash, // /
	Tilde, // ~
	VerticalLine, // |

	// Парные разделители.
	GreaterThanSign, // >
	LeftCurlyBracket, // {
	LeftParenthesis, // (
	LeftSquareBracket, // [
	LessThanSign, // <
	RightCurlyBracket, // }
	RightParenthesis, // )
	RightSquareBracket, // ]

	// Арабские цифры.
	DigitZero,
	DigitOne,
	DigitTwo,
	DigitThree,
	DigitFour,
	DigitFive,
	DigitSix,
	DigitSeven,
	DigitEight,
	DigitNine,

	// Латинские заглавные буквы.
	LatinCapitalLetterA,
	LatinCapitalLetterB,
	LatinCapitalLetterC,
	LatinCapitalLetterD,
	LatinCapitalLetterE,
	LatinCapitalLetterF,
	LatinCapitalLetterG,
	LatinCapitalLetterH,
	LatinCapitalLetterI,
	LatinCapitalLetterJ,
	LatinCapitalLetterK,
	LatinCapitalLetterL,
	LatinCapitalLetterM,
	LatinCapitalLetterN,
	LatinCapitalLetterO,
	LatinCapitalLetterP,
	LatinCapitalLetterQ,
	LatinCapitalLetterR,
	LatinCapitalLetterS,
	LatinCapitalLetterT,
	LatinCapitalLetterU,
	LatinCapitalLetterV,
	LatinCapitalLetterW,
	LatinCapitalLetterX,
	LatinCapitalLetterY,
	LatinCapitalLetterZ,

	// Латинские строчные буквы.
	LatinSmallLetterA,
	LatinSmallLetterB,
	LatinSmallLetterC,
	LatinSmallLetterD,
	LatinSmallLetterE,
	LatinSmallLetterF,
	LatinSmallLetterG,
	LatinSmallLetterH,
	LatinSmallLetterI,
	LatinSmallLetterJ,
	LatinSmallLetterK,
	LatinSmallLetterL,
	LatinSmallLetterM,
	LatinSmallLetterN,
	LatinSmallLetterO,
	LatinSmallLetterP,
	LatinSmallLetterQ,
	LatinSmallLetterR,
	LatinSmallLetterS,
	LatinSmallLetterT,
	LatinSmallLetterU,
	LatinSmallLetterV,
	LatinSmallLetterW,
	LatinSmallLetterX,
	LatinSmallLetterY,
	LatinSmallLetterZ,
};

#define CHAR_SIZE 104

//UnicodeCategory r0 = char.GetUnicodeCategory(symbol);
//char.IsControl()
//char.IsDigit()
//char.IsHighSurrogate()
//char.IsLetter()
//char.IsLetterOrDigit()
//char.IsLowSurrogate()
//char.IsLower()
//char.IsNumber()
//char.IsPunctuation()
//char.IsSeparator()
//char.IsSurrogate()
//char.IsSurrogatePair()
//char.IsSymbol()
//char.IsUpper()
//char.IsWhiteSpace()

/// <summary>Defines the Unicode category of a character.</summary>
enum class UnicodeCategory {
	/// <summary>Uppercase letter. Signified by the Unicode designation "Lu" (letter, uppercase). The value is 0.</summary>
	UppercaseLetter,
	/// <summary>Lowercase letter. Signified by the Unicode designation "Ll" (letter, lowercase). The value is 1.</summary>
	LowercaseLetter,
	/// <summary>Titlecase letter. Signified by the Unicode designation "Lt" (letter, titlecase). The value is 2.</summary>
	TitlecaseLetter,
	/// <summary>Modifier letter character, which is free-standing spacing character that indicates modifications of a preceding letter. Signified by the Unicode designation "Lm" (letter, modifier). The value is 3.</summary>
	ModifierLetter,
	/// <summary>Letter that is not an uppercase letter, a lowercase letter, a titlecase letter, or a modifier letter. Signified by the Unicode designation "Lo" (letter, other). The value is 4.</summary>
	OtherLetter,
	/// <summary>Nonspacing character that indicates modifications of a base character. Signified by the Unicode designation "Mn" (mark, nonspacing). The value is 5.</summary>
	NonSpacingMark,
	/// <summary>Spacing character that indicates modifications of a base character and affects the width of the glyph for that base character. Signified by the Unicode designation "Mc" (mark, spacing combining). The value is 6.</summary>
	SpacingCombiningMark,
	/// <summary>Enclosing mark character, which is a nonspacing combining character that surrounds all previous characters up to and including a base character. Signified by the Unicode designation "Me" (mark, enclosing). The value is 7.</summary>
	EnclosingMark,
	/// <summary>Decimal digit character, that is, a character in the range 0 through 9. Signified by the Unicode designation "Nd" (number, decimal digit). The value is 8.</summary>
	DecimalDigitNumber,
	/// <summary>Number represented by a letter, instead of a decimal digit, for example, the Roman numeral for five, which is "V". The indicator is signified by the Unicode designation "Nl" (number, letter). The value is 9.</summary>
	LetterNumber,
	/// <summary>Number that is neither a decimal digit nor a letter number, for example, the fraction 1/2. The indicator is signified by the Unicode designation "No" (number, other). The value is 10.</summary>
	OtherNumber,
	/// <summary>Space character, which has no glyph but is not a control or format character. Signified by the Unicode designation "Zs" (separator, space). The value is 11.</summary>
	SpaceSeparator,
	/// <summary>Character that is used to separate lines of text. Signified by the Unicode designation "Zl" (separator, line). The value is 12.</summary>
	LineSeparator,
	/// <summary>Character used to separate paragraphs. Signified by the Unicode designation "Zp" (separator, paragraph). The value is 13.</summary>
	ParagraphSeparator,
	/// <summary>Control code character, with a Unicode value of U+007F or in the range U+0000 through U+001F or U+0080 through U+009F. Signified by the Unicode designation "Cc" (other, control). The value is 14.</summary>
	Control,
	/// <summary>Format character that affects the layout of text or the operation of text processes, but is not normally rendered. Signified by the Unicode designation "Cf" (other, format). The value is 15.</summary>
	Format,
	/// <summary>High surrogate or a low surrogate character. Surrogate code values are in the range U+D800 through U+DFFF. Signified by the Unicode designation "Cs" (other, surrogate). The value is 16.</summary>
	Surrogate,
	/// <summary>Private-use character, with a Unicode value in the range U+E000 through U+F8FF. Signified by the Unicode designation "Co" (other, private use). The value is 17.</summary>
	PrivateUse,
	/// <summary>Connector punctuation character that connects two characters. Signified by the Unicode designation "Pc" (punctuation, connector). The value is 18.</summary>
	ConnectorPunctuation,
	/// <summary>Dash or hyphen character. Signified by the Unicode designation "Pd" (punctuation, dash). The value is 19.</summary>
	DashPunctuation,
	/// <summary>Opening character of one of the paired punctuation marks, such as parentheses, square brackets, and braces. Signified by the Unicode designation "Ps" (punctuation, open). The value is 20.</summary>
	OpenPunctuation,
	/// <summary>Closing character of one of the paired punctuation marks, such as parentheses, square brackets, and braces. Signified by the Unicode designation "Pe" (punctuation, close). The value is 21.</summary>
	ClosePunctuation,
	/// <summary>Opening or initial quotation mark character. Signified by the Unicode designation "Pi" (punctuation, initial quote). The value is 22.</summary>
	InitialQuotePunctuation,
	/// <summary>Closing or final quotation mark character. Signified by the Unicode designation "Pf" (punctuation, final quote). The value is 23.</summary>
	FinalQuotePunctuation,
	/// <summary>Punctuation character that is not a connector, a dash, open punctuation, close punctuation, an initial quote, or a final quote. Signified by the Unicode designation "Po" (punctuation, other). The value is 24.</summary>
	OtherPunctuation,
	/// <summary>Mathematical symbol character, such as "+" or "= ". Signified by the Unicode designation "Sm" (symbol, math). The value is 25.</summary>
	MathSymbol,
	/// <summary>Currency symbol character. Signified by the Unicode designation "Sc" (symbol, currency). The value is 26.</summary>
	CurrencySymbol,
	/// <summary>Modifier symbol character, which indicates modifications of surrounding characters. For example, the fraction slash indicates that the number to the left is the numerator and the number to the right is the denominator. The indicator is signified by the Unicode designation "Sk" (symbol, modifier). The value is 27.</summary>
	ModifierSymbol,
	/// <summary>Symbol character that is not a mathematical symbol, a currency symbol or a modifier symbol. Signified by the Unicode designation "So" (symbol, other). The value is 28.</summary>
	OtherSymbol,
	/// <summary>Character that is not assigned to any Unicode category. Signified by the Unicode designation "Cn" (other, not assigned). The value is 29.</summary>
	OtherNotAssigned,
};

#endif // CHAR_HPP
