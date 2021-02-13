#pragma once

#ifndef MEMORY_STREAM_H
#define MEMORY_STREAM_H

#include "Temp/Dependency.h"

#include "Reader.hpp"
#include "Writer.hpp"

class MemoryStream: public Reader, public Writer {
	public:

	MemoryStream(object pointer) {
	}

	virtual ~MemoryStream() {
	}

	virtual object Read(object destination, object base) {
		return NULL;
	}

	virtual object Write(object source, object base) {
		return NULL;
	}
};

#endif // MEMORY_STREAM_H
