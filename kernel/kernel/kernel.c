/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <kernel/hal.h>
#include <stdio.h>
#include <kernel/terminal.h>

void kernel_main()
{
	terminal_install();
	hal_initialize();
	printf("kernel_main()\n");
}
