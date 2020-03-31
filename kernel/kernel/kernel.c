/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <kernel/hal.h>
#include <kernel/terminal.h>
#include <kernel/keyboard.h>
#include <stdio.h>
#include <string.h>

void kernel_main()
{
	//TODO: MOVE TO DIFFERENT INSTALL
	uint8_t keycode_buffer[1024] = {0};

	terminal_install();
	hal_initialize();

	//TODO: MOVE TO DIFFERENT INSTALL
	keyboard_install(TEXTDUMP, keycode_buffer, 1024);

	//printf("kernel_main()\n");

	// this will be part of pic.c probably later on
	outb(0x21, 0b11111100);
	outb(0xA1, 0b11111111);

	enable();
}
