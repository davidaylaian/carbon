.PHONY: all build clean test

all: clean
	$(MAKE) -C kernel

build: all
	cp kernel/kernel.bin sysroot/boot
	grub-mkrescue -o Carbon-x86.iso sysroot

clean:
	$(MAKE) clean -C kernel

test: build
	qemu-system-i386 -cdrom Carbon-x86.iso
