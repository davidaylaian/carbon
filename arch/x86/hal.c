#include <hal.h>

// found in gdt.c
extern void gdt_install();

// install hardware abstraction layer
void hal_install() {
	gdt_install();
}
