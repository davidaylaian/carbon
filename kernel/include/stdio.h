/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>

void putchar(char c);
void puts(const char* str);

/*
 * For the *printf family, we use a library called mpaland/printf which can be found in libk/stdio/printf.c.
 * The library names all of the functions with underscores to avoid conflicts.
 */

#define printf printf_
#define sprintf sprintf_
#define snprintf snprintf_
#define vsnprintf vsnprintf_
#define vprintf vprintf_

int printf_(const char* format, ...);
int sprintf_(char* buffer, const char* format, ...);
int snprintf_(char* buffer, size_t count, const char* format, ...);
int vsnprintf_(char* buffer, size_t count, const char* format, va_list va);
int vprintf_(const char* format, va_list va);

// use output function (instead of buffer) for streamlike interface
int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);

#endif
