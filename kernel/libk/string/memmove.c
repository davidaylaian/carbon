/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>
#include <stddef.h>

void* memmove(void* dest, const void* src, size_t len)
{
	size_t tmp[len];
	memcpy(tmp, src, len);
	memcpy(dest, tmp, len);
	return dest;
}
