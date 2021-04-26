#pragma once

#ifndef SOURCE_TOKEN_HPP
#define SOURCE_TOKEN_HPP

#include "Temp/Dependency.h"

#include "Char.hpp"
#include "CharToken.hpp"
#include "SymbolType.hpp"

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
class SourceToken {

private:

	CharToken &_charToken;

	inline void ReadWhitespace() {
		Type = SymbolType::Whitespace;
		Number = 0;
		do {
			Number++;
			_charToken.ReadChar();
		} while (_charToken.IsWhitespace());
	}

	inline void ReadEndOfLine() {
		Type = SymbolType::EndOfLine;
		Number = 0;
		do {
			Number++;
			_charToken.ReadChar();
		} while (_charToken.IsEndOfLine());
	}

	inline void ReadDelimiter() {
		_charToken.ReadChar();
	}

	inline void ReadInteger() {

	}

	inline void ReadWord() {

	}

	/*inline void ReadUnknown() {
		Type = SymbolType::Unknown;
		Number = 0;
		do {
			Number++;
			_charToken.ReadChar();
		} while (_charToken.Value == Char::Unknown);
	}*/

public:

	// Тип символа.
	SymbolType Type;

	// Нужно реализовать потоки состояний и возможность использования на них объединений union или cast.
	char Value[128]; // Предполагается, что это и будет единственный поток состояний, хранящий значение лексемы.
	// Язык не должен ограничивать размер чисел из-за архитектуры процессора.
	int Symbol; // [Obsolete] Текущий код символа Юникода.
	long Number; // [Obsolete] Значение целого числа.
	double Real; // [Obsolete] Значение числа с плавающей точкой.

	// Основной конструктор.
	SourceToken(CharToken *charToken): _charToken(*charToken) {
		// TODO Это не токен в чистом виде, скорее надо переименовать в машину состояний.
		// TODO И передавать композицию интерфейсов CharToken и CharReader например.
		// TODO Но может быть если класс будет работать как дизассемблер, то и CharWriter.
		_charToken.ReadChar(); // Предпросмотр оптимизирует код.
		Type = SymbolType::Unknown;
	}

	virtual ~SourceToken() {
	}

	// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	// является ли для него состояние машины приемлемым для следующего шага.
	void ReadToken() {
		// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		if (_charToken.EndOfStream) {
			Type = SymbolType::EndOfStream;
			return;
		}

		// В зависимости от текущего состояния необходимо определить следующую m-конфигурацию.
		if (_charToken.IsWhitespace()) {
			ReadWhitespace();
		} else if (_charToken.IsEndOfLine()) {
			ReadEndOfLine();
		} else if (_charToken.IsDelimiter()) {
			ReadDelimiter();
		} else if (_charToken.IsDecimalDigit()) {
			ReadInteger();
		} else if (_charToken.IsLatinLetter()) {
			ReadWord();
		} else {
			_charToken.ReadChar();
			//ReadUnknown();
		}
	}
};

#endif // SOURCE_TOKEN_HPP
