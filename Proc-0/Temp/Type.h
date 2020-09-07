#pragma once

#ifndef TYPE_H
#define TYPE_H

#include "Global.h"

// Тип base под вопросом. Вполне хватит типа object. Он более привычен.
//#define base char*

// Переменная, указывающая на объект и база должны быть размерности указателя для архитектуры,
// или безразмерного (целого). Указатель очень для этого подходит. IntPtr, IntObj, pointer, object, base.
// Базовый "безразмерный" тип для всех объектов, чисел, структур, enum'ов и прочей фигни.
// Этот тип будет реализовывать простейшие операции над любым объектом, скорее всего
// просто адресация и счёт. В данном языке это будет база - количество состояний информации.
// Счёт - количество состояний (если база), степень (если индекс), короче просто число.
// С указателем сложнее, тоже число, но придется его скрыть от программиста. А операции
// производить через cast степенями базы.
// Тоже самое, что и ptrdiff_t.
//#define object char*
#define object ptrdiff_t

#define bool int
#define false 0
#define true 1


// Under C convention (such as in the C standard library), types declared with typedef end with '_t' (e.g., size_t, time_t). But we use without '_t'.
// The purpose of typedef is to assign ALTERNATIVE names to existing types. You are not actually creating a new data type, but rather defining a new name for an existing type.

// Unsigned integer types:
typedef unsigned char u8; //!< 1 byte from 0 to 255 (char, bool).
typedef unsigned short u16; //!< 2 bytes from 0 to 65,535 (short).
typedef unsigned int u32; //!< 4 bytes from 0 to 4,294,967,295 (int, long).
typedef unsigned long long u64; //!< 8 bytes from 0 to 18,446,744,073,709,551,615 (long long).
//typedef u64 ul; //!< Largest supported unsigned type.

// Signed integer types:
typedef signed char s8; //!< 1 bytes from –128 to 127.
typedef signed short s16; //!< 2 bytes from –32,768 to 32,767.
typedef signed int s32; //!< 4 bytes from –2,147,483,648 to 2,147,483,647.
typedef signed long long s64; //!< 8 bytes from –9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
//typedef s64 sl; //!< Largest supported signed type.

// Floating point types:
typedef float f32;
typedef double f64;
typedef long double f80; // Rare.

union type {
	bool type::bool_t;
	u8 type::u8;
	u16 type::u16;
	u32 type::u32;
	u64 type::u64;
	s8 type::s8;
	s16 type::s16;
	s32 type::s32;
	s64 type::s64;
	f32 type::f32;
	f64 type::f64;
	f80 type::f80;
	::size_t type::size_t;
	::ptrdiff_t type::ptrdiff_t;
};


#endif
