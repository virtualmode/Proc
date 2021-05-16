#pragma once

#ifndef SYMBOL_TOKEN_HPP
#define SYMBOL_TOKEN_HPP

#include "Temp/Dependency.h"

#include "Char.hpp"
#include "CharToken.hpp"
#include "Symbol.hpp"
#include "SymbolError.hpp"

/*
	4. Первичная обработка исходного кода для компилятора или интерпретатора начинается с лексического анализа. Есть
	несколько способов реализации: обычная реализация, интерпретатор БНФ или регулярных выражений, компилятор
	анализаторов типа Lex. Для базовых языков подойдёт первый вариант, как самый простой и производительный.
	Если рассмотреть вообще любые данные, то при их первичной обработке происходит лексический анализ по сути, но место
	лексем могут занимать специфические конструкции: состояния, символы, цвета, заголовки, звуковые сэмплы и прочее.
	Чтение этих конструкций из потоков, запись и другие операции можно представить как часть одного и того же процесса.
	Такие классы задач можно выделить суффиксами в соответствии от их назначения, например Reader, Writer или Seeker.
*/

// Лексический анализатор исходного кода. Машина состояний. Конечный автомат.
// В других источниках можно встретить варианты: lexical analyzer, lexer, tokenizer, scanner, token reader.
// TODO Анализатор работает с Юникод текстом и наверное максимум может быть совместим с подобными кодировками,
// TODO но есть ли смысл так делать, непонятно. Типа это UnicodeLexer и должен работать только с Юникодом.
// TODO Если потребуется работать с другими источниками исходников, то для них должен быть написан свой анализатор.

// Лексический анализатор исходного кода, машина состояний, конечный автомат.
// В других источниках можно встретить варианты: lexical analyzer, lexer, tokenizer, scanner, token reader.
// Теоретически он должен быть написан для каждой поддерживаемой кодировки.
// При чтении одного и того же набора символов в разных кодировках все реализации должны возвращать одинаковую лексему.
// Набор лексем избавляет от необходимости создавать реализацию синтаксического анализатора для каждой кодировки.
// Но если и текстовые потоки представить аналогичным образом, одного лексического анализатора также будет достаточно.
class SymbolToken {
private:

	CharToken &_charToken;

	// Перевод машины в состояние ошибки.
	void SetError(SymbolError error, const char *message) {
		Error = error;
		ErrorPosition = _charToken.Position;
		ErrorLine = _charToken.Line;
	}

	inline void ReadIdentifier() {
		Type = Symbol::Identifier;
		//Value = 0;
		do {
			//Value++;
			_charToken.ReadChar();
		} while (_charToken.IsLatinLetter());

		/*int i, k;
		i = 0;
		do { // Считывание всего идентификатора:
			if (i < IDLEN) {
				id[i] = ch;
				i++;
			}
			chRead();
		} while (!(ch < '0' || ch > '9' && toupper(ch) < 'A' || toupper(ch) > 'Z')); // TODO Оригинал.
		id[i] = 0; // Терминальный ноль.
		k = 0;
		while (k < nkw && strcmp(id, keyTab[k].id) != 0) {
			k++; // Поиск совпадений с ключевыми словами.
		}
		// Определение типа идентификатора:
		if (k < nkw) {
			sym = keyTab[k].sym; // Терминальный символ из таблицы языка.
		} else {
			sym = IDENT; // Идентификатор - нетерминальный символ.
		}*/
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
				SetError(SymbolError::NumberOverflow, "Not enought long size to store number.");
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
	}

	virtual ~SymbolToken() {
	}

	void AddTerminal() {
		
	}

	// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	// является ли для него состояние машины приемлемым для следующего шага.
	void ReadToken() {
		// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		if (_charToken.EndOfStream) {
			Type = Symbol::EndOfStream;
			return;
		}

		// В зависимости от текущего состояния необходимо определить следующую m-конфигурацию.
		if (_charToken.IsLatinLetter() ||
			_charToken.Type == Char::Underline) {
			ReadIdentifier();
		} else if (_charToken.IsWhitespace()) {
			ReadWhitespace();
		} else if (_charToken.IsDelimiter()) {
			ReadDelimiter();
		} else if (_charToken.IsEndOfLine()) {
			ReadEndOfLine();
		} else if (_charToken.IsDecimalDigit()) {
			ReadInteger();
		} else {
			ReadUnknown();
		}
	}
};

#endif // SYMBOL_TOKEN_HPP
