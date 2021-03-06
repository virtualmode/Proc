#pragma once

#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include "Temp/Dependency.h"

// Лексемы общего лексического анализатора исходного кода.
// Представляют собой множество терминальных символов поддерживаемых языков.
enum class Symbol {
	Unknown, // Группа непредусмотренных символов.

/*
	// TODO Объединение в группу разделителей увеличит производительность
	// TODO и немного снизит наглядность, поэтому надо подумать.
	// Односимвольные терминалы.
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

	Colon, // :
	Semicolon, // ;
	LessThanSign, // <
	EqualsSign, // =
	GreaterThanSign, // >
	QuestionMark, // ?
	CommercialAt, // @

	LeftSquareBracket, // [
	Backslash, // \ :)
	RightSquareBracket, // ]
	CircumflexAccent, // ^
	Underline, // _
	GraveAccent, // `

	LeftCurlyBracket, // {
	VerticalLine, // |
	RightCurlyBracket, // }
	Tilde, // ~
*/

	// Это базовые символы для всех языков.
	EndOfLine, // Признак окончания строки (LF, CR, CRLF, NEL, LS, PS, VT).
	EndOfStream, // Терминатор последовательности.
	Delimiter, // Односимвольные терминалы, соответствующие разделителям.
	Identifier, // Нетерминальные идентификаторы, начинающиеся с латинской буквы или подчеркивания, содержащие цифры.
	Whitespace, // Горизонтальные отступы между словами (SP, HT, TAB).

	// Числа выражаются конечным числом способов, и можно выделить сразу все лексемы для разных форматов.
	Integer, // Последовательность цифр без разделителей: -123, 0x80, 21h.
	ZeroXInteger,
	XmlInteger, // XML integer format: &#8217.

	Real, // Вещественные числа: -0.3, 3.57e-3, 0.7e12, 1e+20, 5.0f, 1.0d.
	RealExp,

	// Числа с плавающей точкой.
	CppRealFloat,
	CppRealDouble,

	// Шестнадцатиричные целые числа.
	Hexadecimal, // Unix, AT&T assembly, C programming language and its syntactic descendants: 0x5a3.
	BasicHexadecimal, // QuickBASIC, FreeBASIC, Visual Basic: &h5a3.
	CssHexadecimal, // Color references in HTML: #ffffff.
	EscapeHexadecimal, // Escape sequence with : \x5a3.
	IntelHexadecimal, // Intel-derived assembly languages and Modula-2: 5A3H, FFh or 0FFh.
	PascalHexadecimal, // Motorola, 6502, Pascal, Delphi, BASIC: $5a3.
	XmlHexadecimal, // XML hexadecimal format: &#x821a.
	UnicodeHexadecimal, // Unicode escape sequence with all four hexadecimal digits: \u004b.

	AlgolHexadecimal,

	// Терминальные символы логики.
	NotEqual,

	// Зарезервированные слова.
	Class,
	Enumeration,
};

#endif // SYMBOL_HPP
