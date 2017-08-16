/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <stdio.h>

size_t xpos = 0;
size_t ypos = 0;

// clears the screen
static inline void cls()   // the void is infinite
{
	for (size_t i = 0; i < getTerminalWidth() * getTerminalHeight(); i++) {
		setChar(0x0, i, 0);
	}

	xpos = 0;
	ypos = 0;
	updateCursor(0,0);
}

// scrolls up
static inline void scroll()
{
	xpos = 0;

	if (ypos+1 == getTerminalHeight())
	{
		for (size_t i=0; i < getTerminalWidth() * getTerminalHeight(); i++) {
			setChar(
				getChar(i + getTerminalWidth(), 0),
				i, 0
			);
		}
	}
	else {
		ypos++;
	}
}

// prints a character to stdout
static void printch(char c)
{
	switch(c)
	{
		// alert
		case '\a': {
			// nothing for now; we have no audio drivers
			break;
		}

		// backspace
		case '\b': {
			if(xpos == 0)
			{
				if(ypos != 0)
				{
					xpos = getTerminalWidth() - 1;
					ypos--;
					setChar(' ', xpos, ypos);
				}
			}
			else {
				xpos--;
				setChar(' ', xpos, ypos);
			}

			break;
		}

		// formfeed
		case '\f': {
			cls();
			break;
		}

		// newline
		case '\n': {
			scroll();
			break;
		}

		// carriage return
		case '\r': {
			xpos = 0;
			break;
		}

		// tab
		case '\t': {
			xpos += 8-(xpos % 8);
			break;
		}

		// vertical tab
		case '\v': {
			ypos += 8-(ypos % 8);
			break;
		}

		// normal character
		default: {
			setChar(c, xpos, ypos);
			xpos++;
			break;
		}
	}

	// if we are out of room, make more room
	if (xpos == getTerminalWidth()) scroll();
}

// prints a string to stdout
void print(char* str)
{
	const size_t length = strlen(str);

	for (size_t i = 0; i < length; i++) {
		printch(str[i]);
	}

	updateCursor(xpos, ypos);
}

// prints a va_list argument list in the given format
void vprintf(char* format, va_list args)
{
	const size_t length = strlen(format);

	// for every character in string
	for (size_t i=0; i < length; i++)
	{
		if (format[i] == '%')
		{
			switch (format[i+1])
			{
				// %% = %
				case '%': {
					printch('%');
					break;
				}

				// character
				case 'c': {
					printch(va_arg(args, char));
					break;
				}

				// string
				case 's': {
					print(va_arg(args, char*));
					break;
				}

				// decimal
				case 'i':
				case 'd': {
					char buf[8] = {0};
					print(itoa(va_arg(args, int), buf, 10));
					break;
				}

				// hex
				case 'X':
				case 'x': {
					char buf[8] = {0};
					print("0x");
					print(itoa(va_arg(args, int), buf, 16));
					break;
				}

				// binary
				case 'b': {
					char buf[8] = {0};
					print("0b");
					print(itoa(va_arg(args, int), buf, 2));
					break;
				}

				// octal
				case 'o': {
					char buf[8] = {0};
					printch('0');
					print(itoa(va_arg(args, int), buf, 8));
					break;
				}

				// invalid format
				default: break;
			}

			i++;
		}

		else printch(format[i]);
	}

	updateCursor(xpos, ypos);
}

// prints an ellipsis argument list in the given format
void printf(char* format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
