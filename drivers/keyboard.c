#include <keyboard.h>

static void keyboard_handler()
{
	uint8_t scan_code = inb(0x60);
	printfln("%d", scan_code);
}

void keyboard_install()
{
	irq_handler_install(1, keyboard_handler);
}
