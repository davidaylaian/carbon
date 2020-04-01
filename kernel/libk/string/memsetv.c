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

volatile void* memsetv(volatile void *__s, int __c, size_t __n)
{
    volatile size_t *_p = __s;
    while (__n-- > 0) {
        *_p++ = __c;
    }

    return __s;
}
