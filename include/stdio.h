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

// print to stdout with a newline
extern void println(string str);
extern void vprintfln(string format, va_list args);
extern void printfln(string format, ...);

#endif
