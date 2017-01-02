# CarbonOS
CarbonOS is an [open-source](https://github.com/DavidAylaian/CarbonOS) operating system designed to run on x86.

## Organization
CarbonOS is organized into four sections:
* **The [Drivers](drivers):** low-level, hardware-dependent drivers that provide an abstraction layer between the hardware and the library. This section contains all of the files that only work on specific hardware, allowing the rest of the system to be portable.
* **The [Library](library):** the high-level library that provides an abstraction layer between the drivers and the kernel. The library is completely independent from hardware. The CarbonOS library differs from the standard C library, but most of the functions are similar if not the same.
* **The [Headers](include):** the header files for both the drivers and library that can be linked with an `#include`.
* **The [Kernel](kernel):** the kernel that uses the library to provide the end-user experience. In the future, this will be split up into two more sections: the kernel and the shell.

## Compiling
In order to build the system on a Debian-based OS, you must first install the dependencies.
* **GNU Make:** `sudo apt-get install make`
* **NASM:** `sudo apt-get install nasm`
* **GCC Cross-Compiler:** [`http://wiki.osdev.org/GCC_Cross-Compiler`](http://wiki.osdev.org/GCC_Cross-Compiler)
* **GNU Xorriso:** `sudo apt-get install xorriso`
* **QEMU** (technically not part of the build process): `sudo apt-get install qemu`

Now simply run the makefile.
```bash
make build
```

You can run an emulator using
```bash
make vm
```

When you're all finished, delete all compiled files using
```bash
make clean
```

You can also do all three in that order automatically with
```bash
make all
```
