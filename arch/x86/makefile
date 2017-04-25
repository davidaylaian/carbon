OBJS=		\
asm.o		\
gdt_load.o	\
gdt.o		\
hal.o		\
idt.o		\

build:
	$(CC) $(CFLAGS)  asm.c		-o asm.o
	$(AS) $(ASFLAGS) gdt_load.asm	-o gdt_load.o
	$(CC) $(CFLAGS)  gdt.c		-o gdt.o
	$(CC) $(CFLAGS)  hal.c		-o hal.o
	$(CC) $(CFLAGS)  idt.c		-o idt.o

clean:
	rm -f $(OBJS)
