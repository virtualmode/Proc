#pragma once

#ifndef PROC_SYMBOL_TOKEN_HPP
#define PROC_SYMBOL_TOKEN_HPP

#include "Temp/Dependency.h"

#include "SymbolToken.hpp"

// Лексический анализатор Proc.
class ProcSymbolToken: public SymbolToken {
private:

public:

	// Основной конструктор.
	// @param charToken Символьный поток.
	ProcSymbolToken(CharStream *charToken):
		SymbolToken(charToken) {
		EnterKeyword(Symbol::Class, "class");
		EnterKeyword(Symbol::Enumeration, "enum");
	}

	virtual ~ProcSymbolToken() {
	}

	// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	// является ли для него состояние машины приемлемым для следующего шага.
	virtual void ReadToken() {
		// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		if (_charToken.EndOfStream) {
			Type = Symbol::EndOfStream;
			return;
		}

		// В зависимости от текущего состояния необходимо определить следующую m-конфигурацию.
		if (IsIdentifierLetter(false)) {
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

#endif // PROC_SYMBOL_TOKEN_HPP
