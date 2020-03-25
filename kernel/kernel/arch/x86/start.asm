;********************************************
; Copyright 2020 David Aylaian
; https://github.com/davidaylaian/carbon/
; Licensed under the Apache License 2.0
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

; multiboot header
section .multiboot
align 4
dd MULTIBOOT_MAGIC
dd MULTIBOOT_FLAGS
dd MULTIBOOT_CHECKSUM

; the stack
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

; kernel entry
section .text
extern kernel_main
global start
start:
	mov esp, stack_top
	call kernel_main
.hang:	hlt
	jmp .hang
