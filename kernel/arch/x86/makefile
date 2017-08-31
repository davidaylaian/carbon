OBJS=		\
start.o		\

build:
	$(MAKE) -C hal build
	$(AS) $(ASFLAGS) start.asm -o start.o

clean:
	$(MAKE) -C hal clean
	rm -f $(OBJS)
