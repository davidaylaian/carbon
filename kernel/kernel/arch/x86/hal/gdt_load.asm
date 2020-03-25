;****************************************
; Copyright 2020 David Aylaian
; https://github.com/davidaylaian/carbon/
; Licensed under the Apache License 2.0
;****************************************

extern gdt_gdtr
global gdt_load

; for use in gdt_install in gdt.c
; updates the gdtr register and loads the gdt pointed to by gdt_gdtr
gdt_load:
	lgdt [gdt_gdtr]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.reload_cs
.reload_cs:
	ret
