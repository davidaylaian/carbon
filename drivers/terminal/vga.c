#include <drivers/terminal.h>

// variables
const volatile size_t TERMINAL_WIDTH	= 80;
const volatile size_t TERMINAL_HEIGHT	= 25;
volatile uint16_t* vidmem = (uint16_t*) 0xB8000;
uint8_t terminal_color;

/* Please refer to the FreeVGA project for	*/
/* details on the following three functions.	*/

static void setMaximumScanLine(uint8_t fontheight)
{
	outb(CRCT_ADDRESS, 0x09);
	outb(CRCT_DATA, fontheight);
}

static void disableCursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0b00100000);
}

static void enableCursor(uint8_t top, uint8_t bottom)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, inb(0x3D5) & 0xC0 | top);
	
	outb(0x3D4, 0x0B);
	outb(0x3D5, inb(0x3E0) & 0xE0 | bottom);
}

// returns width of terminal
size_t getTerminalWidth() {
	return TERMINAL_WIDTH;
}

// returns height of terminal
size_t getTerminalHeight() {
	return TERMINAL_HEIGHT;
}

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
void setColor(enum TERMINAL_COLOR fgcolor, enum TERMINAL_COLOR bgcolor)
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

// installs driver
void installTerminal(uint8_t cursorSize)
{
	uint8_t fontheight = 16;
	
	setMaximumScanLine(fontheight-1);
	enableCursor(fontheight - cursorSize - 3, fontheight - 3);
	setColor(WHITE, BLACK);
}
