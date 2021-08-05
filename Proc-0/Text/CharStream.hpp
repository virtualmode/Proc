#pragma once

#ifndef CHAR_STREAM_HPP
#define CHAR_STREAM_HPP

#include "Char.hpp"
#include "CharReader.hpp"
#include "CharWriter.hpp"
#include "CharSeeker.hpp"

// Интерфейс потока символов для работы с текстом.
// TODO CharReader и CharWriter должны использоваться независимо.
// TODO Необходимо добавить в язык возможность композиции интерфейсов.
// TODO А пока придётся наследовать с другими необходимыми интерфейсами.
// TODO После реализации композиции данный класс не будет иметь смысла.
class CharStream: public Char, public CharReader, public CharWriter, public CharSeeker {
};

#endif // CHAR_STREAM_HPP
