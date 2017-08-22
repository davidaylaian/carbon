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
extern size_t strlen(const char *str);
extern int strcmp(const char *str1, const char *str2);

// string manipulation
extern char *strcpy(char *dest, const char *src);
extern char *strrev(char *str);

// string conversion
extern char *itoa(int n, char *buffer, int base);

#endif
