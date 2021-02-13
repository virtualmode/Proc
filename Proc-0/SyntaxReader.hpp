#pragma once

#ifndef SYNTAX_READER_H
#define SYNTAX_READER_H

class SyntaxReader {
public:

	// Чтение очередной конструкции.
	// Вообще парсер видимо за один вызов должен всё обработать.
	// Причем верхнем узлом будет модуль/листинг.
	// Мне кажется Parse() все равно надо разбить на шаги.
	// С другой стороны в отличае от чтения лексем, разбор
	// синтаксиса уже нелинейный процесс.
	// @return Количество успешно прочтённых TODO.
	virtual int ReadSyntax() = 0;

	virtual void ReadBody() = 0;
	virtual void ReadDefinition() = 0;
};

#endif // SYNTAX_READER_H
