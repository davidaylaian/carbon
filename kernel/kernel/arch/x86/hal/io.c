/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <kernel/hal.h>
#include <stdint.h>

// enable interrupts
void enable()
{
	asm volatile("sti");
}

// disable interrupts
void disable()
{
	asm volatile("cli");
}

// send an 8-bit value to an I/O device
void outb(uint16_t port, uint8_t val)
{
	asm volatile("outb %1, %0" :: "a" (val), "Nd" (port));
}

// send a 16-bit value to an I/O device
void outw(uint16_t port, uint16_t val)
{
	asm volatile("outw %1, %0" :: "a" (val), "Nd" (port));
}

// get an 8-bit value from an I/O device
uint8_t inb(uint16_t port)
{
	uint8_t val;
	asm volatile("inb %0, %1" : "=a" (val) : "Nd" (port));
	return val;
}

// get a 16-bit value from an I/O device
uint16_t inw(uint16_t port)
{
	uint16_t val;
	asm volatile("inw %0, %1" : "=a" (val) : "Nd" (port));
	return val;
}
