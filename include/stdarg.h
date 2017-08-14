/**
 * 
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 * 
 * Based on code found at
 * http://www.brokenthorn.com/Resources/OSDev14.html
 * Copyright 2008, BrokenThorn Entertainment, Co.
 * 
 */

#ifndef STDARG_H
#define STDARG_H

#include <stdint.h>

typedef uint8_t* va_list;

#define STACKITEM sizeof(int)

#define	VA_SIZE(TYPE)			\
	((sizeof(TYPE) + STACKITEM - 1)	\
	& ~(STACKITEM - 1))

#define	va_start(AP, LASTARG)		\
	(AP=((va_list)&(LASTARG)	\
	+ VA_SIZE(LASTARG)))

#define va_end(AP)

#define va_arg(AP, TYPE)		\
	(AP += VA_SIZE(TYPE),		\
	*((TYPE *)			\
	(AP - VA_SIZE(TYPE))))

#endif
