#include <stdio.h>

// prints an ellipsis argument list to stdout in the given format
int printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);
	return ret;
}
