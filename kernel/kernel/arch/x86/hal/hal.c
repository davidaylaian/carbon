/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <kernel/hal.h>

void gdt_install();
void idt_install();
void pic_remap();
void isr_install();
void irq_install();
void pit_install();
void idt_setvect();

void hal_initialize()
{
	gdt_install();
	idt_install();
	pic_remap();
	isr_install();
	irq_install();
	pit_install();
}

void setvect(size_t intn, size_t handler)
{
	idt_setvect(intn, handler);
}
