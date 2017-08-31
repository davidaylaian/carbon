/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#ifndef REGS_H
#define REGS_H

#include <stdint.h>

struct regs
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t intn, error_code;
	uint32_t eip, cs, eflags, useresp, ss;
};

#endif
