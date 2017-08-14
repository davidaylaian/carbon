OBJS=		\
kmain.o		\

build:
	$(MAKE) -C arch build
	$(CC) $(CFLAGS) kmain.c -o kmain.o

clean:
	$(MAKE) -C arch clean
	rm -f $(OBJS)
