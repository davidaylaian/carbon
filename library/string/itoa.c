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

// converts interger to string
char* itoa(int32_t n, char* str, size_t base)
{
	if (n == 0) return "0";
	
	size_t i = 0;
	bool isNegative = false;
	
	// negative numbers (only in base 10)
	if (n < 0 && base == 10)
	{
		isNegative = true;
		n = -n;
	}
	
	// conversion
	while (n)
	{
		size_t rem = n % base;
		str[i++] = (rem > 9) ? (rem-10) + 'a' : rem + '0';
		n = n/base;
	}
	
	if (isNegative) str[i++] = '-';
	str = strrev(str);
	return str;
}
