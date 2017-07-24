/**
 * 
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/CarbonOS/
 * 
 */

#include <keyboard.h>

// converts scancode to ascii
// see http://wiki.osdev.org/Keyboard#Scan_Code_Sets
char scancode_to_ascii[128] =
{
	// normal keys
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*',
	0, ' ', 0,
	
	// function keys
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
	// lock keys
	0, 0,
	
	// keypad
	'7', '8', '9', '-',
	'4', '5', '6', '+',
	'1', '2', '3',
	'0', '.',
	
	// function keys
	0, 0, 0,
	0, 0,
	0, 0, 0, 0
};

// handles the keyboard interrupt
void keyboard_handler()
{
	uint8_t scancode = inb(0x60);
	//printf("%x ", scancode);
	
	if(scancode < 0x81) {
		char keypress = scancode_to_ascii[scancode];
		printf("%c", keypress);
	}
}

// install the keyboard handler
void keyboard_install()
{
	irq_handler_install(1, keyboard_handler);
}
