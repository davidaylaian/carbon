/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>

char* strcpy(char* dest, const char* src)
{
	return memcpy(dest, src, strlen(src) + 1);
}
