# Carbon

Carbon is an x86 operating system in early development.

## Building
###### Note: this section was written for Linux systems. Please submit an [issue](issues) if you have problems building Carbon.

### Step 1: Clone the Repository

```bash
git clone https://github.com/davidaylaian/carbon.git
cd carbon
```

### Step 2: Install Dependencies

* Make: `sudo apt-get install make`
* NASM: `sudo apt-get install nasm`
* GCC Cross-Compiler: [`http://wiki.osdev.org/GCC_Cross-Compiler`](https://wiki.osdev.org/GCC_Cross-Compiler)
* Xorriso: `sudo apt-get install xorriso`

### Step 3: Build the kernel

To build the kernel, run `make` inside of the kernel directory.

```bash
cd kernel
make
cd ..
```

You need a [cross-compiler](https://github.com/davidaylaian/carbon/blob/master/doc/cross-compiler.md) for this step. Additional important information and common problems can be found in [`doc/building-the-kernel.md`](https://github.com/davidaylaian/carbon/blob/master/doc/building-the-kernel.md).

### Step 4: Build Carbon-x86.iso

To build Carbon-x86.iso, copy kernel/kernel.bin to sysroot/boot, and use `grub-mkrescue` to build the disk image.

```bash
cp kernel/kernel.bin sysroot/boot
grub-mkrescue -o Carbon-x86.iso sysroot
```

## Running

Any emulator should work, but we reccomend qemu.

To install qemu: `sudo apt-get install qemu`<br>
To use qemu: `qemu-system-i386 -cdrom Carbon-x86.iso`
