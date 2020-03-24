/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef _STDARG_H
#define _STDARG_H

typedef __builtin_va_list	va_list;

#define va_start(ap, pN)	__builtin_va_start(ap, pN)
#define va_end(ap)		__builtin_va_end(ap)
#define va_arg(ap, type)	__builtin_va_arg(ap, type)
#define va_copy(dest, src)	__builtin_va_copy(dest, src)

#endif
