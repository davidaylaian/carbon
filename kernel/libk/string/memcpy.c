/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>
#include <stddef.h>

void* memcpy(void* dest, const void* src, size_t len)
{
	size_t* dp = dest;
	const size_t* sp = src;

	for (size_t n = 0; n < len; n++)
	{
		*dp++ = *sp++;
	}

	return dest;
}

