/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>

char* strmove(char* dest, const char* src)
{
	return memmove(dest, src, strlen(src) + 1);
}


