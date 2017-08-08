/**
 * 
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/CarbonOS/
 * 
 */

#include <drivers/keyboard.h>

static bool sequence = 0;
static volatile uint16_t stdin[256] = {0}; 
static volatile int16_t front = 0;
static volatile int16_t rear = -1;
static volatile int16_t items = 0;

static uint8_t keymap_us[0x59] = {
	KEY_RESERVED,
	KEY_ESC,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_LEFTBRACKET,
	KEY_RIGHTBRACKET,
	KEY_ENTER,
	KEY_LEFTCTRL,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_GRAVE,
	KEY_LEFTSHIFT,
	KEY_BACKSLASH,
	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,
	KEY_COMMA,
	KEY_DOT,
	KEY_SLASH,
	KEY_RIGHTSHIFT,
	KEY_KPAD_ASTERIK,
	KEY_LEFTALT,
	KEY_SPACE,
	KEY_CAPSLOCK,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_NUMLOCK,
	KEY_SCRLOCK,
	KEY_KPAD_7,
	KEY_KPAD_8,
	KEY_KPAD_9,
	KEY_KPAD_MINUS,
	KEY_KPAD_4,
	KEY_KPAD_5,
	KEY_KPAD_6,
	KEY_KPAD_PLUS,
	KEY_KPAD_1,
	KEY_KPAD_2,
	KEY_KPAD_3,
	KEY_KPAD_0,
	KEY_KPAD_DOT,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_F11,
	KEY_F12
};

// add keypress to stdin
static void keyboard_stdin_add(uint16_t keypress)
{
	if(rear == 255) rear = -1;
	stdin[++rear] = keypress;
	items++;
}

// read keypress from stdin
uint16_t keyboard_stdin_read()
{
	while(items == 0);
	
	uint16_t data = stdin[front];
	stdin[front++] = 0;
	if(front == 255) front = 0;
	items--;
	return data;
}

// handles the keyboard interrupt
static void keyboard_handler()
{
	uint8_t scancode = inb(0x60);
	
	if(sequence == 0)
	{
		if(scancode < 0x59) {
			scancode = keymap_us[scancode];
			keyboard_stdin_add(scancode);
		}
		else if(scancode == 0xE0) sequence = 1;
		else if(scancode == 0xE1) keyboard_stdin_add(KEY_PAUSE);
	}
	else
	{
		switch(scancode)
		{
			case 0x1C: {
				keyboard_stdin_add(KEY_KPAD_ENTER);
				break;
			}
			
			case 0x1D: {
				keyboard_stdin_add(KEY_RIGHTCTRL);
				break;
			}
			
			case 0x35: {
				keyboard_stdin_add(KEY_KPAD_SLASH);
				break;
			}
			
			case 0x38: {
				keyboard_stdin_add(KEY_RIGHTALT);
				break;
			}
			
			case 0x47: {
				keyboard_stdin_add(KEY_HOME);
				break;
			}
			
			case 0x48: {
				keyboard_stdin_add(KEY_UP);
				break;
			}
			
			case 0x49: {
				keyboard_stdin_add(KEY_PAGEUP);
				break;
			}
			
			case 0x4B: {
				keyboard_stdin_add(KEY_LEFT);
				break;
			}
			
			case 0x4D: {
				keyboard_stdin_add(KEY_RIGHT);
				break;
			}
			
			case 0x4F: {
				keyboard_stdin_add(KEY_END);
				break;
			}
			
			case 0x50: {
				keyboard_stdin_add(KEY_DOWN);
				break;
			}
			
			case 0x51: {
				keyboard_stdin_add(KEY_PAGEDOWN);
				break;
			}
			
			case 0x52: {
				keyboard_stdin_add(KEY_INSERT);
				break;
			}
			
			case 0x53: {
				keyboard_stdin_add(KEY_DELETE);
				break;
			}
			
			case 0x5D: {
				keyboard_stdin_add(KEY_APPS);
				break;
			}
			
			// key release; ignore
			default: {
				sequence = 0;
				break;
			}
		}
	}
}

// install the keyboard handler
void keyboard_install()
{
	irq_handler_install(1, keyboard_handler);
}
