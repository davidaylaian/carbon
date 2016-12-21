OUTPUT_FORMAT("binary")
ENTRY(start)
phys = 1M;

SECTIONS
{
	/* executable opcodes and operands */
	.text phys : AT(phys) {
		text = .;
		*(.text)
		*(.rodata*)
		. = ALIGN(4K);
	}
	
	/* read-write data (initialized)   */
	.data : AT(phys + (data - text)) {
		data = .;
		*(.data)
		. = ALIGN(4K);
	}
	
	/* read-write data (uninitialized) */
	.bss : AT(phys + (bss - text)) {
		bss = .;
		*(.bss)
		. = ALIGN(4K);
	}
	
	end = .;
}
