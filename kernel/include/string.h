/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef _STRING_H
#define _STRING_H

#include <attribute.h>
#include <stddef.h>

void* memset(void* dest, int src, size_t len);
void* memcpy(void* dest, const void* src, size_t len);
void* memmove(void* dest, const void* src, size_t len);

// volatile versions of memory functions
volatile void* memsetv(volatile void* __s, int __c, size_t __n);
volatile void* memcpyv(volatile void* dest, const volatile void* src, size_t len);
volatile void* memmovev(volatile void* dest, const volatile void* src, size_t len);

size_t strlen(const char* str);
int strcmp(const char* str1, const char* str2);

char* strcpy(char* dest, const char* src);
char* strmove(char* dest, const char* src);
char* strcat(char* dest, const char* src);
char* strrev(char* str);

char* itoa(int n, char* buffer, int base);

#endif
