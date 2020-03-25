/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef HAL_REGS_H
#define HAL_REGS_H

#include <stdint.h>

struct hal_registers
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t intn, error_code;
	uint32_t eip, cs, eflags, useresp, ss;
};

#endif
