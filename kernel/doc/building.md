# Building the Kernel

To build the kernel, run `make`.

## Common Problems

### i686-elf-gcc not found

```
make: i686-elf-gcc: Command not found
Makefile:48: recipe for target 'kernel/kernel.c.o' failed
make: *** [kernel/kernel.c.o] Error 127
```

This means that you either haven't installed a cross compiler, or it's not set up correctly. For help, see [http://wiki.osdev.org/GCC_Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler).
