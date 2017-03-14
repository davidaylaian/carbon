#ifndef STDIO_H
#define STDIO_H

#include <drivers/terminal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define EOF -1

// print to stdout
extern void print(string str);
extern void vprintf(string format, va_list args);
extern void printf(string format, ...);

// prints a string and a newline
inline void println(string str) {
	printf("%s\n", str);
}

// prints a va_list argument list in the given format and a newline
inline void vprintfln(string format, va_list args) {
	vprintf(format, args);
	print("\n");
}

// prints an ellipsis argument list in the given format and a newline
inline void printfln(string format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	
	print("\n");
}

#endif
