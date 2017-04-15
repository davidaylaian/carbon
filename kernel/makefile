OBJS=		\
start.o		\
main.o		\

build:
	$(AS) $(ASFLAGS) start.asm	-o start.o
	$(CC) $(CFLAGS)  main.c	-o main.o

clean:
	rm -f $(OBJS)
