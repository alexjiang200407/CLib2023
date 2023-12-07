#include "util.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

char* formatBuf(size_t* bufSz, const char* const fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	// First vsnprintf gets the length of the buffer minus null character
	size_t len = vsnprintf(NULL, 0, fmt, args);

	if (bufSz)
	{
		*bufSz = len;
	}

	// Malloc enough bytes for string
	char* buf = malloc(len + 1);

	if (!buf)
	{
		return NULL;
	}

	// Now print for real
	vsnprintf(buf, len + 1, fmt, args);

	va_end(args);
	return buf;
}

int rng(int min, int max)
{
	// Return random number between range
	return rand() % (max + 1 - min) + min;
}

void* CpyToHeap(void* cpy, size_t sz)
{
	void* ret = malloc(sz);
	if (!ret)
	{
		return NULL;
	}

	memcpy(ret, cpy, sz);
	return ret;
}

void swap(Item* lhs, Item* rhs)
{
	Item temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}
