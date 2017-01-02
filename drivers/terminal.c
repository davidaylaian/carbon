#include <terminal.h>

// variables
const size_t TERMINAL_WIDTH	= 80;
const size_t TERMINAL_HEIGHT	= 25;
uint16_t* vidmem = (uint16_t*) 0xB8000;
uint8_t terminal_color;

// sets cursor location to xpos, ypos
void updateCursor(size_t xpos, size_t ypos)
{
	// calculate where cursor should be
	uint16_t position = ypos * TERMINAL_WIDTH + xpos;
	
	// send bytes
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((position >> 8) & 0xFF));
}

// changes the color of outputted text
void setColor(enum vga_color fgcolor, enum vga_color bgcolor)
{
	terminal_color = (fgcolor | bgcolor << 4);
}

// displays c to xpos, ypos
void setChar(char c, size_t xpos, size_t ypos)
{
	vidmem [ypos * TERMINAL_WIDTH + xpos] = (c | terminal_color << 8);
}

// gets the char at xpos, ypos
char getChar(size_t xpos, size_t ypos)
{
	return vidmem [ypos * TERMINAL_WIDTH + xpos];
}