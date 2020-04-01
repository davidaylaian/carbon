/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <kernel/terminal.h>

int vprintf(const char* format, va_list args)
{
	int res = 0;
	for (size_t i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			putchar(format[i]);
			res++;
		}
		else
		{
			switch (format[++i])
			{
				case '%':
				{
					putchar('%');
					res++;
					break;
				}

				case 'c':
				{
					putchar(va_arg(args, int));
					res++;
					break;
				}

				case 's':
				{
					char* str = va_arg(args, char*);
					terminal_print(str);
					res += strlen(str);
					break;
				}

				case 'i':
				case 'd':
				{
					char buf[12] = {0};
					terminal_print(itoa(va_arg(args, int), buf, 10));
					res += strlen(buf);
					break;
				}

				case 'u':
				{
					char buf[12] = {0};
					terminal_print(itoa(va_arg(args, unsigned int), buf, 10));
					res += strlen(buf);
					break;
				}

				case 'X':
				case 'x':
				{
					char buf[12] = {0};
					//terminal_print("0x");
					//res += 2;
					terminal_print(itoa(va_arg(args, int), buf, 16));
					res += strlen(buf);
					break;
				}

				case 'b':
				{
					char buf[12] = {0};
					terminal_print("0b");
					res += 2;
					terminal_print(itoa(va_arg(args, int), buf, 2));
					res += strlen(buf);
					break;
				}

				case 'o':
				{
					char buf[12] = {0};
					putchar('0');
					res += 1;
					terminal_print(itoa(va_arg(args, int), buf, 8));
					res += strlen(buf);
					break;
				}

				case 'n':
				{
					int *tmp = (int*) va_arg(args, int);
					*tmp = res;
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

	return res;
}
