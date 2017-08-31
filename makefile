# Required Dependencies:
# * gnu make		(sudo apt-get install make)
# * nasm		(sudo apt-get install nasm)
# * gcc cross-compiler	(see http://wiki.osdev.org/GCC_Cross-Compiler)
# * grub-mkrescue	(sudo apt-get install xorriso)

# Additional Reccomended Software:
# * qemu		(sudo apt-get install qemu)


# executables
export AS=nasm
export CC=i686-elf-gcc
export LINK=i686-elf-gcc
export QEMU=qemu-system-i386

# flags
export ASFLAGS=-felf32
export CFLAGS=-nostdlib -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdinc -fno-builtin -I ~/Carbon/kernel/include -I ~/Carbon/library/include -masm=intel -c
export LDFLAGS=-ffreestanding -O3 -nostdlib -lgcc

# object files
OBJS=				\
kernel/arch/x86/hal/gdt_load.o	\
kernel/arch/x86/hal/wrappers.o	\
kernel/arch/x86/hal/asm.o	\
kernel/arch/x86/hal/gdt.o	\
kernel/arch/x86/hal/idt.o	\
kernel/arch/x86/hal/pic.o	\
kernel/arch/x86/hal/isr.o	\
kernel/arch/x86/hal/irq.o	\
kernel/arch/x86/hal/hal.o	\
kernel/drivers/keyboard.o	\
kernel/drivers/vga.o		\
library/string/strcat.o		\
library/string/strcmp.o		\
library/string/strcpy.o		\
library/string/strlen.o		\
library/string/strrev.o		\
library/string/itoa.o		\
library/stdio/putchar.o		\
library/stdio/puts.o		\
library/stdio/vprintf.o		\
library/stdio/printf.o		\
kernel/arch/x86/start.o	\
kernel/kmain.o			\

all:
	make build
	make vm
	make clean

build:
	$(MAKE) -C library build
	$(MAKE) -C kernel build
	$(CC) $(LDFLAGS) -T kernel/link.ld -o sysroot/boot/kernel.bin $(OBJS)
	grub-mkrescue -o Carbon.iso sysroot

vm:
	$(QEMU) -cdrom Carbon.iso

clean:
	rm -rf sysroot/boot/kernel.bin
	rm -f Carbon.iso
	$(MAKE) -C library clean
	$(MAKE) -C kernel clean
