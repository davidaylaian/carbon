/**
 * 
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/CarbonOS/
 * 
 */

#include <keyboard.h>

// converts scancode to ascii (stub)
char scancode_to_ascii(uint8_t scancode)
{
	return 0;
}

// handles the keyboard interrupt
void keyboard_handler()
{
	keypress = scancode_to_ascii(inb(0x60));
	printfln("%c", keypress);
}

// install the keyboard handler
void keyboard_install()
{
	irq_handler_install(1, keyboard_handler);
}
