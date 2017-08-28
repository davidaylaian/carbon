/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <hal.h>

#define MAX_INTERRUPTS 256

// describes an interrupt descriptor
struct idt_descriptor {
	uint16_t  baseLo;
	uint16_t  selector;
	uint8_t   reserved;
	uint8_t   flags;
	uint16_t  baseHi;
} __attribute__((packed));

// describes the structure for the idtr register
struct idtr {
	uint16_t  limit;
	uint32_t  base;
} __attribute__((packed));

// the interrupt descriptor table is an array of descriptors
struct idt_descriptor idt[MAX_INTERRUPTS];

// idtr is used to set the idtr register to point to the idt
struct idtr idtr;

// display (primitive) error message and halt execution
noreturn void default_handler()
{
	puts("\n");
	puts("              +==================================================+              ");
	puts("              |  ***  default_handler: Unhandled Exception  ***  |              ");
	puts("              |  ***           Execution halted.            ***  |              ");
	puts("              +==================================================+              ");
	puts("\n");

	disable();
	while (1);
}

// installs an interrupt routine (ir)
void install_ir(uint32_t i, uint64_t base, uint16_t flags, uint16_t sel)
{
	// set base address
	idt[i].baseLo	= base & 0xFFFF;
	idt[i].baseHi	= (base >> 16) & 0xFFFF;

	// thanks Intel
	idt[i].reserved	= 0;

	// set flags and selector
	idt[i].flags	= flags;
	idt[i].selector	= sel;
}

void idt_install()
{
	// set up idtr
	idtr.limit = sizeof(struct idt_descriptor) * MAX_INTERRUPTS-1;
	idtr.base  = (uint32_t) & idt[0];

	// register default handlers
	for (size_t i=0; i<MAX_INTERRUPTS; i++)
		install_ir (i, (size_t)default_handler, 0x8E, 0x08);

	// load idt by setting idtr register to point to idt
	asm("lidt [idtr]");
}
