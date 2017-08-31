/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <keyboard.h>

bool sequence = 0;

static char keymap_us[0x54] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
	'[', ']', '\n', 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
	';', '\'', '`', 0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm',
	',', '.', '/', 0, '*', 0, ' ', 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	'7', '8', '9', '-',
	'4', '5', '6', '+',
	'1', '2', '3', '0', '.'
};

// handles the keyboard interrupt
static void keyboard_handler()
{
	uint8_t scancode = inb(0x60);

	if(sequence) {
		sequence = 0;
	} else {
		if(scancode < 0x54) {
			char c = keymap_us[scancode];
			if(c) printf("%c", c);
		} else if(scancode == 0xE0) {
			sequence = 1;
		}
	}
}

// install the keyboard handler
void keyboard_install()
{
	irq_handler_install(1, keyboard_handler);
}
