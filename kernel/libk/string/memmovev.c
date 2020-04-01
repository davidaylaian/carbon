/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 * Code written and modified by Geoffrey Kublin
 * https://github.com/ReewassSquared
 * geoffreykublin@gmail.com
 * 
 */

#include <string.h>
#include <stddef.h>

volatile void* memmovev(volatile void* dest, const volatile void* src, size_t len)
{
	volatile size_t* tmp[len];
	memcpyv(tmp, src, len);
	memcpyv(dest, tmp, len);

	return dest;
}
