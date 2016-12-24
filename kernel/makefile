# object files
OBJS=			\
start.o			\
main.o			\

build:
	$(ASM) $(ASFLAGS) start.asm	-o start.o
	$(CC)  $(CFLAGS)  main.c	-o main.o

clean:
	rm -f $(OBJS)
