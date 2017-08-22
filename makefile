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
export CFLAGS=-nostdlib -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdinc -fno-builtin -I ~/Carbon/include -masm=intel -c
export LDFLAGS=-ffreestanding -O3 -nostdlib -lgcc

# object files
OBJS=				\
arch/i386/gdt_load.o		\
arch/i386/wrappers.o		\
arch/i386/asm.o			\
arch/i386/gdt.o			\
arch/i386/idt.o			\
arch/i386/pic.o			\
arch/i386/isr.o			\
arch/i386/irq.o			\
arch/i386/hal.o			\
drivers/keyboard.o		\
drivers/vga.o			\
library/string/strcmp.o		\
library/string/strlen.o		\
library/string/strrev.o		\
library/string/itoa.o		\
library/stdio/putchar.o		\
library/stdio/puts.o		\
library/stdio/vprintf.o		\
library/stdio/printf.o		\
kernel/arch/i386/start.o	\
kernel/kmain.o			\

all:
	make build
	make vm
	make clean

build:
	# iso
	mkdir -p iso/boot/grub
	cp grub.cfg iso/boot/grub/grub.cfg
	
	$(MAKE) -C arch build		# hal
	$(MAKE) -C drivers build	# drivers
	$(MAKE) -C library build	# library
	$(MAKE) -C kernel build		# kernel
	
	# kernel.bin
	$(CC) $(LDFLAGS) -T kernel/link.ld -o iso/boot/kernel.bin $(OBJS)
	
	# Carbon.iso
	grub-mkrescue -o Carbon.iso iso

vm:
	$(QEMU) -cdrom Carbon.iso

clean:
	rm -rf iso
	rm -f Carbon.iso
	$(MAKE) -C arch clean
	$(MAKE) -C drivers clean
	$(MAKE) -C library clean
	$(MAKE) -C kernel clean
