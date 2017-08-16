# Carbon
Carbon is an open-source operating system designed to run on x86-based computers.

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
