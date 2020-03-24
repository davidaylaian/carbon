/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <stdio.h>
#include <string.h>
#include <terminal.h>

// writes a string plus a newline to stdout
void puts(const char *str)
{
	terminal_write(str, strlen(str));
	terminal_write_char('\n');
}
