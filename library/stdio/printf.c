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
		case '\a': {		// alert
			// nothing for now; we have no audio drivers
			break;
		}
		
		case '\b': {		// backspace
			xpos--;
			setChar(' ', xpos, ypos);
			break;
		}
		
		case '\f': {		// formfeed
			cls();
			break;
		}
		
		case '\n': {		// newline
			scroll();
			break;
		}
		
		case '\r': {		// carriage return
			xpos = 0;
			break;
		}
		
		case '\t': {		// tab
			xpos += 8-(xpos % 8);
			break;
		}
		
		case '\v': {		// vertical tab
			ypos += 8-(ypos % 8);
			break;
		}
		
		default: {		// normal character
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
				case 'c': {				// character
					printch(va_arg(args, char));
					i++;
					break;
				}
				
				case 's': {				// string
					print(va_arg(args, char*));
					i++;
					break;
				}
				
				case '%': {				// %% = %
					printch('%');
					i++;
					break;
				}
				
				default: {				// invalid format; do nothing
					i++;
					break;
				}
			}
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
	vprintfln(format, args);
	va_end(args);
}
