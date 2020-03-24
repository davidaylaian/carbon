/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#define NULL ((void*) 0x0)
#define offsetof(type, member) ((size_t) & ((type*) 0)->member)

typedef signed ptrdiff_t;
typedef unsigned size_t;

#endif
