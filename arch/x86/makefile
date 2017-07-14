OBJS=		\
asm.o		\
wrappers.o	\
gdt_load.o	\
gdt.o		\
idt.o		\
pic.o		\
isr.o		\
irq.o		\
hal.o		\

build:
	$(AS) $(ASFLAGS) gdt_load.asm	-o gdt_load.o
	$(AS) $(ASFLAGS) wrappers.asm 	-o wrappers.o
	$(CC) $(CFLAGS)  asm.c		-o asm.o
	$(CC) $(CFLAGS)  gdt.c		-o gdt.o
	$(CC) $(CFLAGS)  idt.c		-o idt.o
	$(CC) $(CFLAGS)  pic.c		-o pic.o
	$(CC) $(CFLAGS)  isr.c		-o isr.o
	$(CC) $(CFLAGS)  irq.c		-o irq.o
	$(CC) $(CFLAGS)  hal.c		-o hal.o

clean:
	rm -f $(OBJS)
