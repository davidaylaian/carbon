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
* GCC Cross-Compiler: [`doc/cross-compiler.md`](https://github.com/davidaylaian/carbon/blob/master/doc/cross-compiler.md)
* Xorriso: `sudo apt-get install xorriso`

### Step 3: Build the kernel

To build the kernel, run `make` inside of either the kernel directory or root directory.


Additional information and common problems can be found in [`doc/building-the-kernel.md`](https://github.com/davidaylaian/carbon/blob/master/doc/building-the-kernel.md).

### Step 4: Build Carbon-x86.iso

To build Carbon-x86.iso, run `make build` in the root directory

## Running

Any emulator should work, but we reccomend qemu.

To install qemu: `sudo apt-get install qemu`<br>
To use qemu: `qemu-system-i386 -cdrom Carbon-x86.iso`

Running `make test` automatically builds and launches qemu with the iso in order to test it.