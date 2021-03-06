#pragma once

#ifndef SYMBOL_TOKEN_HPP
#define SYMBOL_TOKEN_HPP

#include "Temp/Dependency.h"

#include "Char.hpp"
#include "CharToken.hpp"
#include "Symbol.hpp"
#include "SymbolError.hpp"
#include "Keyword.hpp"

/*
	4. Первичная обработка исходного кода для компилятора или интерпретатора начинается с лексического анализа. Есть
	несколько способов реализации: обычная реализация, интерпретатор БНФ или регулярных выражений, компилятор
	анализаторов типа Lex. Для базовых языков подойдёт первый вариант, как самый простой и производительный.
	Если рассмотреть вообще любые данные, то при их первичной обработке происходит лексический анализ по сути, но место
	лексем могут занимать специфические конструкции: состояния, символы, цвета, заголовки, звуковые сэмплы и прочее.
	Чтение этих конструкций из потоков, запись и другие операции можно представить как часть одного и того же процесса.
	Такие классы задач можно выделить суффиксами в соответствии от их назначения, например Reader, Writer или Seeker.
*/

#define KEYWORD_TABLE_SIZE 32

// Лексический анализатор исходного кода, машина состояний, конечный автомат.
// В других источниках можно встретить варианты: lexical analyzer, lexer, tokenizer, scanner, token reader.
// Теоретически он должен быть написан для каждой поддерживаемой кодировки.
// При чтении одного и того же набора символов в разных кодировках все реализации должны возвращать одинаковую лексему.
// Набор лексем избавляет от необходимости создавать реализацию синтаксического анализатора для каждой кодировки.
// Но если и текстовые потоки представить аналогичным образом, одного лексического анализатора также будет достаточно.
class SymbolToken {
protected:

	CharToken &_charToken;

	int _keywordCount;
	struct Keyword _keywordTable[KEYWORD_TABLE_SIZE];

	// Перевод машины в состояние ошибки.
	void SetError(SymbolError error, const char *message) {
		Error = error;
		ErrorPosition = _charToken.Position;
		ErrorLine = _charToken.Line;
	}

	// Является ли текущий символ частью идентификатора.
	// @param orDigit Учитывать цифры в середине и конце идентификатора.
	inline bool IsIdentifierLetter(bool orDigit) {
		return _charToken.Type == Char::Underline ||
			_charToken.IsLatinLetter() || // TODO Можно расширить поддержку идентификаторов.
			(orDigit && _charToken.IsDecimalDigit());
	}

	inline void ReadIdentifier() {
		Type = Symbol::Identifier;
		Value = 0;
		do { // Считывание всего идентификатора.
			if (Value < KEYWORD_ID_SIZE) {
				// TODO Заменить на нормальные строки и символьные лексемы.
				Identifier[Value] = (char)_charToken.Value;
				Value++;
			}
			_charToken.ReadChar();
		} while (IsIdentifierLetter(true));
		Identifier[Value] = '\0'; // Терминальный ноль.
		// Поиск совпадений с ключевыми словами.
		Value = 0;
		while (Value < _keywordCount &&
			strcmp(Identifier, _keywordTable[Value].Identifier) != 0) // TODO Заменить на нормальные строки.
			Value++;
		// Определение типа идентификатора.
		if (Value < _keywordCount) {
			Type = _keywordTable[Value].Symbol; // Терминальный символ из таблицы языка.
		} else {
			Type = Symbol::Identifier; // Идентификатор считается нетерминальный символ.
		}
	}

	inline void ReadWhitespace() {
		Type = Symbol::Whitespace;
		Value = 0;
		do {
			Value++;
			_charToken.ReadChar();
		} while (_charToken.IsWhitespace());
	}

	inline void ReadDelimiter() {
		Type = Symbol::Delimiter;
		Value = (int)_charToken.Type;
		_charToken.ReadChar();
	}

	inline void ReadEndOfLine() {
		Type = Symbol::EndOfLine;
		Value = 0;
		do {
			Value++;
			_charToken.ReadChar();
		} while (_charToken.IsEndOfLine());
	}

	// Чтение целого числа.
	inline void ReadInteger() {
		Type = Symbol::Integer;
		Value = 0;
		do {
			if (Value <= (LONG_MAX - (long)_charToken.Type + (long)Char::Digit0) / 10) {
				Value = 10 * Value + (long)_charToken.Type - (long)Char::Digit0;
			} else if (Error != SymbolError::None) {
				SetError(SymbolError::NumberOverflow, "Not enough long size to store number.");
			}
			_charToken.ReadChar();
		} while (_charToken.IsDecimalDigit());
	}

	inline void ReadUnknown() {
		Type = Symbol::Unknown;
		_charToken.ReadChar();
	}

public:

	// Тип символа.
	Symbol Type;

	// Нужно реализовать потоки состояний и возможность использования на них объединений union или cast.
	// Язык не должен ограничивать размер чисел из-за архитектуры процессора.
	long Value; // Предполагается, что это и будет единственный поток состояний, хранящий значение лексемы.
	double Real; // [Obsolete] Значение числа с плавающей точкой.
	char Identifier[KEYWORD_ID_SIZE]; // [Obsolete] Значение идентификатора.

	// TODO Состояние очередной ошибки можно вынести в отдельный интерфейс.
	// TODO Но если здесь достаточно одного состояния, то в синтаксическом анализаторе это может быть несколько ошибок за итерацию.
	SymbolError Error; // Флаг наличия ошибки.
	long ErrorPosition; // Позиция в символьном потоке.
	long ErrorLine; // Строка с ошибкой.

	// Основной конструктор.
	SymbolToken(CharToken *charToken):
		_charToken(*charToken) {
		Type = Symbol::Unknown;
		Error = SymbolError::None;
		// TODO Это не токен в чистом виде, скорее надо переименовать в машину состояний.
		// TODO И передавать композицию интерфейсов CharToken и CharReader например.
		// TODO Но может быть если класс будет работать как дизассемблер, то и CharWriter.
		_charToken.ReadChar(); // Предпросмотр оптимизирует код.
		_keywordCount = 0;
	}

	virtual ~SymbolToken() {
	}

	// Добавление зарезервированного слова.
	void EnterKeyword(Symbol symbol, const char *name) {
		_keywordTable[_keywordCount].Symbol = symbol;
		memcpy(_keywordTable[_keywordCount].Identifier, name, strlen(name));
		_keywordCount++;
	}

	// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	// является ли для него состояние машины приемлемым для следующего шага.
	virtual void ReadToken() = 0;
};

#endif // SYMBOL_TOKEN_HPP
