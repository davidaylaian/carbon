/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>
#include <stddef.h>

void* memset(void* dest, int src, size_t len)
{
	size_t* dp = dest;

	for (size_t n = 0; n < len; n++)
	{
		*dp++ = src;
	}

	return dest;
}
