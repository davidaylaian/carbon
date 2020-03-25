/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <attribute.h>
#include <stddef.h>
#include <stdint.h>

// from gdt_load.asm
void gdt_load();

#define GDT_MAX_DESCRIPTORS 3

// describes properties of a memory block and permissions
struct gdt_descriptor {
	uint16_t limit;
	uint16_t base_lo;
	uint8_t  base_mid;
	uint8_t  flags;
	uint8_t  granularity;
	uint8_t  base_hi;
} packed;

// describes the structure for the gdtr register
struct gdt_gdtr {
	uint16_t limit;
	uint32_t base;
} packed;

static struct gdt_descriptor gdt[GDT_MAX_DESCRIPTORS];
struct gdt_gdtr gdt_gdtr;

static void gdt_set_descriptor(size_t i, uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity)
{
	gdt[i].base_lo	= base & 0xFFFF;
	gdt[i].base_mid	= (base >> 16) & 0xFF;
	gdt[i].base_hi	= (base >> 24) & 0xFF;

	gdt[i].limit = limit & 0xFFFF;
	gdt[i].flags = access;

	gdt[i].granularity = (limit >> 16) & 0x0F;
	gdt[i].granularity |= granularity & 0xF0;
}

void gdt_install()
{
	gdt_gdtr.limit = (sizeof(struct gdt_descriptor) * GDT_MAX_DESCRIPTORS) - 1;
	gdt_gdtr.base  = (uint32_t) &gdt[0];

	// null descriptor
	gdt_set_descriptor(0, 0, 0, 0, 0);

	// code descriptor
	gdt_set_descriptor(1, 0,
		0xFFFFFFFF,
		0b10011010,
		0b11001111
	);

	// data descriptor
	gdt_set_descriptor(2, 0,
		0xFFFFFFFF,
		0b10010010,
		0b11001111
	);

	gdt_load();
}
