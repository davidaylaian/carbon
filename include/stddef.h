/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#ifndef STDDEF_H
#define STDDEF_H

typedef signed ptrdiff_t;
typedef unsigned size_t;

#define NULL (void*) 0x0

#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE*)0) -> MEMBER)

#endif
