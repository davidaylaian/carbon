OBJS=		\
kmain.o		\

build:
	$(MAKE) -C arch build
	$(MAKE) -C drivers build
	$(CC) $(CFLAGS) kmain.c -o kmain.o

clean:
	$(MAKE) -C arch clean
	$(MAKE) -C drivers clean
	rm -f $(OBJS)
