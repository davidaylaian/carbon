# Required Dependencies:
# * gnu make		(sudo apt-get install make)
# * nasm		(sudo apt-get install nasm)
# * gcc cross-compiler	(see http://wiki.osdev.org/GCC_Cross-Compiler)
# * grub-mkrescue	(sudo apt-get install xorriso)

# Additional Reccomended Software:
# * qemu		(sudo apt-get install qemu)



# flags
CFLAGS=-nostdlib -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdinc -fno-builtin -I./include -masm=intel -c -o
LDFLAGS=-ffreestanding -O3 -nostdlib -lgcc -T kernel/link.ld -o iso/boot/kernel.bin
ASFLAGS=-felf32 -o

all:
	make build
	make vm
	make clean

build:
	# iso/
	mkdir -p iso/boot/grub
	cp grub.cfg iso/boot/grub/grub.cfg
	
	# *.o
	nasm		$(ASFLAGS) kernel/start.o kernel/start.asm
	i686-elf-gcc	$(CFLAGS) kernel/main.o kernel/main.c
	
	# kernel.bin
	i686-elf-gcc	$(LDFLAGS) kernel/start.o kernel/main.o
	
	# CarbonOS.iso
	grub-mkrescue -o CarbonOS.iso iso/

vm:
	qemu-system-i386 -cdrom CarbonOS.iso

clean:
	rm -rf iso/
	rm -f CarbonOS.iso
	find . -name "*.o" -type f -delete
