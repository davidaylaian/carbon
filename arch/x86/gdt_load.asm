;****************************************
; Copyright 2017 David Aylaian
; https://github.com/DavidAylaian/Carbon/
;****************************************

extern gdtr
global gdt_load

; load the gdt
gdt_load:
	lgdt [gdtr]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush
flush:
	ret
