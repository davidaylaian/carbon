/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <hal.h>

void setvect(uint8_t intn, uint64_t handler)
{
	install_ir(intn, handler, 0x8E, 0x08);
}

// install hardware abstraction layer
void hal_install()
{
	gdt_install();
	idt_install();
	pic_remap();
	isr_install();
	irq_install();
}
