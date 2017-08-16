/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <string.h>

// compares two strings lexicographically
int8_t strcmp(const char *str1, const char *str2)
{
	while (*str1 == *str2++) {
		if (*str1++ == 0) return 0;
	}

	return *(char*) str1 - *(char*) (str2 - 1);
}
