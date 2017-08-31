;********************************************
; Copyright 2017 David Aylaian
; https://github.com/DavidAylaian/Carbon/
;********************************************

; multiboot constants
MULTIBOOT_ALIGN		equ 1<<0		; page boundaries
MULTIBOOT_MEMINFO	equ 1<<1		; memory map
MULTIBOOT_MAGIC		equ 0x1BADB002		; magic number
MULTIBOOT_FLAGS		equ MULTIBOOT_ALIGN | MULTIBOOT_MEMINFO
MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

;********************************************
; start.asm - "where things start off scarce"
;********************************************

section .multiboot
align 4

; multiboot header
dd MULTIBOOT_MAGIC
dd MULTIBOOT_FLAGS
dd MULTIBOOT_CHECKSUM

section .bss
align 4

stack_bottom:
resb 16384
stack_top:

; kernel entry point
section .text
global start
start:
	mov esp, stack_top
	extern kmain
	call kmain
	jmp .hang

.hang:
	hlt
	jmp .hang
