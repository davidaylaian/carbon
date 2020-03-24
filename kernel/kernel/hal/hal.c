/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <hal.h>

void gdt_install();
void idt_install();
void pic_remap();

void hal_initialize()
{
	gdt_install();
	idt_install();
	pic_remap();
}
