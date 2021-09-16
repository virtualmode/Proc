#pragma once

#ifndef PROC_SYMBOL_HPP
#define PROC_SYMBOL_HPP

#include "Temp/Dependency.h"

#include "Symbol.hpp"

// Лексический анализатор Proc.
class ProcSymbol: public Symbol {
private:

public:

	// Основной конструктор.
	// @param charToken Символьный поток.
	ProcSymbol(CharStream *charToken):
		Symbol(charToken) {
		EnterKeyword(SymbolType::Class, "class");
		EnterKeyword(SymbolType::Enumeration, "enum");
	}

	virtual ~ProcSymbol() {
	}

	// Чтение очередной лексемы. Простейший шаг, определяющий следующий автомат.
	// Результат чтения не имеет значения, т.к. синтаксический анализатор сам решает,
	// является ли для него состояние машины приемлемым для следующего шага.
	virtual void ReadToken() {
		// Если нет возможности прочесть очередное состояние из потока, работа анализатора завершается.
		if (_charToken.EndOfStream) {
			Type = SymbolType::EndOfStream;
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

#endif // PROC_SYMBOL_HPP
