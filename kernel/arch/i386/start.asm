;********************************************
; Copyright 2017 David Aylaian
; https://github.com/DavidAylaian/CarbonOS/
;********************************************

;********************************************
; start.asm - "where things start off scarce"
;********************************************

ALIGN 4
mboot:
	; define constants
	MULTIBOOT_ALIGN		equ 1<<0		; page boundaries
	MULTIBOOT_MEMINFO	equ 1<<1		; memory map
	MULTIBOOT_KLUDGE	equ 1<<16		; a.out kludge
	MULTIBOOT_MAGIC		equ 0x1BADB002		; magic number
	MULTIBOOT_FLAGS		equ MULTIBOOT_ALIGN | MULTIBOOT_MEMINFO | MULTIBOOT_KLUDGE
	MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
	EXTERN text, bss, end
	
	; grub multiboot header
	dd MULTIBOOT_MAGIC
	dd MULTIBOOT_FLAGS
	dd MULTIBOOT_CHECKSUM
	
	; sections for link.ld
	dd mboot
	dd text
	dd bss
	dd end
	dd start

; kernel entry point
global start
start:
	; set up stack
	mov esp, stack
	
	; execute kmain()
	extern kmain
	call kmain
	
	; hang if kmain() returns
	jmp hang

; hangs the cpu
global hang
hang:
	hlt
	jmp hang

; reserve 16KB for bss segment
SECTION .bss
	resb 16384

stack:
