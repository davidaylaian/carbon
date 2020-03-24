CC := i686-elf-gcc
AS := nasm

CWARNINGS := -Wall -Wextra -Wshadow -Wcast-align -Wwrite-strings -Wredundant-decls -Winline
CFLAGS := -std=gnu11 -ffreestanding -O3 -I include -nostdlib -nostdinc -fno-builtin -masm=intel -lgcc $(CWARNINGS)
ASFLAGS := -w+orphan-labels

# TODO: potentially place object and dependency files into obj and dep directories

PROJDIRS := include kernel libk
SRCFILES := $(shell find $(PROJDIRS) -type f -name '*.c')
HDRFILES := $(shell find $(PROJDIRS) -type f -name '*.h')
DOCFILES := $(shell find . -type f -name '*.md')
OBJFILES := $(patsubst %.c, %.c.o, $(SRCFILES))
DEPFILES := $(patsubst %.c, %.c.d, $(SRCFILES))
ASMSRCFILES := $(shell find $(PROJDIRS) -type f -name '*.asm')
ASMOBJFILES := $(patsubst %.asm, %.asm.o, $(ASMSRCFILES))
ASMDEPFILES := $(patsubst %.asm, %.asm.d, $(ASMSRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES) $(ASMSRCFILES) $(DOCFILES) Makefile

.PHONY: all
all: kernel.bin

.PHONY: clean
clean:
	@$(RM) $(wildcard $(OBJFILES) $(ASMOBJFILES) $(DEPFILES) $(ASMDEPFILES) kernel.bin kernel.gz)

.PHONY: dist tar
dist tar: clean
	@tar czf kernel.gz $(ALLFILES)
	@$(info kernel.gz)

.PHONY: todolist
todolist:
	@grep -rnw . -e TODO --exclude Makefile

kernel.bin: Makefile $(OBJFILES) $(ASMOBJFILES)
	@$(CC) -ffreestanding -O3 -nostdlib -lgcc -T kernel/link.ld -o kernel.bin $(filter-out $<, $^)
	@$(info kernel.bin)

%.c.o: %.c Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# TODO: fix assembly circular dependencies
%.asm.o: %.asm Makefile
	@$(AS) $(ASFLAGS) -o $@ -felf32 $<

-include $(DEPFILES)
-include $(ASMDEPFILES)
