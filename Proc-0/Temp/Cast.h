#pragma once

#ifndef CAST_H
#define CAST_H

#include "Global.h"
#include "Type.h"

class Cast {
	public:

	static type Cast::type(const char *stdinput, const char *format);

	inline static ::size_t Cast::size_t(const char *value) { return (::size_t)Cast::type(value, "%llu").u64; } // Attempt to avoid definitions like this: return cast::type(value, SRC_CAST_FORMAT_SIZE_T).size_t;
	inline static u64 Cast::u64(const char *value) { return Cast::type(value, "%llu").u64; }
	inline static u32 Cast::u32(const char *value) { return Cast::type(value, "%u").u32; }
	inline static u16 Cast::u16(const char *value) { return Cast::type(value, "%hu").u16; }
	inline static u8 Cast::u8(const char *value) { return Cast::type(value, "%hhu").u8; }

	inline static ::ptrdiff_t Cast::ptrdiff_t(const char *value) { return (::ptrdiff_t)Cast::type(value, "%lld").s64; }
	inline static s64 Cast::s64(const char *value) { return Cast::type(value, "%lld").s64; }
	inline static s32 Cast::s32(const char *value) { return Cast::type(value, "%d").s32; }
	inline static s16 Cast::s16(const char *value) { return Cast::type(value, "%hd").s16; }
	inline static s8 Cast::s8(const char *value) { return Cast::type(value, "%hhd").s8; }

	inline static f80 Cast::f80(const char *value) { return Cast::type(value, "%Lf").f80; }
	inline static f64 Cast::f64(const char *value) { return Cast::type(value, "%lf").f64; }
	inline static f32 Cast::f32(const char *value) { return Cast::type(value, "%f").f32; }
	static bool Cast::bool_t(const char *value);

	// Conversion to std::string type. Empty string if error:
	static std::string Cast::string(const char *format, ...); //!< Like snprintf.
	inline static std::string Cast::string(::u64 value) { return Cast::string("%llu", value); }
	inline static std::string Cast::string(::u32 value) { return Cast::string("%u", value); }
	inline static std::string Cast::string(::u16 value) { return Cast::string("%hu", value); }
	inline static std::string Cast::string(::u8 value) { return Cast::string("%hhu", value); }
	inline static std::string Cast::string(::s64 value) { return Cast::string("%lld", value); }
	inline static std::string Cast::string(::s32 value) { return Cast::string("%d", value); }
	inline static std::string Cast::string(::s16 value) { return Cast::string("%hd", value); }
	inline static std::string Cast::string(::s8 value) { return Cast::string("%hhd", value); }
	inline static std::string Cast::string(::f80 value) { return Cast::string("%Lf", value); }
	inline static std::string Cast::string(::f64 value) { return Cast::string("%lf", value); }
	inline static std::string Cast::string(::f32 value) { return Cast::string("%f", value); }
	inline static std::string Cast::string(bool value) { return value ? std::string("1") : std::string("0"); }

	// Сложные преобразования:
	static int hexToDec(char hexChar); //!< Преобразование шестнадцатиричного символа в код.
	static int hexToDec(const char *hexString, ::size_t length); //!< Преобразование шестнадцатиричного кода известной длины в десятичное число.
	inline static int hexToDec(const char *hexString) { return hexToDec(hexString, strlen(hexString)); } //!< Преобразование строки с шестнадцатиричным кодом в десятичное число.
	static short decToHex(char dec); // Эти два байта можно использовать как строку из двух шестнадцатиричных символов без терминирующего символа.
};


#endif
