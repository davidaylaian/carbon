OBJS=		\
main.o		\

build:
	$(MAKE) -C arch build
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	$(MAKE) -C arch clean
	rm -f $(OBJS)
