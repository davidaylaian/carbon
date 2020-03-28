/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <attribute.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/hal.h>

// TODO: Add a way to change the terminal color

static const uint8_t MAX_SCANLINE = 16;
static const size_t TERMINAL_WIDTH  = 80;
static const size_t TERMINAL_HEIGHT = 25;
static const uint8_t HORIZ_TAB_SIZE = 8;
static const uint8_t VERT_TAB_SIZE = 8;

size_t terminal_width()
{
	return TERMINAL_WIDTH;
}

size_t terminal_height()
{
	return TERMINAL_HEIGHT;
}

static size_t xpos;
static size_t ypos;
static uint8_t cursor_start;
static bool cursor_enabled;

static void terminal_update_cursor()
{
	uint16_t pos = ypos * TERMINAL_WIDTH + xpos;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_cursor_enable()
{
	cursor_enabled = 1;
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | (MAX_SCANLINE - 1));
}

void terminal_cursor_disable()
{
	cursor_enabled = 0;
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void terminal_cursor_shape(uint8_t scanline_start)
{
	cursor_start = scanline_start;

	if (cursor_start >= MAX_SCANLINE)
	{
		cursor_start = MAX_SCANLINE - 1;
	}

	if (cursor_enabled)
	{
		terminal_cursor_enable();
	}
}

void terminal_set_cursor_pos(size_t x, size_t y)
{
	xpos = x;
	ypos = y;

	if (xpos >= TERMINAL_WIDTH)
	{
		xpos = TERMINAL_WIDTH - 1;
	}

	if (ypos >= TERMINAL_HEIGHT)
	{
		ypos = TERMINAL_HEIGHT - 1;
	}

	terminal_update_cursor();
}

void terminal_get_cursor_pos(size_t* x, size_t* y)
{
	*x = xpos;
	*y = ypos;
}

static uint16_t *vidmem = (uint16_t*) 0xB8000;
static uint8_t terminal_color = 0b00001111; // white on black

void terminal_set_char(char c, size_t x, size_t y)
{
	vidmem[y * TERMINAL_WIDTH + x] = c | terminal_color << 8;
}

char terminal_get_char(size_t x, size_t y)
{
	return vidmem[y * TERMINAL_WIDTH + x];
}

static void terminal_clear()
{
	xpos = 0;
	ypos = 0;

	for (size_t i = 0; i < TERMINAL_HEIGHT * TERMINAL_WIDTH; i++)
	{
		vidmem[i] = ' ' | terminal_color << 8;
	}
}

// write a character without updating the cursor
static void terminal_write_char_internal(char c)
{
	switch (c)
	{
		// carriage return
		case '\r':
			xpos = 0;
			break;

		// newline
		case '\n':
			xpos = 0;
			ypos++;
			break;

		// tab
		case '\t':
			xpos += HORIZ_TAB_SIZE - xpos % HORIZ_TAB_SIZE;
			break;

		// vertical tab
		case '\v':
			ypos += VERT_TAB_SIZE - ypos % VERT_TAB_SIZE;
			break;

		// backspace
		case '\b':
			// TODO: Support backspace character
			break;

		// formfeed
		case '\f':
			terminal_clear();
			break;

		// alarm
		case '\a':
			// TODO: We have no audio drivers
			break;

		default:
			terminal_set_char(c, xpos, ypos);
			xpos++;
			break;
	}

	// start new line if we are out of room on the current line
	if (xpos == TERMINAL_WIDTH)
	{
		xpos = 0;
		ypos++;
	}

	// scroll if we are out of room on all lines
	if (ypos == TERMINAL_HEIGHT)
	{
		ypos--;
		for (size_t i = 0; i < TERMINAL_HEIGHT; i++)
		{
			vidmem[i] = vidmem[i + TERMINAL_HEIGHT];
		}
	}
}

// write a character to the terminal
void terminal_write_char(char c)
{
	terminal_write_char_internal(c);
	terminal_update_cursor();
}

// write len bytes of data to the terminal
void terminal_write(const char* data, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		terminal_write_char_internal(data[i]);
	}

	terminal_update_cursor();
}

// write a null-terminated string to the terminal
void terminal_print(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		terminal_write_char_internal(str[i]);
	}

	terminal_update_cursor();
}

static void terminal_max_scanline(uint8_t scanline)
{
	outb(0x3D4, 0x09);
	outb(0x3D5, scanline);
}

void terminal_install()
{
	xpos = 0;
	ypos = 0;
	cursor_start = 12;
	cursor_enabled = 1;

	terminal_max_scanline(MAX_SCANLINE);
	terminal_clear();
	terminal_cursor_enable();
	terminal_update_cursor();
}
