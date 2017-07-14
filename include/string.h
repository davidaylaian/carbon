#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

// string examination
extern int8_t strcmp(const char *str1, const char *str2);
extern size_t strlen(const char* str);

// string manipulation
extern char* strrev(char* str);

#endif
