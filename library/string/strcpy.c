#include <stdio.h>

char *strcpy(char *dest, const char *src)
{
	char *dest2 = dest;
	while ((*dest2++ = *src++));
	return dest;
}
