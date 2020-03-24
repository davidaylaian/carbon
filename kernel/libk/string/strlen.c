/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>
#include <stddef.h>

size_t strlen(const char* str)
{
	size_t length = 0;
	for (; str[length] != '\0'; length++);
	return length;
}

