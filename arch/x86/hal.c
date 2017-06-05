#include <hal.h>

extern void gdt_install();
extern void idt_install();
extern void install_ir(uint32_t i, uint64_t base, uint16_t flags, uint16_t sel);

void setvect(uint8_t intn, uint64_t handler) {
	install_ir(intn, handler, 0x8E, 0x08);
}

// install hardware abstraction layer
void hal_install() {
	gdt_install();
	idt_install();
}
