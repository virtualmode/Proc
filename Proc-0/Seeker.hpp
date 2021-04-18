#pragma once

#ifndef SEEKER_HPP
#define SEEKER_HPP

#include "Temp/Dependency.h"

class Seeker {
public:
	// offset - количество состояний относительно начала потока.
	// Но есть проблема. Из-за использования логарифма, по сути мы можем перемещаться недалеко внутри одного машинного слова.
	// Надо придумать возможность длинного прыжка.
	virtual object Seek(object offset) = 0;
};

#endif // SEEKER_HPP
