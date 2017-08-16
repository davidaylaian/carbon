/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#ifndef STDIO_H
#define STDIO_H

#include <drivers/keyboard.h>
#include <drivers/vga.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define EOF -1

// print to stdout
extern void print(char* str);
extern void vprintf(char* format, va_list args);
extern void printf(char* format, ...);

// print to stdout with a newline
extern void println(char* str);
extern void vprintfln(char* format, va_list args);
extern void printfln(char* format, ...);

#endif
