#include <hal.h>
#include <stdio.h>

void kmain()
{
	terminal_install(1, WHITE, BLACK);
	hal_install();
	printf("\f");
	enable();
}
