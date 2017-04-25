#include <hal.h>

#define MAX_DESCRIPTORS 3

// found in gdt.asm
extern void gdt_load();

/* Note: __attribute__((packed))			*/
/* Packing will prevent the compiler from putting our	*/
/* code through the good-code-to-bad-code converter by	*/
/* telling it not to optimize our code. Doing so will	*/
/* convert our good C code into bad Java code, and this	*/
/* is bad because Java is basically just bad C code.	*/

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

// the global descriptor table is an array of descriptors
struct gdt_descriptor gdt[MAX_DESCRIPTORS];

// gdtr is used to set the gdtr register to point to the gdt
struct gdtr gdtr;

void gdt_set_descriptor (uint32_t i, uint64_t base, uint64_t limit, uint8_t access, uint8_t grand)
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

void gdt_install()
{
	// set up gdtr
	gdtr.limit = (sizeof (struct gdt_descriptor) * MAX_DESCRIPTORS) -1;
	gdtr.base  = (uint32_t)& gdt[0];
	
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
	
	// load gdt by setting gdtr register to point to gdt and reloading registers
	gdt_load();
}
