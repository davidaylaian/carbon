# Carbon
Carbon is an open-source operating system designed to run on x86-based computers.

## Organization
Carbon is organized into four sections:

* **The [Drivers](drivers):** low-level, hardware-dependent drivers that provide an abstraction layer between the hardware and the library. This section contains all of the files that only work on specific hardware, allowing the rest of the system to be portable.

* **The [Library](library):** the high-level library that provides an abstraction layer between the drivers and the kernel. The library is completely independent from hardware. The Carbon library differs from the standard C library, but most of the functions are similar if not the same.

* **The [Headers](include):** the header files for both the drivers and library that can be linked with an `#include`. The library headers are stored directly in [include](include). The driver headers are placed into [include/drivers](include/drivers) so that `drivers/<feature>/<hardware>.c` will provide code for all of the functions in the respective `include/drivers/<feature>.h` for the specified hardware device.

* **The [Kernel](kernel):** the kernel that uses the library to provide the end-user experience. In the future, this will be split up into two more sections: the kernel and the shell.

## Compiling
###### Note: this section was written for use on [Debian-based](https://www.debian.org) systems. Please submit us an [issue](issues) for instructions on how to build Carbon on other systems.

#### Step 1: Clone the repository

```bash
git clone https://github.com/DavidAylaian/Carbon.git
cd Carbon
```

#### Step 2: Install dependencies

* GNU Make: `sudo apt-get install make`
* NASM: `sudo apt-get install nasm`
* GCC Cross-Compiler: [`http://wiki.osdev.org/GCC_Cross-Compiler`](http://wiki.osdev.org/GCC_Cross-Compiler)
* GNU Xorriso: `sudo apt-get install xorriso`
* QEMU: `sudo apt-get install qemu`

#### Step 3: Build the system
The system can be built via. `make`:

```bash
# build system
make build

# run a virtual machine
make vm

# clean up everything made with build
make clean

# do all three in that order
make all
```
