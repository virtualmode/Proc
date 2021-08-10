#pragma once

#ifndef SYMBOL_ERROR_HPP
#define SYMBOL_ERROR_HPP

#include "Temp/Dependency.h"

// Ошибки лексического анализатора исходного кода.
// TODO Может быть этот анализатор не должен иметь состояния ошибки в будущем, но это неточно.
enum class SymbolError {
	None, // Нет ошибки.
	IdentifierOverflow, // Ошибка переполнения размера имени переменной.
	NumberOverflow, // Ошибка переполнения числовой переменной.
};

#endif // SYMBOL_ERROR_HPP
