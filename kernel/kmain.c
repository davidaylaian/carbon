/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <vga.h>
#include <hal.h>
#include <stdio.h>

void kmain()
{
	// screen
	vga_enable_cursor(12, 13);
	vga_set_color(COLOR_WHITE, COLOR_BLACK);
	printf("\f");

	// interrupts
	hal_install();
	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	enable();
	keyboard_install();
}
