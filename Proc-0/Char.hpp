#pragma once

#ifndef CHAR_H
#define CHAR_H

// Множество абстрактного алфавита, обозначающее значение символов, а не их числовое представление.
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
	VerticalTabulation // Вертикальная табуляция, VT.
};

#endif // CHAR_H
