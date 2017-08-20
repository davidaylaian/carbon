/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 * Based off of code that can be found at
 * http://www.geeksforgeeks.org/implement-itoa/
 *
 */

#include <string.h>

// converts an interger to a string
char *itoa(int n, char *str, int base)
{
	if (!n)
	{
		return "0";
	}

	int i = 0;
	bool is_negative = false;

	// negative numbers (only in base 10)
	if (n < 0 && base == 10)
	{
		is_negative = true;
		n = -n;
	}

	// conversion
	while (n)
	{
		int32_t rem = n % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		n = n / base;
	}

	if (is_negative)
	{
		str[i] = '-';
	}

	str = strrev(str);
	return str;
}
