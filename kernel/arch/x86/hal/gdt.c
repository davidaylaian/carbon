/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <hal.h>

#define MAX_DESCRIPTORS 3

extern void gdt_load();

// describes properties of a memory block and permissions
struct gdt_descriptor {
	uint16_t  limit;
	uint16_t  baseLo;
	uint8_t   baseMid;
	uint8_t   flags;
	uint8_t   grand;
	uint8_t   baseHi;
} __attribute__((packed));

// describes the structure for the gdtr register
struct gdtr {
	uint16_t  limit;
	uint32_t  base;
} __attribute__((packed));

static struct gdt_descriptor gdt[MAX_DESCRIPTORS];
struct gdtr gdtr;

// set a gdt descriptor
void gdt_set_descriptor(uint32_t i, uint64_t base, uint64_t limit, uint8_t access, uint8_t grand)
{
	// set base address
	gdt[i].baseLo	= base & 0xFFFF;
	gdt[i].baseMid	= (base >> 16) & 0xFF;
	gdt[i].baseHi	= (base >> 24) & 0xFF;

	// set limit
	gdt[i].limit = limit & 0xFFFF;

	// set flags
	gdt[i].flags = access;

	// set granularity
	gdt[i].grand = (limit >> 16) & 0x0F;
	gdt[i].grand |= grand & 0xF0;
}

// install the gdt
void gdt_install()
{
	// set up gdtr
	gdtr.limit = (sizeof(struct gdt_descriptor) * MAX_DESCRIPTORS) - 1;
	gdtr.base  = (uint32_t) &gdt[0];

	// null descriptor
	gdt_set_descriptor(0, 0, 0, 0, 0);

	// code descriptor
	gdt_set_descriptor(1, 0, 0xFFFFFFFF,
		0b10011010,
		0b11001111
	);

	// data descriptor
	gdt_set_descriptor(2, 0, 0xFFFFFFFF,
		0b10010010,
		0b11001111
	);

	gdt_load();
}
