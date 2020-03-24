/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <stdio.h>
#include <terminal.h>

void putchar(char c)
{
	terminal_write_char(c);
}
