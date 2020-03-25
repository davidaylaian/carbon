# Setting up the GCC Cross-Compiler

In order to build Carbon, you need to have a cross-compiler. GCC is the compiler that we use, so these instructions will install GCC.

## Part 1: Preliminaries and Dependencies

First, decide where to install the cross-compiler, what versions of software to use, and what languages you want your cross compiler to support.

```sh
# the cross compiler will be installed to $INSTALL/cross
INSTALL="/usr/local"

# software versions
BINUTILS_VERSION="2.31.1"
GCC_VERSION="8.3.0"

# languages, seperated by commas
# valid languages are ada, c, c++, fortran, go, jit, lto, objc, and obj-c++
LANGUAGES="c,c++"

# number of jobs
JOBS=$(nproc)
```

Now, we need to make the working directory where we will install the compiler.

```sh
cd $INSTALL
sudo mkdir cross
cd cross
```

Before building anything, install the necessary dependencies. On a system that uses `apt`, this looks like this:

```sh
sudo apt-get update
sudo apt-get install gcc g++ make bison flex gawk libgmp3-dev libmpfr-dev libmpfr4 libmpfr4-dbg libmpc-dev texinfo libcloog-isl-dev build-essential gcc-multilib libc6-i386
```

On other systems, you will have to find the equivalent packages.

## Part 2: Building the Compiler

Download and unpack binutils and GCC...


```sh
sudo wget http://ftpmirror.gnu.org/binutils/binutils-$BINUTILS_VERSION.tar.gz
sudo wget http://ftpmirror.gnu.org/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz
for f in *.tar*; do sudo tar zvxf $f; done
sudo rm -f binutils-$BINUTILS_VERSION.tar.gz
sudo rm -f gcc-$GCC_VERSION.tar.gz
```

...and create the installation directory.

```sh
sudo mkdir install
export PREFIX="$INSTALL/cross/install"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```

In every session that you use the cross-compiler, you will need to re-export `PATH`. It is reccomended to simply add it to your `.bashrc`. For example, if you are installing the cross compiler at `/usr/local/cross`, then add

```sh
export PATH="/usr/local/cross/install/bin:$PATH"
```

to `.bashrc`. Now, it is time to build and install binutils and GCC themselves. This will take a while. Binutils comes first.

```sh
sudo mkdir build-binutils
cd build-binutils
sudo ../binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
sudo make -j $JOBS
sudo make -j $JOBS install
cd ..
```

Finally, GCC.

```sh
sudo mkdir build-gcc
cd build-gcc
sudo ../gcc-$GCC_VERSION/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=$LANGUAGES --without-headers
sudo make -j $JOBS all-gcc
sudo make -j $JOBS all-target-libgcc
sudo make -j $JOBS install-gcc
sudo make -j $JOBS install-target-libgcc
cd ..
```

If everything went right, you now have your very own cross-compiler! You can delete the `binutils-$BINUTILS_VERSION` and `gcc-$GCC_VERSION` folders if desired; they don't do anything. More likely though, something went wrong. Some of the more common issues are using incompatible versions of binutils and GCC and not installing all of the prerequisites. The [OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler) also has multiple articles on cross-compilers that might be useful. Good luck!
