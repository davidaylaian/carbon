/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <vga.h>

static const volatile uint16_t VGA_WIDTH = 80;
static const volatile uint16_t VGA_HEIGHT = 25;
static volatile uint16_t *vidmem = (uint16_t*) 0xB8000;
static uint8_t vga_color;

// get the terminal width
uint16_t vga_get_width()
{
	return VGA_WIDTH;
}

// get the terminal height
uint16_t vga_get_height()
{
	return VGA_HEIGHT;
}

// set the maximum scanline
void vga_set_max_scanline(uint8_t scanline)
{
	outb(0x3D4, 0x09);
	outb(0x3D5, scanline);
}

// enable the cursor
void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

// disable the cursor
void vga_disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

// sets the cursor's position to xpos, ypos
void vga_set_cursor_pos(uint16_t xpos, uint16_t ypos)
{
	uint16_t pos = ypos * VGA_WIDTH + xpos;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

// changes the color
void vga_set_color(enum VGA_COLORS fgcolor, enum VGA_COLORS bgcolor)
{
	vga_color = fgcolor | bgcolor << 4;
}

// sets xpos, ypos to c
void vga_set_char(char c, uint16_t xpos, uint16_t ypos)
{
	vidmem[ypos * VGA_WIDTH + xpos] = c | vga_color << 8;
}

// gets the char at xpos, ypos
char vga_get_char(uint16_t xpos, uint16_t ypos)
{
	return vidmem[ypos * VGA_WIDTH + xpos];
}
