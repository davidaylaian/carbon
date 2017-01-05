#ifndef TERMINAL_H
#define TERMINAL_H

#include <asm.h>
#include <stddef.h>
#include <stdint.h>

// color constants
enum TERMINAL_COLOR {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GRAY = 7,
	DARK_GRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15
};

extern size_t getTerminalWidth();
extern size_t getTerminalHeight();
extern void setColor(enum TERMINAL_COLOR fgcolor, enum TERMINAL_COLOR bgcolor);
extern void setChar(char c, size_t xpos, size_t ypos);
extern char getChar(size_t xpos, size_t ypos);

#endif
