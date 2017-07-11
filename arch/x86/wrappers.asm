extern isr_handler
isr_wrapper:
	; push registers
	pusha
	push ds
	push es
	push fs
	push gs
	
	; flush segment registers and reload them for kernel mode
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; push the stack
	mov eax, esp
	push eax
	
	; call the handler
	mov eax, isr_handler
	call eax
	
	; pop registers
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	
	; return
	add esp, 8
	iret

global isr_wrapper_0
global isr_wrapper_1
global isr_wrapper_2
global isr_wrapper_3
global isr_wrapper_4
global isr_wrapper_5
global isr_wrapper_6
global isr_wrapper_7
global isr_wrapper_8
global isr_wrapper_9
global isr_wrapper_10
global isr_wrapper_11
global isr_wrapper_12
global isr_wrapper_13
global isr_wrapper_14
global isr_wrapper_15
global isr_wrapper_16
global isr_wrapper_17
global isr_wrapper_18
global isr_wrapper_19
global isr_wrapper_20
global isr_wrapper_21
global isr_wrapper_22
global isr_wrapper_23
global isr_wrapper_24
global isr_wrapper_25
global isr_wrapper_26
global isr_wrapper_27
global isr_wrapper_28
global isr_wrapper_29
global isr_wrapper_30
global isr_wrapper_31

isr_wrapper_0:
	push byte 0
	push byte 0
	jmp isr_wrapper

isr_wrapper_1:
	push byte 0
	push byte 1
	jmp isr_wrapper

isr_wrapper_2:
	push byte 0
	push byte 2
	jmp isr_wrapper

isr_wrapper_3:
	push byte 0
	push byte 3
	jmp isr_wrapper

isr_wrapper_4:
	push byte 0
	push byte 4
	jmp isr_wrapper

isr_wrapper_5:
	push byte 0
	push byte 5
	jmp isr_wrapper

isr_wrapper_6:
	push byte 0
	push byte 6
	jmp isr_wrapper

isr_wrapper_7:
	push byte 0
	push byte 7
	jmp isr_wrapper

isr_wrapper_8:
	push byte 8
	jmp isr_wrapper

isr_wrapper_9:
	push byte 0
	push byte 9
	jmp isr_wrapper

isr_wrapper_10:
	push byte 10
	jmp isr_wrapper

isr_wrapper_11:
	push byte 11
	jmp isr_wrapper

isr_wrapper_12:
	push byte 12
	jmp isr_wrapper

isr_wrapper_13:
	push byte 13
	jmp isr_wrapper

isr_wrapper_14:
	push byte 14
	jmp isr_wrapper

isr_wrapper_15:
	push byte 0
	push byte 15
	jmp isr_wrapper

isr_wrapper_16:
	push byte 0
	push byte 16
	jmp isr_wrapper

isr_wrapper_17:
	push byte 0
	push byte 17
	jmp isr_wrapper

isr_wrapper_18:
	push byte 0
	push byte 18
	jmp isr_wrapper

isr_wrapper_19:
	push byte 0
	push byte 19
	jmp isr_wrapper

isr_wrapper_20:
	push byte 0
	push byte 20
	jmp isr_wrapper

isr_wrapper_21:
	push byte 0
	push byte 21
	jmp isr_wrapper

isr_wrapper_22:
	push byte 0
	push byte 22
	jmp isr_wrapper

isr_wrapper_23:
	push byte 0
	push byte 23
	jmp isr_wrapper

isr_wrapper_24:
	push byte 0
	push byte 24
	jmp isr_wrapper

isr_wrapper_25:
	push byte 0
	push byte 25
	jmp isr_wrapper

isr_wrapper_26:
	push byte 0
	push byte 26
	jmp isr_wrapper

isr_wrapper_27:
	push byte 0
	push byte 27
	jmp isr_wrapper

isr_wrapper_28:
	push byte 0
	push byte 28
	jmp isr_wrapper

isr_wrapper_29:
	push byte 0
	push byte 29
	jmp isr_wrapper

isr_wrapper_30:
	push byte 0
	push byte 30
	jmp isr_wrapper

isr_wrapper_31:
	push byte 0
	push byte 31
	jmp isr_wrapper

extern irq_handler
irq_wrapper:
	; push registers
	pusha
	push ds
	push es
	push fs
	push gs
	
	; flush segment registers and reload them for kernel mode
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; push the stack
	mov eax, esp
	push eax
	
	; call the handler
	mov eax, irq_handler
	call eax
	
	; pop registers
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	
	; return
	add esp, 8
	iret

global irq_wrapper_0
global irq_wrapper_1
global irq_wrapper_2
global irq_wrapper_3
global irq_wrapper_4
global irq_wrapper_5
global irq_wrapper_6
global irq_wrapper_7
global irq_wrapper_8
global irq_wrapper_9
global irq_wrapper_10
global irq_wrapper_11
global irq_wrapper_12
global irq_wrapper_13
global irq_wrapper_14
global irq_wrapper_15

irq_wrapper_0:
	cli
	push byte 0
	jmp isr_wrapper

irq_wrapper_1:
	cli
	push byte 1
	jmp irq_wrapper

irq_wrapper_2:
	cli
	push byte 2
	jmp irq_wrapper

irq_wrapper_3:
	cli
	push byte 3
	jmp irq_wrapper

irq_wrapper_4:
	cli
	push byte 4
	jmp irq_wrapper

irq_wrapper_5:
	cli
	push byte 5
	jmp irq_wrapper

irq_wrapper_6:
	cli
	push byte 6
	jmp irq_wrapper

irq_wrapper_7:
	cli
	push byte 7
	jmp irq_wrapper

irq_wrapper_8:
	cli
	push byte 8
	jmp irq_wrapper

irq_wrapper_9:
	cli
	push byte 9
	jmp irq_wrapper

irq_wrapper_10:
	cli
	push byte 10
	jmp irq_wrapper

irq_wrapper_11:
	cli
	push byte 11
	jmp irq_wrapper

irq_wrapper_12:
	cli
	push byte 12
	jmp irq_wrapper

irq_wrapper_13:
	cli
	push byte 13
	jmp irq_wrapper

irq_wrapper_14:
	cli
	push byte 14
	jmp irq_wrapper

irq_wrapper_15:
	cli
	push byte 15
	jmp irq_wrapper
