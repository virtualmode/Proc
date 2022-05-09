package proc.Source.Symbol

/**
 * Тип символа (лексемы) лексического анализатора исходного кода.
 * Перечисление представляет множество всех терминальных символов поддерживаемых языков.
 */
enum class Type { // enum Symbol.Type

	//region Вспомогательные символы

	Unknown, // Группа непредусмотренных символов.
	EndOfStream, // Терминатор последовательности.

	//endregion

	/*//region Односимвольные терминалы

	// Данные лексемы используются, если соответствующие им литеры не являются частью других терминалов языка.

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

	// ASCII 0x003a-0x0040.
	Colon, // :
	Semicolon, // ;
	LessThanSign, // <
	EqualsSign, // =
	GreaterThanSign, // >
	QuestionMark, // ?
	CommercialAt, // @

	// ASCII 0x005b-0x0060.
	LeftSquareBracket, // [
	Backslash, // \ :)
	RightSquareBracket, // ]
	CircumflexAccent, // ^
	Underline, // _
	GraveAccent, // `

	// ASCII 0x007b-0x007e.
	LeftCurlyBracket, // {
	VerticalLine, // |
	RightCurlyBracket, // }
	Tilde, // ~

	//endregion*/

	//region Терминальные символы логики

	OrPredicate, // ||
	AndPredicate, // &&
	EqualsPredicate, // ==
	NotEqualsPredicate, // !=
	LessThanPredicate, // <
	LessThanOrEqualPredicate, // <=
	GreaterThanPredicate, // >
	GreaterThanOrEqualPredicate, // >=

	//endregion

	//region Арифметические операторы

	AddAssignment, // +=
	SubtractAssignment, // -=
	MultiplyAssignment, // *=
	DivideAssignment, // /=
	RemainderAssignment, // %=

	//endregion

	//region Зарезервированные слова

	// Access modifiers.
	// Модификаторы доступа.
	Private,
	Protected,
	Public,

	Constant,
	Static,

	// Объекты.
	Class,
	Enumeration,

	//endregion

	//region Неутверждённые символы

	// Составные терминальные символы.
	EndOfLine, // Признак окончания строки (LF, CR, CRLF, NEL, LS, PS, VT).
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

	//endregion
}

/* lexical symbols of Oberon

 0 null
 1 times
 3 div
 4 mod
			5 and			&& AND
 6 plus
 7 minus
			8 or			|| OR
			9 eql			== =
			10 neq			!= #
			11 lss			<
			12 leq			<=
			13 gtr			>
			14 geq			>=
18 period
20 char
21 int
23 false
24 true
27 not
28 lparen
29 lbrak
31 ident
32 if
34 while
35 repeat
40 comma
41 colon
42 becomes
44 rparen
45 rbrak
47 then
48 of
49 do
52 semicolon
53 end
55 else
56 elsif
57 until
60 array
61 record
63 const
64 type
65 var
66 procedure
67 begin
69 module
70 eof

*/
