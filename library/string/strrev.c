/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <string.h>

char *strrev(char *str)
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
