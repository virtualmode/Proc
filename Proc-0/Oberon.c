// Учебная реализация Оберона-0.
// Набор конечных вложенных машин состояний, использующих стек, и являющихся бесконечным магазинным автоматом.

// Внешние заголовочные файлы:
#include <stdio.h>
#include <limits.h>
#include <malloc.h> // malloc.
#include <string.h> // memset.


//######################################################################################################################
//#                                                Вспомогательный код                                                 #
//######################################################################################################################

// C не хочет использовать свои константы в инициализации массивов, поэтому придется использовать препроцессор:
#define IDLEN 16
#define KW 34
#define MAXCODE 1000
#define NOFCOM 16

// Константы лексического анализатора:
const char _NULL = 0, TIMES = 1, _DIV = 3, _MOD = 4, AND = 5, PLUS = 6, MINUS = 7, OR = 8, EQL = 9,
	NEQ = 10, LSS = 11, GEQ = 12, LEQ = 13, GTR = 14, PERIOD = 18, COMMA = 19, COLON = 20, RPAREN = 22, RBRAK = 23,
	OF = 25, THEN = 26, DO = 27, LPAREN = 29, LBRAK = 30, NOT = 32, BECOMES = 33, NUMBER = 34, IDENT = 37,
	SEMICOLON = 38, END = 40, ELSE = 41, ELSIF = 42, IF = 44, WHILE = 46, _ARRAY = 54, _RECORD = 55, _CONST = 57,
	TYPE = 58, _VAR = 59, PROCEDURE = 60, BEGIN = 61, MODULE = 63, _EOF = 64;

// Константы генератора кода:
const int WORDSIZE = 4, MAXREL = 200;
// Class/mode:
const char HEAD = 0, VAR = 1, PAR = 2, CONST = 3, FLD = 4, TYP = 5, PROC = 6, SPROC = 7, REG = 10, COND = 11;
// Form:
const char BOOLEAN = 0, INTEGER = 1, ARRAY = 2, RECORD = 3;
// Opcodes:
const char MOV = 0, MVN = 1, ADD = 2, SUB = 3, MUL = 4, DIV = 5, MOD = 6, CMP = 7, MOVI = 16, MVNI = 17, ADDI = 18,
	SUBI = 19, MULI = 20, DIVI = 21, MODI = 22, CMPI = 23, CHKI = 24, LDW = 32, LDB = 33, POP = 34, STW = 36, STB = 37,
	PSH = 38, RD = 40, WRD = 41, WRH = 42, WRL = 43, BEQ = 48, BNE = 49, BLT = 50, BGE = 51, BLE = 52, BGT = 53,
	BR = 56, BSR = 57, RET = 58, FP = 12, SP = 13, LNK = 14, PC = 15; // Reserved registers.

const long RISC_MEMSIZE = 1024; // Просто константа объема памяти в попугаях.

// Вспомогательные типы данных:
typedef int bool;
#define FALSE 0
#define TRUE 1

typedef char Identf[IDLEN];

struct KeyTab {
	int sym;
	char id[12];
};

// Объект с описанием типа данных.
struct TypeDesc {
	int form, // Элементарные типы: INTEGER, BOOLEAN, ARRAY, RECORD (описывается через список типов).
		size, // Размер элементарного типа, определяемого архитектурой.
		len; // Длина массива.
	void *fields; // Поля для записи.
	struct TypeDesc *base; // Элемент массива.
};

// Объект для хранения объявлений.
struct ObjDesc {
	int class, lev; // Класс объекта: переменная, константа, тип, процедура; уровень объявления, например в параметрах процедуры.
	struct ObjDesc *next, *dsc; // Следующее объявление текущего уровня; ссылка на первый элемент вложенного уровня.
	struct TypeDesc *type; // Ссылка на описанее типа объявления.
	Identf name; // Имя объявления.
	long val; // Значение.
};

// Атрибут синтаксически сворачиваемых символов.
struct Item {
	// Атрибут-режим соответствует режиму адресации команд компьютера, а диапазон его значений зависит от множества режимов адресации целевого компьютера.
	int mode, // Режим для множителя, слагаемого, или выражения, т.е. определение где хранится его значение и как к нему обратиться.
		lev;
	struct TypeDesc *type; // Атрибутом элемента также является его тип.
	long a, // Режим Var, класс Var, значение по адресу a. Режим Const, класс Const, значение есть константа a.
		b,
		c,
		r; // Режим Reg, класса нет, значение содержится в регистре R[r].
};

// Глобальные переменные лексического анализатора:
long val;
Identf id; // Текстовое представление текущего разобранного идентификатора.
bool error; // Флаг ошибки BOOL.
long errpos;
char ch; // Текущий символ, прочитанный лексическим анализатором.
int nkw;
struct KeyTab keyTab[KW];
FILE *readerOss, // Исходный код.
	*writerOut; // Файл с выходной информацией.

// Глобальные переменные синтаксического анализатора:
int sym; // Тип текущей разобранной терминальной последовательности.
bool loaded;
struct ObjDesc *topScope, *universe, *guard;

// Глобальные переменные генератора кода:
struct TypeDesc *boolType, *intType;
int curlev, pc, cno;
long entry, fixlist;
char regs[64]; // Множество используемых регистров.
FILE *writerOsg; // Целевой код.
long code[MAXCODE], comadr[NOFCOM];
Identf comname[NOFCOM]; // Команды.
char mnemo[64][5]; // Для декодера.

// Заглушки для обероновских процедур и функций.
extern inline char ORD(char character) {
	return character;
}

// Проверка принадлежности множеству регистров.
extern inline bool IN(char *regs, char reg) {
	if (regs[reg] == 0)
		return FALSE;
	else
		return TRUE;
}

// Добавить значение во множество.
extern inline void INCL(char *regs, char reg) {
	regs[reg] = 1;
}

// Исключить значение из множества.
extern inline void EXCL(char *regs, char reg) {
	regs[reg] = 0;
}

// Возвращает значение x = x * 2^n функции.
long ASH(long x, long n) {
	int i = 0;
	long pow = 1;
	for (i = 0; i < n; i++) {
		pow *= 2;
	}
	return x * pow;
}

// Проверка на нечётность.
extern inline bool ODD(long x) {
	return x % 2 == 1;
}

// Считывает очередной символ из файла.
extern inline void chRead() {
	fread(&ch, sizeof(char), 1, readerOss);
}


//######################################################################################################################
//#                                        Лексический анализатор OSS (сканер)                                         #
//######################################################################################################################

// Вывод ошибки в выходной файл.
void Mark(const char *msg) {
	long p = ftell(readerOss) - 1;
	if (p > errpos) {
		fprintf(writerOut, "Problem at position (%u): %s\n", p, msg);
	}
	errpos = p;
	error = TRUE;
}

// Когда машина состояний (автомат) читает очередной символ и получает букву,
// то переходит в состояние определения идентификатора или терминального символа.
void Ident() {
	int i, k;
	i = 0;
	do { // Считывание всего идентификатора:
		if (i < IDLEN) {
			id[i] = ch;
			i++;
		}
		chRead();
	} while (!(ch < '0' || ch > '9' && toupper(ch) < 'A' || toupper(ch) > 'Z')); // TODO Оригинал.
	id[i] = 0;
	k = 0;
	while (k < nkw && strcmp(id, keyTab[k].id) != 0) {
		k++; // Поиск совпадений с ключевыми словами.
	}
	// Определение типа идентификатора:
	if (k < nkw) {
		sym = keyTab[k].sym; // Терминальный символ из таблицы языка.
	} else {
		sym = IDENT; // Идентификатор - нетерминальный символ.
	}
}

// Считывание целого числа.
void Number() {
	val = 0;
	sym = NUMBER;
	do {
		if (val <= (LONG_MAX - ORD(ch) + ORD('0')) / 10) {
			val = 10 * val + (ORD(ch) - ORD('0'));
		} else {
			Mark("too big number.");
			val = 0;
		}
		chRead();
	} while (!(ch < '0' || ch > '9'));
}

void Comment() {
	chRead();
	while (TRUE) {
		while (TRUE) {
			while (ch == '(') {
				chRead();
				if (ch == '*')
					Comment();
			}
			if (ch == '*') {
				chRead();
				break;
			}
			if (feof(readerOss)) {
				break;
			}
			chRead();
		}
		if (ch == ')') {
			chRead();
			break;
		}
		if (feof(readerOss)) {
			Mark("complete the comment.");
			break;
		}
	}
}

// Основная машина состояний лексического анализатора, выполняющая простейший шаг и определяющая следующий автомат.
void Get() {
	// Пропуск пробелов, табуляций, перевода каретки, новой строки и других непонятных знаков:
	while (!feof(readerOss) && ch <= ' ') {
		chRead();
	}
	// Проверка на конец файла:
	if (feof(readerOss)) {
		sym = _EOF;
	} else { // Переход к следующему состоянию:
		switch (ch) {
			case '&': chRead(); sym = AND; break;
			case '*': chRead(); sym = TIMES; break;
			case '+': chRead(); sym = PLUS; break;
			case '-': chRead(); sym = MINUS; break;
			case '=': chRead(); sym = EQL; break;
			case '#': chRead(); sym = NEQ; break;
			case '<': chRead();
				if (ch == '=') {
					chRead();
					sym = LEQ;
				} else {
					sym = LSS;
				}
				break;
			case '>': chRead();
				if (ch == '=') {
					chRead();
					sym = GEQ;
				} else {
					sym = GTR;
				}
				break;
			case ';': chRead(); sym = SEMICOLON; break;
			case ',': chRead(); sym = COMMA; break;
			case ':':
				chRead();
				if (ch == '=') {
					chRead();
					sym = BECOMES;
				} else {
					sym = COLON;
				}
				break;
			case '.': chRead(); sym = PERIOD; break;
			case '(':
				chRead();
				if (ch == '*') {
					Comment();
					Get();
				} else {
					sym = LPAREN;
				}
				break;
			case ')': chRead(); sym = RPAREN; break;
			case '[': chRead(); sym = LBRAK; break;
			case ']': chRead(); sym = RBRAK; break;
			default:
				if (ch >= '0' && ch <= '9') {
					Number();
				} else if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') {
					Ident();
				} else if (ch == '~') {
					chRead();
					sym = NOT;
				} else {
					chRead();
					sym = _NULL;
				}
				break;
		}
	}
}

void EnterKW(int sym, const char *name) {
	keyTab[nkw].sym = sym;
	memcpy(keyTab[nkw].id, name, strlen(name));
	nkw++;
}

// В оригинале код находится в глобальной области модуля OSS:
void Oss(const char *fileName) {
	nkw = 0;
	error = TRUE;
	writerOut = fopen(fileName, "w");
	if (writerOut == NULL)
		return;
	
	EnterKW(    _NULL, "BY");
	EnterKW(       DO, "DO");
	EnterKW(       IF, "IF");
	EnterKW(    _NULL, "IN");
	EnterKW(    _NULL, "IS");
	EnterKW(       OF, "OF");
	EnterKW(       OR, "OR");
	EnterKW(    _NULL, "TO");
	EnterKW(      END, "END");
	EnterKW(    _NULL, "FOR");
	EnterKW(     _MOD, "MOD");
	EnterKW(    _NULL, "NIL");
	EnterKW(     _VAR, "VAR");
	EnterKW(    _NULL, "CASE");
	EnterKW(     ELSE, "ELSE");
	EnterKW(    _NULL, "EXIT");
	EnterKW(     THEN, "THEN");
	EnterKW(     TYPE, "TYPE");
	EnterKW(    _NULL, "WITH");
	EnterKW(   _ARRAY, "ARRAY");
	EnterKW(    BEGIN, "BEGIN");
	EnterKW(   _CONST, "CONST");
	EnterKW(    ELSIF, "ELSIF");
	EnterKW(    _NULL, "IMPORT");
	EnterKW(    _NULL, "UNTIL");
	EnterKW(    WHILE, "WHILE");
	EnterKW(  _RECORD, "RECORD");
	EnterKW(    _NULL, "REPEAT");
	EnterKW(    _NULL, "RETURN");
	EnterKW(    _NULL, "POINTER");
	EnterKW(PROCEDURE, "PROCEDURE");
	EnterKW(     _DIV, "DIV");
	EnterKW(    _NULL, "LOOP");
	EnterKW(   MODULE, "MODULE");
}

void OssInit(const char *fileName, long pos) {
	readerOss = fopen(fileName, "rb");
	if (readerOss == NULL)
	{
		errpos = 0;
		error = TRUE;
		printf("Can't open file: %s", fileName);
	} else {
		errpos = pos;
		error = FALSE;
		fseek(readerOss, pos, SEEK_SET);
		chRead();
		Oss("oberon.out"); // Отладочная информация.
	}
}


//######################################################################################################################
//#                                             Синтаксический анализатор                                              #
//######################################################################################################################

// Создание нового объекта:
struct ObjDesc *objNew() {
	struct ObjDesc *result = (struct ObjDesc *)malloc(sizeof(struct ObjDesc));
	memset(result, 0, sizeof(struct ObjDesc));
	return result;
}

// Сравнение объектов.
extern inline bool objEql(struct ObjDesc *a, struct ObjDesc *b) {
	if (memcmp(a, b, sizeof(struct ObjDesc)) == 0)
		return TRUE;
	else
		return FALSE;
}

// Копирование объектов.
extern inline void objCpy(struct ObjDesc *a, struct ObjDesc *b) {
	memcpy(a, b, sizeof(struct ObjDesc));
}

// Копирование идентификатора, которые уже являются указателями.
extern inline void idCpy(Identf a, Identf b) {
	memcpy(a, b, sizeof(char) * IDLEN);
}

// Создание объекта типа.
struct TypeDesc *typeNew() {
	struct TypeDesc *result = (struct TypeDesc *)malloc(sizeof(struct TypeDesc));
	memset(result, 0, sizeof(struct TypeDesc));
	return result;
}

// Создание нового элемента:
struct Item *itemNew() {
	struct Item *result = (struct Item *)malloc(sizeof(struct Item));
	memset(result, 0, sizeof(struct Item));
	return result;
}

struct ObjDesc *NewObj(int class) {
	struct ObjDesc *newObj, *x;
	x = topScope;
	idCpy(guard->name, id);
	while (strcmp(x->next->name, id) != 0) {
		x = x->next;
	}
	if (objEql(x->next, guard)) {
		newObj = objNew();
		idCpy(newObj->name, id);
		newObj->class = class;
		newObj->next = guard;
		x->next = newObj;
		return newObj;
	} else {
		Mark("redefinition.");
		return x->next;
	}
}

struct ObjDesc *Find() {
	struct ObjDesc *s, *x;
	s = topScope;
	memcpy(guard->name, id, sizeof(char) * IDLEN);
	while (TRUE) {
		x = s->next;
		while(strcmp(x->name, id) != 0) {
			x = x->next;
		}
		if (!objEql(x, guard)) {
			return x;
		}
		if (objEql(s, universe)) {
			Mark("undefined.");
			return x;
		}
		s = s->dsc;
	}
}

struct ObjDesc *FindField(struct ObjDesc *list) {
	idCpy(guard->name, id);
	while (strcmp(list->name, id) != 0) {
		list = list->next;
	}
	return list;
}

bool IsParam(struct ObjDesc *obj) {
	return obj->class == PAR || obj->class == VAR && obj->val > 0;
}

void OpenScope() {
	struct ObjDesc *s = objNew();
	s->class = HEAD;
	s->dsc = topScope;
	s->next = guard;
	topScope = s;
}

void CloseScope() {
	topScope = topScope->dsc;
}

// Parser.
void Field(struct Item *x, struct ObjDesc *obj);
void Index(struct Item *x, struct Item *y);
struct Item *Expression();

void Selector(struct Item *x) {
	struct Item *y;
	struct ObjDesc *obj;
	while (sym == LBRAK || sym == PERIOD) {
		if (sym == LBRAK) {
			Get();
			y = Expression();
			if (x->type->form == ARRAY) {
				Index(x, y);
			} else {
				Mark("isn't an array.");
			}
			if (sym == RBRAK) {
				Get();
			} else {
				Mark("] ?");
			}
		} else {
			Get();
			if (sym == IDENT) {
				if (x->type->form == RECORD) {
					obj = FindField(x->type->fields);
					Get();
					if (!objEql(obj, guard)) {
						Field(x, obj);
					} else {
						Mark("undefined.");
					}
				} else {
					Mark("isn't a record.");
				}
			} else {
				Mark("isn't an identifier.");
			}
		}
	}
}

struct Item *MakeItem(struct ObjDesc *obj);
struct Item *MakeConstItem(struct TypeDesc *typ, long val);
void Op1(int op, struct Item *x);
void Op2(int op, struct Item *x, struct Item *y);

struct Item *Factor() {
	struct Item *x;
	struct ObjDesc *obj;
	if (sym < LPAREN) {
		Mark("is an identifier?");
		do {
			Get();
		} while (!(sym >= LPAREN));
	}
	if (sym == IDENT) {
		obj = Find();
		Get();
		x = MakeItem(obj);
		Selector(x);
	} else if (sym == NUMBER) {
		x = MakeConstItem(intType, val);
		Get();
	} else if (sym == LPAREN) {
		Get();
		x = Expression();
		if (sym == RPAREN) {
			Get();
		} else {
			Mark(") ?");
		}
	} else if (sym == NOT) {
		Get();
		x = Factor();
		Op1(NOT, x);
	} else {
		Mark("is a factor?");
		x = MakeItem(guard);
	}

	return x;
}

struct Item *Term() {
	struct Item *x, *y;
	int op;
	x = Factor();
	while (sym >= TIMES && sym <= AND) {
		op = sym;
		Get();
		if (op == AND) {
			Op1(op, x);
		}
		y = Factor();
		Op2(op, x, y);
	}

	return x;
}

struct Item *SimpleExpression() {
	struct Item *x, *y;
	int op;
	if (sym == PLUS) {
		Get();
		x = Term();
	} else if (sym == MINUS) {
		Get();
		x = Term();
		Op1(MINUS, x);
	} else {
		x = Term();
	}
	while (sym >= PLUS && sym <= OR) {
		op = sym;
		Get();
		if (op == OR) {
			Op1(op, x);
		}
		y = Term();
		Op2(op, x, y);
	}

	return x;
}

void Relation(int op, struct Item *x, struct Item *y);

struct Item *Expression() {
	struct Item *x, *y;
	int op;
	x = SimpleExpression();
	if (sym >= EQL && sym <= GTR) {
		op = sym;
		Get();
		y = SimpleExpression();
		Relation(op, x, y);
	}

	return x;
}

void OsgParameter(struct Item *x, struct TypeDesc *ftyp, int class);

void Parameter(struct ObjDesc *fp) {
	struct Item *x;
	x = Expression();
	if (IsParam(fp)) {
		OsgParameter(x, fp->type, fp->class);
		fp = fp->next;
	} else {
		Mark("too many arguments.");
	}
}

void Param(struct Item *x) {
	if (sym == LPAREN) {
		Get();
	} else {
		Mark(") ?");
	}
	x = Expression();
	if (sym == RPAREN) {
		Get();
	} else {
		Mark(") ?");
	}
}

void Store(struct Item *x, struct Item *y);
void Call(struct Item *x);
void IoCall(struct Item *x, struct Item *y);
void CJump(struct Item *x);
void FJump(long l);
void FixLink(long l);
void BJump(long l);

void StatSequence() {
	struct ObjDesc *par, *obj;
	struct Item *x, *y;
	long l;
	while (TRUE) { // Синхронизация.
		obj = guard;
		if (sym < IDENT) {
			Mark("is an operator?");
			do {
				Get();
			} while (!(sym >= IDENT));
		}
		if (sym == IDENT) {
			obj = Find();
			Get();
			x = MakeItem(obj);
			Selector(x);
			if (sym == BECOMES) {
				Get();
				y = Expression();
				Store(x, y);
			} else if (sym == EQL) {
				Mark(":= ?");
				Get();
				y = Expression();
			} else if (x->mode == PROC) {
				par = obj->dsc;
				if (sym == LPAREN) {
					Get();
					if (sym == RPAREN) {
						Get();
					} else {
						while (TRUE) {
							Parameter(par);
							if (sym == COMMA) {
								Get();
							} else if (sym == RPAREN) {
								Get();
								break;
							} else if (sym >= SEMICOLON) {
								break;
							} else {
								Mark(") or , ?");
							}
						}
					}
				}
				if (obj->val < 0) {
					Mark("call ahead.");
				} else if (!IsParam(par)) {
					Call(x);
				} else {
					Mark("too less arguments.");
				}
			} else if (x->mode == SPROC) {
				if (obj->val <= 3) {
					Param(y);
				}
				IoCall(x, y);
			} else if (obj->class == TYP) {
				Mark("wrong operator?");
			} else {
				Mark("is an operator?");
			}
		} else if (sym == IF) {
			Get();
			x = Expression();
			CJump(x);
			if (sym == THEN) {
				Get();
			} else {
				Mark("THEN?");
			}
			StatSequence();
			l = 0;
			while (sym == ELSIF) {
				Get();
				FJump(l);
				FixLink(x->a);
				x = Expression();
				CJump(x);
				if (sym == THEN) {
					Get();
				} else {
					Mark("THEN?");
				}
				StatSequence();
			}
			if (sym == ELSE) {
				Get();
				FJump(l);
				FixLink(x->a);
				StatSequence();
			} else {
				FixLink(x->a);
			}
			FixLink(l);
			if (sym == END) {
				Get();
			} else {
				Mark("END?");
			}
		} else if (sym == WHILE) {
			Get();
			l = pc;
			x = Expression();
			CJump(x);
			if (sym == DO) {
				Get();
			} else {
				Mark("DO?");
			}
			StatSequence();
			BJump(l);
			FixLink(x->a);
			if (sym == END) {
				Get();
			} else {
				Mark("END?");
			}
		}
		if (sym == SEMICOLON) {
			Get();
		} else if (sym >= SEMICOLON && sym < IF || sym >= _ARRAY) {
			break;
		} else {
			Mark("; ?");
		}
	}
}

// Создание описателя объекта на основе класса.
struct ObjDesc *IdentList(int class) {
	struct ObjDesc *first = NULL, *obj;
	if (sym == IDENT) {
		first = NewObj(class);
		Get();
		while (sym == COMMA) {
			Get();
			if (sym == IDENT) {
				obj = NewObj(class);
				Get();
			} else {
				Mark("is an identifier?");
			}
		}
		if (sym == COLON) {
			Get();
		} else {
			Mark(": ?");
		}
	}

	return first;
}

// Создание описателя типа на основе состояния машины.
struct TypeDesc *Type() {
	struct ObjDesc *obj, *first;
	struct Item *x;
	struct TypeDesc *tp, *type;
	type = intType; // Синхронизация.
	if (sym != IDENT && sym < _ARRAY) {
		Mark("is a type?");
		do {
			Get();
		} while (!(sym == IDENT || sym >= _ARRAY));
	}
	if (sym == IDENT) {
		obj = Find();
		Get();
		if (obj->class == TYP) {
			type = obj->type;
		} else {
			Mark("is a type?");
		}
	} else if (sym == _ARRAY) {
		Get();
		x = Expression();
		if (x->mode != CONST || x->a < 0) {
			Mark("invalid index.");
		}
		if (sym == OF) {
			Get();
		} else {
			Mark("OF?");
		}
		tp = Type();
		type = typeNew();
		type->form = _ARRAY;
		type->base = tp;
		type->len = (int)x->a;
		type->size = type->len * tp->size;
	} else if (sym == _RECORD) {
		Get();
		type = typeNew();
		type->form = RECORD;
		type->size = 0;
		OpenScope();
		while (TRUE) {
			if (sym == IDENT) {
				first = IdentList(FLD);
				tp = Type();
				obj = first;
				while (!objEql(obj, guard)) {
					obj->type = tp;
					obj->val = type->size;
					type->size += obj->type->size;
					obj = obj->next;
				}
			}
			if (sym == SEMICOLON) {
				Get();
			} else if (sym == IDENT) {
				Mark("; ?");
			} else {
				break;
			}
		}
		type->fields = topScope->next;
		CloseScope();
		if (sym == END) {
			Get();
		} else {
			Mark("END?");
		}
	} else {
		Mark("is an identifier?");
	}

	return type;
}

void Declarations(long varsize) {
	struct ObjDesc *obj, *first;
	struct Item *x;
	struct TypeDesc *tp;
	long l;
	// Синхронизация:
	if (sym < _CONST && sym != END) {
		Mark("is a declaration?");
		do {
			Get();
		} while (!(sym >= _CONST || sym == END)); // Поиск терминала, который понимает компилятор.
	}
	while (TRUE) {
		if (sym == _CONST) {
			Get();
			while (sym == IDENT) {
				obj = NewObj(CONST);
				Get();
				if (sym == EQL) {
					Get();
				} else {
					Mark("= ?");
				}
				x = Expression();
				if (x->mode == CONST) {
					obj->val = x->a;
					obj->type = x->type;
				} else {
					Mark("expression is not a constant.");
				}
				if (sym == SEMICOLON) {
					Get();
				} else {
					Mark("; ?");
				}
			}
		}
		if (sym == TYPE) {
			Get();
			while (sym == IDENT) {
				obj = NewObj(TYP);
				Get();
				if (sym == EQL) {
					Get();
				} else {
					Mark("= ?");
				}
				obj->type = Type();
				if (sym == SEMICOLON) {
					Get();
					Mark("; ?");
				}
			}
		}
		if (sym == _VAR) {
			Get();
			while (sym == IDENT) {
				first = IdentList(VAR);
				tp = Type();
				obj = first;
				while (!objEql(obj, guard)) {
					obj->type = tp;
					obj->lev = curlev;
					varsize += obj->type->size;
					obj->val = -varsize;
					obj = obj->next;
				}
				if (sym == SEMICOLON) {
					Get();
				} else {
					Mark("; ?");
				}
			}
		}
		if (sym >= _CONST && sym <= _VAR) {
			Mark("is a declaration?");
		} else {
			break;
		}
	}
}

void FpSection(long *parblksize) {
	struct ObjDesc *obj, *first;
	struct TypeDesc *tp;
	long parsize;
	if (sym == VAR) {
		Get();
		first = IdentList(PAR);
	} else {
		first = IdentList(VAR);
	}
	if (sym == IDENT) {
		obj = Find();
		Get();
		if (obj->class == TYP) {
			tp = obj->type;
		} else {
			Mark("is an identifier?");
			tp = intType;
		}
	} else {
		Mark("is an identifier?");
		tp = intType;
	}
	if (first->class == VAR) {
		parsize = tp->size;
		if (tp->form >= ARRAY) {
			Mark("is not a record parameter.");
		}
	} else {
		parsize = WORDSIZE;
	}
	obj = first;
	while (!objEql(obj, guard)) {
		obj->type = tp;
		*parblksize = *parblksize + parsize;
		obj = obj->next;
	}
}

void IncLevel(int n);
void EnterCmd(Identf name);
void Enter(long size);
void Return(long size);

void ProcedureDecl() {
	const long marksize = 8;
	struct ObjDesc *proc, *obj;
	Identf procid;
	long locblksize, parblksize;
	Get();
	if (sym == IDENT) {
		idCpy(procid, id);
		proc = NewObj(PROC);
		Get();
		parblksize = marksize;
		IncLevel(1);
		OpenScope();
		proc->val = -1;
		if (sym == LPAREN) {
			Get();
			if (sym == RPAREN) {
				Get();
			} else {
				FpSection(&parblksize);
				while (sym == SEMICOLON) {
					Get();
					FpSection(&parblksize);
				}
				if (sym == RPAREN) {
					Get();
				} else {
					Mark(") ?");
				}
			}
		} else if (curlev == 1) {
			EnterCmd(procid);
		}
		obj = topScope->next;
		locblksize = parblksize;
		while (!objEql(obj, guard)) {
			obj->lev = curlev;
			if (obj->class == PAR) {
				locblksize -= WORDSIZE;
			} else {
				obj->val = locblksize;
				obj = obj->next;
			}
		}
		proc->dsc = topScope->next;
		if (sym == SEMICOLON) {
			Get();
		} else {
			Mark("; ?");
		}
		locblksize = 0;
		Declarations(locblksize);
		while (sym == PROCEDURE) {
			ProcedureDecl();
			if (sym == SEMICOLON) {
				Get();
			} else {
				Mark("; ?");
			}
		}
		proc->val = pc;
		Enter(locblksize);
		if (sym == BEGIN) {
			Get();
			StatSequence();
		}
		if (sym == END) {
			Get();
		} else {
			Mark("END?");
		}
		if (sym == IDENT) {
			if (strcmp(procid, id) != 0) {
				Mark("is not fit.");
			}
			Get();
		}
		Return(parblksize - marksize);
		CloseScope();
		IncLevel(-1);
	}
}

void Open();
void Header(long size);
// Для примера можно не использовать void Close(Identf s, long globals);

// Запуск процесса компиляции.
void Module() {
	Identf modid;
	long varsize;
	if (sym == MODULE) {
		Get(); // Считывание следующего нетерминала. Мы ожидаем там имя модуля.
		Open(); // Инициализация регистров.
		OpenScope();
		varsize = 0;
		if (sym == IDENT) {
			idCpy(modid, id);
			Get(); // Точка с запятой после идентификатора.
			fprintf(writerOut, "Compilation of '%s' module...\n\n", modid);
			// Лог Оберона: Texts.Append(Oberon.Log, W.buf);
		} else {
			Mark("is an identifier?");
		}
		if (sym == SEMICOLON) {
			Get();
		} else {
			Mark("; ?");
		}
		Declarations(varsize);
		while (sym == PROCEDURE) {
			ProcedureDecl();
			if (sym == SEMICOLON) {
				Get();
			} else {
				Mark("; ?");
			}
		}
		Header(varsize);
		if (sym == BEGIN) {
			Get();
			StatSequence();
		}
		if (sym == END) {
			Get();
		} else {
			Mark("END?");
		}
		if (sym == IDENT) {
			if (strcmp(modid, id) != 0) {
				Mark("is not fit.");
			}
			Get();
		} else {
			Mark("is an identifier?");
		}
		if (sym != PERIOD) {
			Mark(". ?");
		}
		CloseScope();
		if (!error) {
			// TODO Установка обработанного модуля idCpy(modid, s);
			// TODO Close(s, varsize);
			fprintf(writerOut, "Code has been generated %u\n", pc);
		}
	} else {
		Mark("MODULE?");
	}
}

void OspEnter(int cl, long n, Identf name, struct TypeDesc *type) {
	struct ObjDesc *obj;
	obj = objNew();
	obj->class = cl;
	obj->val = n;
	idCpy(obj->name, name);
	obj->type = type;
	obj->dsc = NULL;
	obj->next = topScope->next;
	topScope->next = obj;
}

void Osp() {
	fprintf(writerOut, "Oberon-0 compiler\n\n");
	guard = objNew();
	guard->class = VAR;
	guard->type = intType;
	guard->val = 0;
	topScope = NULL;
	OpenScope();
	OspEnter(TYP,   1, "BOOLEAN",  boolType);
	OspEnter(TYP,   2, "INTEGER",  intType);
	OspEnter(CONST, 1, "TRUE",     boolType);
	OspEnter(CONST, 0, "FALSE",    boolType);
	OspEnter(SPROC, 1, "Read",     NULL);
	OspEnter(SPROC, 2, "Write",    NULL);
	OspEnter(SPROC, 3, "WriteHex", NULL);
	OspEnter(SPROC, 4, "WriteLn",  NULL);
	universe = topScope;
}

void Osg(const char *writerFile);
void Decode();

// Основная функция инициализации и последующей компиляции кода.
void Compile(const char *fileName) {
	OssInit(fileName, 0);
	Osg("oberon.bin"); // Целевой код.
	Get(); // Первый запуск машины состояний, который считывает первый терминал. Он должен быть как минимум MODULE, чтобы листинг можно было считать программой.
	Osp();
	Module();
	Decode();

	fclose(readerOss);
	fclose(writerOut);
	fclose(writerOsg);
}


//######################################################################################################################
//#                                                  Генератор кода                                                    #
//######################################################################################################################

void GetReg(long r) {
	int i = 0;
	while (i < FP && IN(regs, i)) {
		i++;
	}
	INCL(regs, i);
	r = i;
}

void Put(long op, long a, long b, long c) {
	// Выдать команду:
	if (op >= 32) {
		op -=64;
	}
	code[pc] = ASH(ASH(ASH(op, 4) + a, 4) + b, 18) + (c % 262144); // 40000H.
	pc++;
}

void PutBr(long op, long disp) {
	// Выдать команду перехода:
	code[pc] = ASH(op - 64, 26) + (disp % 67108864); // 4000000H.
	pc++;
}

void TestRange(long x) {
	// 18-битное значение:
	if (x >= 131072 || x < -131072) {
		Mark("too big value.");
	}
}

void OsgLoad(struct Item *x) {
	long r;
	// x->mode != Reg.
	if (x->mode == VAR) {
		if (x->lev == 0) {
			x->a -= pc * 4;
		}
		GetReg(r);
		Put(LDW, r, x->r, x->a);
		EXCL(regs, x->r);
		x->r = r;
	} else if (x->mode == CONST) {
		TestRange(x->a);
		GetReg(x->r);
		Put(MOVI, x->r, 0, x->a);
	}
	x->mode = REG;
}

void LoadBool(struct Item *x) {
	if (x->type->form != BOOLEAN) {
		Mark("is a boolean?");
	}
	OsgLoad(x);
	x->mode = COND;
	x->a = 0;
	x->b = 0;
	x->c = 1;
}

void PutOp(long cd, struct Item *x, struct Item *y) {
	if (x->mode != REG) {
		OsgLoad(x);
	}
	if (y->mode == CONST) {
		TestRange(y->a);
		Put(cd + 16, x->r, x->r, y->a);
	} else {
		if (y->mode != REG) {
			OsgLoad(y);
		}
		Put(cd, x->r, x->r, y->r);
		EXCL(regs, y->r);
	}
}

long Negated(long cond) {
	if (ODD(cond)) {
		return cond - 1;
	} else {
		return cond + 1;
	}
}

long Merged(long l0, long l1) {
	long l2, l3;
	if (l0 != 0) {
		l2 = l0;
		while (TRUE) {
			l3 = code[l2] % 262144; // 40000H.
			if (l3 == 0) {
				break;
			}
			l2 = l3;
		}
		code[l2] -= l3 - l1;
		return l0;
	} else {
		return l1;
	}
}

void Fix(long at, long with) {
	code[at] = code[at] / 4194304 * 4194304 + (with % 4194304);
}

void FixWith(long l0, long l1) {
	long l2;
	while (l0 != 0) {
		l2 = code[l0] % 262144;
		Fix(l0, l1 - l0);
		l0 = l2;
	}
}

void FixLink(long l) {
	long l1;
	while (l != 0) {
		l1 = code[l] % 262144;
		Fix(l, pc - l);
		l = l1;
	}
}

// (*-----------------------*)

void IncLevel(int n) {
	curlev += n;
}

struct Item *MakeConstItem(struct TypeDesc *typ, long val) {
	struct Item *x = itemNew();
	x->mode = CONST;
	x->type = typ;
	x->a = val;

	return x;
}

struct Item *MakeItem(struct ObjDesc *y) {
	long r;
	struct Item *x = itemNew();
	x->mode = y->class;
	x->type = y->type;
	x->lev = y->lev;
	x->a = y->val;
	x->b = 0;
	if (y->lev == 0) {
		x->r = PC;
	} else if (y->lev == curlev) {
		x->r = FP;
	} else {
		Mark("level!");
		x->r = 0;
	}
	if (y->class == PAR) {
		GetReg(r);
		Put(LDW, r, x->r, x->a);
		x->mode = VAR;
		x->r = r;
		x->a = 0;
	}

	return x;
}

// (* x = x->y *)
void Field(struct Item *x, struct ObjDesc *y) {
	x->a += y->val;
	x->type = y->type;
}

// (* x = x[y] *)
void Index(struct Item *x, struct Item *y) {
	if (y->type != intType) {
		Mark("index is not an integer.");
	}
	if (y->mode == CONST) {
		if (y->a < 0 || y->a >= x->type->len) {
			Mark("wrong index.");
		}
		x->a += y->a * x->type->base->size;
	} else {
		if (y->mode != REG) {
			OsgLoad(y);
		}
		Put(CHKI, y->r, 0, x->type->len);
		Put(MULI, y->r, y->r, x->type->base->size);
		Put(ADD, y->r, x->r, y->r);
		EXCL(regs, x->r);
		x->r = y->r;
	}
	x->type = x->type->base;
}

// (* x = op x *)
void Op1(int op, struct Item *x) {
	long t;
	if (op == MINUS) {
		if (x->type->form != INTEGER) {
			Mark("wrong type.");
		} else if (x->mode == CONST) {
			x->a = -x->a;
		} else {
			if (x->mode == VAR) {
				OsgLoad(x);
			}
			Put(MVN, x->r, 0, x->r);
		}
	} else if (op == NOT) {
		if (x->mode != COND) {
			LoadBool(x);
		}
		x->c = Negated(x->c);
		t = x->a;
		x->a = x->b;
		x->b = t;
	} else if (op == AND) {
		if (x->mode != COND) {
			LoadBool(x);
		}
		PutBr(BEQ + Negated(x->c), x->a);
		EXCL(regs, x->r);
		x->a = pc - 1;
		FixLink(x->b);
		x->b = 0;
	}
}

// (* x = x op y *)
void Op2(int op, struct Item *x, struct Item *y) {
	if (x->type->form == INTEGER && y->type->form == INTEGER) {
		if (x->mode == CONST && y->mode == CONST) {
			// Недостаёт контроля переполнения.
			if (op == PLUS) {
				x->a += y->a;
			} else if (op == MINUS) {
				x->a -= y->a;
			} else if (op == TIMES) {
				x->a *= y->a;
			} else if (op == DIV) {
				x->a = x->a / y->a;
			} else if (op == MOD) {
				x->a = x->a % y->a;
			} else {
				Mark("wrong type.");
			}
		} else {
			if (op == PLUS) {
				PutOp(ADD, x, y);
			} else if (op == MINUS) {
				PutOp(SUB, x, y);
			} else if (op == TIMES) {
				PutOp(MUL, x, y);
			} else if (op == DIV) {
				PutOp(DIV, x, y);
			} else if (op == MOD) {
				PutOp(MOD, x, y);
			} else {
				Mark("wrong type.");
			}
		}
	} else if (x->type->form == BOOLEAN && y->type->form == BOOLEAN) {
		if (y->mode != COND) {
			LoadBool(y);
		}
		if (op == OR) {
			x->a = y->a;
			x->b = Merged(y->b, x->b);
			x->c = y->c;
		} else if (op == AND) {
			x->a = Merged(y->a, x->a);
			x->b = y->b;
			x->c = y->c;
		}
	} else {
		Mark("wrong type.");
	}
}

// (* x = x ? y *)
void Relation(int op, struct Item *x, struct Item *y) {
	if (x->type->form != INTEGER || y->type->form != INTEGER) {
		Mark("wrong type.");
	} else {
		PutOp(CMP, x, y);
		x->c = op - EQL;
		EXCL(regs, y->r);
	}
	x->mode = COND;
	x->type = boolType;
	x->a = 0;
	x->b = 0;
}

// (* x = y *)
void Store(struct Item *x, struct Item *y) {
	long r;
	if (x->type->form == BOOLEAN || x->type->form == INTEGER && x->type->form == y->type->form) {
		if (y->mode == COND) {
			Put(BEQ + Negated(y->c), y->r, 0, y->a);
			EXCL(regs, y->r);
			y->a = pc - 1;
			FixLink(y->b);
			GetReg(y->r);
			Put(MOVI, y->r, 0, 1);
			PutBr(BR, 2);
			FixLink(y->a);
			Put(MOVI, y->r, 0, 0);
		} else if (y->mode != REG) {
			OsgLoad(y);
		}
		if (x->mode == VAR) {
			if (x->lev == 0) {
				x->a -= pc * 4;
			}
			Put(STW, y->r, x->r, x->a);
		} else {
			Mark("wrong assignment.");
		}
		EXCL(regs, x->r);
		EXCL(regs, y->r);
	} else {
		Mark("wrong assignment.");
	}
}

void OsgParameter(struct Item *x, struct TypeDesc *ftyp, int class) {
	long r;
	if (x->type == ftyp) {
		if (class == PAR) { // Параметр-ссылка.
			if (x->mode == VAR) {
				if (x->a != 0) {
					GetReg(r);
					Put(ADDI, r, x->r, x->a);
				} else {
					r = x->r;
				}
			} else {
				Mark("wrong parameter mode.");
			}
			Put(PSH, r, SP, 4);
			EXCL(regs, r);
		} else { // Value param.
			if (x->mode != REG) {
				OsgLoad(x);
			}
			Put(PSH, x->r, SP, 4);
			EXCL(regs, x->r);
		}
	} else {
		Mark("wrong parameter type.");
	}
}

// (*-----------------------*)

void CJump(struct Item *x) {
	if (x->type->form == BOOLEAN) {
		if (x->mode != COND) {
			LoadBool(x);
		}
		PutBr(BEQ + Negated(x->c), x->a);
		EXCL(regs, x->r);
		FixLink(x->b);
		x->a = pc -1;
	} else {
		Mark("is a boolean?");
		x->a = pc;
	}
}

void BJump(long l) {
	PutBr(BR, l - pc);
}

void FJump(long l) {
	PutBr(BR, l);
	l = pc - 1;
}

void Call(struct Item *x) {
	PutBr(BSR, x->a - pc);
}

void IoCall(struct Item *x, struct Item *y) {
	struct Item *z;
	if (x->a < 4) {
		if (y->type->form != INTEGER) {
			Mark("is an integer?");
		}
	}
	if (x->a == 1) {
		GetReg(z->r);
		z->mode = REG;
		z->type = intType;
		Put(RD, z->r, 0, 0);
		Store(y, z);
	} else if (x->a == 2) {
		OsgLoad(y);
		Put(WRD, 0, 0, y->r);
		EXCL(regs, y->r);
	} else if (x->a == 3) {
		OsgLoad(y);
		Put(WRH, 0, 0, y->r);
		EXCL(regs, y->r);
	} else {
		Put(WRL, 0, 0, 0);
	}
}

void Header(long size) {
	entry = pc;
	Put(MOVI, SP, 0, RISC_MEMSIZE - size); // Инициализация SP. Используется RISC.MemSize из ядра ОС Оберон.
	Put(PSH, LNK, SP, 4);
}

void Enter(long size) {
	Put(PSH, LNK, SP, 4);
	Put(PSH, FP, SP, 4);
	Put(MOV, FP, 0, SP);
	Put(SUBI, SP, SP, size);
}

void Return(long size) {
	Put(MOV, SP, 0, FP);
	Put(POP, FP, SP, 4);
	Put(POP, LNK, SP, size + 4);
	PutBr(RET, LNK);
}

// Инициализация регистров.
void Open() {
	curlev = 0;
	pc = 0;
	cno = 0;
	memset(regs, 0, sizeof(char) * 64);
}

void Close(Identf s, long globals) {
	Put(POP, LNK, SP, 4);
	PutBr(RET, LNK);
}

void EnterCmd(Identf name) {
	idCpy(name, &comname[cno]);
	comadr[cno] = pc * 4;
	cno++;
}

// (*-----------------------*)

/*void LoadOsg(Identf s) {
	RISC.Load(code, pc);
	RISC.Execute(entry * 4, s, Oberon.Log);
}*/

/*void ExecOsg(Identf s) {
	i = 0;
	while (i < cno && s != comname[i]) {
		i++;
	}
	if (i < cno) {
		RISC.Execute(comadr[i], s, Oberon.Log);
	}
}*/

void Decode() {
	long i, w, op, a;
	fprintf(writerOsg, "entry %u\n", entry * 4);
	i = 0;
	while (i < pc) {
		w = code[i];
		op = w / 67108864 % 64;
		fprintf(writerOsg, "%u 9X [%s] ", 4 * i, mnemo[op]);
		if (op < BEQ) {
			a = w % 262144;
			if (a >= 131072) {
				a -= 262144; // Расширение знака.
			}
			fprintf(writerOsg, "9X %u, %u, ", w / 4194304 % 16, w / 262144 % 16);
		} else {
			a = w % 67108864;
			if (a >= 33554432) {
				a -= 67108864; // Расширение знака.
			}
		}
		fprintf(writerOsg, "%u\n", a);
		i++;
	}
	fprintf(writerOsg, "\n");
}

extern inline void SetMnemo(char op, const char *name) {
	memcpy(mnemo[op], name, strlen(name));
}

void Osg(const char *writerFile) {
	writerOsg = fopen(writerFile, "w");
	if (writerOsg == NULL)
		return;

	boolType = typeNew();
	boolType->form = BOOLEAN;
	boolType->size = 4;
	intType = typeNew();
	intType->form = INTEGER;
	intType->size = 4;

	SetMnemo(MOV,  "MOV ");
	SetMnemo(MVN,  "MVN ");
	SetMnemo(ADD,  "ADD ");
	SetMnemo(SUB,  "SUB ");
	SetMnemo(MUL,  "MUL ");
	SetMnemo(DIV,  "DIV ");
	SetMnemo(MOD,  "MOD ");
	SetMnemo(CMP,  "CMP ");
	SetMnemo(MOVI, "MOVI");
	SetMnemo(MVNI, "MVNI");
	SetMnemo(ADDI, "ADDI");
	SetMnemo(SUBI, "SUBI");
	SetMnemo(MULI, "MULI");
	SetMnemo(DIVI, "DIVI");
	SetMnemo(MODI, "MODI");
	SetMnemo(CMPI, "CMPI");
	SetMnemo(CHKI, "CHKI");
	SetMnemo(LDW,  "LDW ");
	SetMnemo(LDB,  "LDB ");
	SetMnemo(POP,  "POP ");
	SetMnemo(STW,  "STW ");
	SetMnemo(STB,  "STB ");
	SetMnemo(PSH,  "PSH ");
	SetMnemo(BEQ,  "BEQ ");
	SetMnemo(BNE,  "BNE ");
	SetMnemo(BLT,  "BLT ");
	SetMnemo(BGE,  "BGE ");
	SetMnemo(BLE,  "BLE ");
	SetMnemo(BGT,  "BGT ");
	SetMnemo(BR,   "BR  ");
	SetMnemo(BSR,  "BSR ");
	SetMnemo(RET,  "RET ");
	SetMnemo(RD,   "RD  ");
	SetMnemo(WRD,  "WRD ");
	SetMnemo(WRH,  "WRH ");
	SetMnemo(WRL,  "WRL ");
}
