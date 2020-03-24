/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <string.h>

char* strrev(char* str)
{
	size_t start = 0;
	size_t end = strlen(str) - 1;
	char swap;

	while (start < end)
	{
		swap = str[start];
		str[start] = str[end];
		str[end] = swap;

		start++;
		end--;
	}

	return str;
}
