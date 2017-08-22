#include <stdio.h>

// writes a string and a newline to stdout
void puts(const char *str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		putchar(str[i]);
	}

	putchar('\n');
}
