OBJS=		\
main.o		\

build:
	$(MAKE) -C arch build
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm -f $(OBJS)
