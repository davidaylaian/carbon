# for now, most of these are aliased to the PHONY targets in ./kernel/,
# but this may change as the OS evolves.

.PHONY: all build clean dist tar test todolist

all: clean
	$(MAKE) -C kernel

build: all
	cp kernel/kernel.bin sysroot/boot
	grub-mkrescue -o Carbon-x86.iso sysroot

clean:
	$(MAKE) clean -C kernel

dist tar: clean
	$(MAKE) tar -C kernel

test: build
	qemu-system-i386 -cdrom Carbon-x86.iso

todolist:
	$(MAKE) todolist -C kernel