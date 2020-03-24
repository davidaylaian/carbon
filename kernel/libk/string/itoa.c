/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// TODO: Switch to using an itoa based off of this one: http://www.strudel.org.uk/itoa/

char* itoa(int n, char* str, int base)
{
	if (!n)
	{
		return (char*) "0";
	}

	int i = 0;
	bool negative = false;

	// handle negative numbers
	if (n < 0 && base == 10)
	{
		negative = true;
		n = -n;
	}

	// string to int conversion
	while (n)
	{
		int rem = n % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		n /= base;
	}

	if (negative)
	{
		str[i] = '-';
	}

	str = strrev(str);
	return str;
}
