#ifndef TERMINAL_H
#define TERMINAL_H

#include <asm.h>
#include <stddef.h>
#include <stdint.h>

// color constants
enum vga_color {
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

// variables
extern const size_t TERMINAL_WIDTH;
extern const size_t TERMINAL_HEIGHT;

// inline functions
inline size_t getTerminalWidth() {
	return TERMINAL_WIDTH;
}

inline size_t getTerminalHeight() {
	return TERMINAL_HEIGHT;
}

// function prototypes
extern void updateCursor(int xpos, int ypos);
extern void setColor(enum vga_color fgcolor, enum vga_color bgcolor);
extern void setChar(char c, uint8_t xpos, uint8_t ypos);
extern char getChar(uint8_t xpos, uint8_t ypos);

#endif
