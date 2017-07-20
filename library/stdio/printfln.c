/**
 * 
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/CarbonOS/
 * 
 */

#include <stdio.h>

 // prints a string and a newline
void println(char* str)
{
	print(str);
	print("\n");
}

// prints a va_list argument list in the given format and a newline
void vprintfln(char* format, va_list args)
{
	vprintf(format, args);
	print("\n");
}

// prints an ellipsis argument list in the given format and a newline
void printfln(char* format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	print("\n");
}
