#ifndef TERMINAL_H
#define TERMINAL_H

#include <hal.h>
#include <stddef.h>
#include <stdint.h>

// terminal size
static const volatile size_t TERMINAL_WIDTH	= 80;
static const volatile size_t TERMINAL_HEIGHT	= 25;

// returns width of terminal
static inline size_t getTerminalWidth() {
	return TERMINAL_WIDTH;
}

// returns height of terminal
static inline size_t getTerminalHeight() {
	return TERMINAL_HEIGHT;
}

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

// ports
#define CRCT_ADDRESS	0x3D4
#define CRCT_DATA	0x3D5

// function prototypes
extern void updateCursor(size_t xpos, size_t ypos);
extern void setColor(enum TERMINAL_COLOR fgcolor, enum TERMINAL_COLOR bgcolor);
extern void setChar(char c, size_t xpos, size_t ypos);
extern char getChar(size_t xpos, size_t ypos);
extern void installTerminal(uint8_t cursorSize);

#endif
