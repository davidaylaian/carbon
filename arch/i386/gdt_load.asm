extern gdtr
global gdt_load
gdt_load:
	lgdt [gdtr]		; load the GDT
	mov ax, 0x10		; flush segment registers and reload them for kernel mode
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flushCS	; perform far jump to set cs to 0x08
flushCS:
	ret
