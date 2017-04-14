OBJS=		\
asm.o		\
gdt_load.o	\
gdt.o		\

build:
	$(CC)  $(CFLAGS)  asm.c		-o asm.o
	$(ASM) $(ASFLAGS) gdt_load.asm	-o gdt_load.o
	$(CC)  $(CFLAGS)  gdt.c		-o gdt.o
	$(CC)  $(CFLAGS)  hal.c		-o hal.o

clean:
	rm -f $(OBJS)
