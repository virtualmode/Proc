#pragma once

#ifndef CHAR_HPP
#define CHAR_HPP

// Мнемоники символов доступных алфавитов, представляющие их смысл, а не числовое значение в конкретной кодировке.
// Все символы строго сгруппированы для оптимизации обращений лексических анализаторов.
enum class Char {

	// ASCII управляющие символы 0x0000-0x001f.
	Null, // Пустой символ ^@ (NULL).
	StartOfHeading, // Начало заголовка ^A.
	StartOfText, // Начало текста ^B.
	EndOfText, // Сигнал прерывания в терминале ^C.
	EndOfTransmission, // Конец вводимых данных ^D.
	Enquiry, // Запрос ^E.
	Acknowledge, // Подтверждение ^F.
	Bell, // Звуковой сигнал ^G, \a.
	Backspace, // Возврат на один шаг ^H, \b.
	CharacterTabulation, // Горизонтальная табуляция ^I, \t (HT, TAB).
	LineFeed, // Подача строки, конец строки, новая строка ^J, \n (LF, EOL, NL).
	LineTabulation, // Вертикальная табуляция ^K, \v (VT).
	FormFeed, // Прогон страницы ^L, \f (FF).
	CarriageReturn, // Возврат каретки ^M, \r (CR).
	ShiftOut, // Режим национальных символов ^N.
	ShiftIn, // Режим ASCII ^O.
	DataLinkEscape, // Экранирование управляющих символов в обычный текст ^P.
	DeviceControlOne, // Первый код управления устройством ^Q.
	DeviceControlTwo, // Второй код управления устройством ^R.
	DeviceControlThree, // Третий код управления устройством ^S.
	DeviceControlFour, // Четвёртый код управления устройством ^T.
	NegativeAcknowledge, // Отрицательное подтверждение ^U.
	SynchronousIdle, // Пустой символ для синхронного режима передачи ^V.
	EndOfTransmissionBlock, // Конец блока передаваемых данных ^W.
	Cancel, // Отмена предыдущих данных строки ^X.
	EndOfMedium, // Конец носителя ^Y.
	Substitute, // Символ замены потерянного во время передачи символа ^Z.
	Escape, // Альтернативный регистр для следующих символов, считающихся уже не ASCII ^[, \e.
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
	HyphenMinus, // -
	FullStop, // .
	Slash, // /

	// Индо-арабские десятичные цифры 0x0030-0x0039.
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

	// Латинские заглавные буквы 0x0041-0x005a.
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

	// ASCII 0x005b-0x0060.
	LeftSquareBracket, // [
	Backslash, // \ :)
	RightSquareBracket, // ]
	CircumflexAccent, // ^
	LowLine, // _
	GraveAccent, // `

	// Латинские строчные буквы 0x0061-0x007a.
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

	// ASCII 0x007b-0x007e.
	LeftCurlyBracket, // {
	VerticalLine, // |
	RightCurlyBracket, // }
	Tilde, // ~
	Delete, // Управляющий символ забивания кода отверстием на перфоленте ^? (DEL).

	Unknown, // Символ неизвестного назначения.

	// Unicode.
	NoBreakSpace, // Неразрывный пробел 0x00a0 (NBSP).
	NonBreakingHyphen, // Неразрывный дефис 0x2011.
	LineSeparator, // Разделитель строк (LS).
	NextLine, // Переход на следующую строку (NEL).
	ParagraphSeparator, // Разделитель абзацев (PS).
};

#endif // CHAR_HPP
