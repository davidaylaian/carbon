/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <kernel/hal.h>
#include <kernel/terminal.h>
#include <stdio.h>
#include <string.h>

void kernel_main()
{
	terminal_install();
	hal_initialize();
	printf("kernel_main()\n");
	enable();

	/*while (1)
	{
		char* str = "         ";
		printf("get_timer_tick() = %s\n", itoa(get_timer_tick(), str, 10));
	}*/
}
