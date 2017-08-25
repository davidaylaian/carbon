/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <stdio.h>

// prints a string to stdout
static void print(const char *str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		putchar(str[i]);
	}
}

// prints a variable argument list to stdout in the given format
int vprintf(const char *format, va_list args)
{
	int ret = 0;

	for (size_t i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			putchar(format[i]);
			ret++;
		}
		else
		{
			switch (format[++i])
			{
				case '%':
				{
					putchar('%');
					ret++;
					break;
				}

				case 'c':
				{
					putchar(va_arg(args, char));
					ret++;
					break;
				}

				case 's':
				{
					char* tmp = va_arg(args, char*);
					print(tmp);
					ret += strlen(tmp);
					break;
				}

				case 'i':
				case 'd':
				{
					char buf[11] = {0};
					print(itoa(va_arg(args, int), buf, 10));
					ret += strlen(buf);
					break;
				}

				case 'X':
				case 'x':
				{
					char buf[9] = {0};
					print("0x");
					ret += 2;
					print(itoa(va_arg(args, int), buf, 16));
					ret += strlen(buf);
					break;
				}

				case 'b':
				{
					char buf[33] = {0};
					print("0b");
					ret += 2;
					print(itoa(va_arg(args, int), buf, 2));
					ret += strlen(buf);
					break;
				}

				case 'o':
				{
					char buf[12] = {0};
					putchar('0');
					ret += 1;
					print(itoa(va_arg(args, int), buf, 8));
					ret += strlen(buf);
					break;
				}

				case 'n':
				{
					int *tmp = (int*) va_arg(args, int);
					*tmp = ret;
					break;
				}

				default:
				{
					return -1;
					break;
				}
			}
		}
	}

	return ret;
}
