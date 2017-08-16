/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// string examination
extern int8_t strcmp(const char *str1, const char *str2);
extern size_t strlen(const char* str);

// string manipulation
extern char* strrev(char* str);

// string conversion
char* itoa(int32_t n, char* buffer, size_t base);

#endif
