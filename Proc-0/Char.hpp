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
	LatinSmallLetterJ,
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

#endif // CHAR_HPP
