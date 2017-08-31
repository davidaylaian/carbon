/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#ifndef STDIO_H
#define STDIO_H

#include <keyboard.h>
#include <vga.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define EOF -1

// print to stdout
extern void putchar(char c);
extern void puts(const char *str);
extern int vprintf(const char *format, va_list args);
extern int printf(const char *format, ...);

#endif
