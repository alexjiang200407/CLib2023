#include "stringUtil.h"
#include <stdio.h>
#include <stdarg.h>

char* formatBuf(size_t* bufSz, const char* const fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	size_t len = vsnprintf(NULL, 0, fmt, args);

	if (bufSz)
	{
		*bufSz = len;
	}

	char* buf = malloc(len + 1);

	if (!buf)
	{
		return NULL;
	}

	vsnprintf(buf, len + 1, fmt, args);

	va_end(args);
	return buf;
}
