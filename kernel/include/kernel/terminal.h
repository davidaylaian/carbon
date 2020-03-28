/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <attribute.h>
#include <stddef.h>
#include <stdint.h>

// terminal size
size_t terminal_width();
size_t terminal_height();

// cursor
void terminal_cursor_enable();
void terminal_cursor_disable();
void terminal_cursor_shape(uint8_t scanline_start);
void terminal_set_cursor_pos(size_t x, size_t y);
void terminal_get_cursor_pos(size_t* x, size_t* y);

// screen I/O
char terminal_set_char(char c, size_t x, size_t y);
char terminal_get_char(size_t x, size_t y);
char terminal_write_char(char c);
void terminal_write(const char* data, size_t len);
void terminal_print(const char* str);

// miscellaneous
void terminal_install();

#endif
