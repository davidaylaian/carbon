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

/*
 * TODO: Carbon will eventually need a more sophisticated buffer-based stdio.
 * However, it won't matter until we start getting into userspace. For now,
 * we just need something small and forwards compatible.
 */

void putchar(char c);
void puts(const char* str);
int vprintf(const char* format, va_list args);
int printf(const char* format, ...);

#endif
