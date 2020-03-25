# Building the Kernel

To build the kernel, run `make`.

#### Phony Targets

- `make` and `make all`: aliased to `make kernel.bin`
- `make clean`: delete all object files, dependencies files, and `kernel.bin` and `kernel.gz`
- `make dist` and `make tar`: first runs `make clean`, then creates an archive containing all files
- `make todolist`: outputs all lines containing "TODO" in the project, excluding the Makefile

## Common Problems

#### i686-elf-gcc not found

```
make: i686-elf-gcc: Command not found
Makefile:48: recipe for target 'kernel/kernel.c.o' failed
make: *** [kernel/kernel.c.o] Error 127
```

This means that you either haven't installed a cross-compiler, or it's not set up correctly. For help, see [cross-compiler.md](https://github.com/davidaylaian/carbon/blob/master/doc/cross-compiler.md).
