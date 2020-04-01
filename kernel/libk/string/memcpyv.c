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

volatile void* memcpyv(volatile void *__d, const volatile void *__s, size_t __n)
{
    volatile size_t* _dp = __d;
	const volatile size_t* _sp = __s;

	while (__n-- > 0) {
		*_dp++ = *_sp++;
	}

	return __d;
}
