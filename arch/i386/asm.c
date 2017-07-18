#include <hal.h>

// enable interrupts
void enable() {
	asm("sti");
}

// disable interrupts
void disable() {
	asm("cli");
}

// get an 8-bit value from an I/O device
uint8_t inb(uint16_t port)
{
	uint8_t val;
	asm volatile("inb %0, %1" : "=a"(val) : "Nd"(port));
	return val;
}

// send an 8-bit value to an I/O device
void outb(uint16_t port, uint8_t val)
{
	asm volatile("outb %1, %0" :: "a"(val), "Nd"(port));
}
