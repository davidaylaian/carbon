#include <hal.h>
#include <stdio.h>

void kmain()
{
	terminal_install(1, WHITE, BLACK);
	hal_install();
	printf("\f");
	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	enable();
}
