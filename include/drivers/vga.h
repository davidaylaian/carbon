/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#ifndef DRIVERS_TERMINAL_H
#define DRIVERS_TERMINAL_H

#include <hal.h>
#include <stddef.h>
#include <stdint.h>

// color constants
enum VGA_COLORS {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GRAY = 7,
	COLOR_DARK_GRAY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15
};

extern uint16_t vga_get_width();
extern uint16_t vga_get_height();
extern void vga_set_max_scanline(uint8_t scanline);
extern void vga_enable_cursor(uint8_t cursor_top, uint8_t cursor_bottom);
extern void vga_disable_cursor();
extern void vga_set_cursor_pos(uint16_t xpos, uint16_t ypos);
extern void vga_set_color(enum VGA_COLORS fgcolor, enum VGA_COLORS bgcolor);
extern void vga_set_char(char c, uint16_t xpos, uint16_t ypos);
extern char vga_get_char(uint16_t xpos, uint16_t ypos);

#endif
