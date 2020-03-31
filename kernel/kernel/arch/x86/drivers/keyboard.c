/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 * Code written and modified by Geoffrey Kublin
 * https://github.com/ReewassSquared
 * geoffreykublin@gmail.com
 * 
 * 
 * keyboard.c - contains functions for setting up basic keyboard utilities.
 *
 */

#include <kernel/terminal.h>
#include <kernel/hal.h>
#include <kernel/keyboard.h>
#include <stdbool.h>

volatile struct keyboard_state keyboard_state;

// Layer 1 state
volatile uint32_t __keystate__[8] = {0};
volatile uint32_t __keystate_ext__[8] = {0};
volatile struct keyboard_error __keyerror__;

// static variables used for keycode queue
static volatile int32_t front = -1;
static volatile int32_t rear = -1;
static uint32_t keybuf_size;
static uint8_t *keybuf;

//static methods for keycode queue

static uint8_t enqueue(uint8_t v)
{
	if (((front == 0) && (rear == (int32_t) (keybuf_size - 1)))
			|| (front == rear + 1)) {
		return 255; /* buffer overflow */
	} else {
		if (front == -1) {
			front = 0;
		}
		rear = (rear + 1) % keybuf_size;
		keybuf[rear] = v;
	}

	return 0;
}

static uint8_t dequeue()
{
	uint8_t v;
	if (front == -1) {
		v = 0; /* buffer underflow */
	} else {
		v = keybuf[front];
		if (front == rear) {
			front = (rear = -1);
		} else {
			front = (front + 1) % keybuf_size;
		}
	}

	return v;
}

uint8_t keycode_to_char[128] = 
{
	'\r', '1', '2', '3', '4', '5', '6', '7', 
	'8', '9', '0', '-', '=', '\b', '\t', 'q',
	'w', 'e', 'r', 't', 'y', 'u', 'i', 'o',
	'p', '[', ']', '\n', 'a', 's', 'd', 'f', 
	'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 
	',', '.', '/', '*', ' ', '7', '8', '9',
	'-', '4', '5', '6', '+', '1', '2', '3',
	'0', '.', '\n', '/', 
	0, /* rest are undefined */
};

uint8_t keycode_to_char_shft[128] = 
{
	'\r', '!', '@', '#', '$', '%', '^', '&', 
	'*', '(', ')', '_', '+', '\b', '\t', 'Q',
	'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O',
	'P', '{', '}', '\n', 'A', 'S', 'D', 'F', 
	'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
	'<', '>', '?', '*', ' ', '7', '8', '9',
	'-', '4', '5', '6', '+', '1', '2', '3',
	'0', '.', '\n', '/', 
	0, /* rest are undefined */
};

uint8_t keystate_table[128] = 
{
	0, /* reserved */
	68, /* escape */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, /*1-9, 0*/
	11, /* -/_ key */
	12, /* =/+ key */
	13, /* backspace */
	14, /* tab */
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
	27, /* enter */
	69, /* Left Control */
	28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	70, /* Left Shift */
	40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	71, /* Right Shift */
	51, /* Keypad * */
	72, /* Left Alt */
	52, /* Space */
	73, /* Capslock */
	74, 75, 76, 77, 78, 79, 80, 81, 82, 83, /* F1 - F10 */
	84, /* Number Lock */
	85, /* Scroll Lock */
	53,  /* Keypad 7 (HOME) */
	54,  /* Keypad 8 (ARROW UP) */
	55,  /* Keypad 9 (PGUP) */
	56, /* Keypad - */
	57, /* Keypad 4 (ARROW LEFT) */
	58, /* Keypad 5 */
	59, /* Keypad 6 (ARROW RIGHT) */
	60, /* Keypad + */
	61, /* Keypad 1 (END) */
	62, /* Keypad 2 (ARROW DOWN) */
	63, /* Keypad 3 (PGDN) */
	64, /* Keypad 0 (INS) */
	65, /* Keypad . (DEL) */
	0, 0, 0, /* reserved */
	86, 87, /* F11 and F12 */
	0, /* reserved */
};

uint8_t keystate_ext_table[128] = 
{
	0, 0, 0, 0, 0, 0, 0, 0, /*0x07*/
	0, 0, 0, 0, 0, 0, 0, 0, /*0x0F*/
	88, /* previous track */
	0, 0, 0, 0, 0, 0, 0, /*0x17*/
	0,
	89, /* next track */
	0, 0,
	66, /* keypad enter */
	90, /* right control */
	0, 0, /*0x1F*/
	91, /* mute */
	92, /* calculator */
	93, /* play */
	0,
	94, /* stop */
	0, 0, 0, /*0x27*/
	0, 0, 0, 0, 0, 0,
	95, /* volume down */
	0, /*0x2F*/
	96, /* volume up */
	0,
	97, /* www home */
	0, 0,
	67, /* keypad / */
	0, 0, /*0x37*/
	98, /* right alt */
	0, 0, 0, 0, 0, 0, /*0x3F*/
	0, 0, 0, 0, 0, 0, 0,
	99, /* home */ /*0x47*/
	100, /* cursor up */
	101, /* page up */
	0, 
	102, /* cursor left */
	0,
	103, /* cursor right */
	0,
	104, /* end */ /*0x4F*/
	105, /* cursor down */
	106, /* page down */
	107, /* insert */
	108, /* delete */
	0, 0, 0, 0, /*0x57*/
	0, 0, 0,
	109, /* left GUI */
	110, /* right GUI */
	111, /* apps */
	112, /* ACPI power */
	113, /* ACPI sleep */ /*0x5F*/
	0, 0, 0,
	114, /* ACPI wake */
	0,
	115, /* WWW search */
	116, /* WWW favorites */
	117, /* WWW refresh */ /*0x67*/
	118, /* WWW stop */
	119, /* WWW forward */
	120, /* WWW back */
	121, /* my computer */
	122, /* email */
	123, /* media select */
	0, /* reserved */
};

char keycode_to_text(uint8_t keycode)
{
	char _r;
	if(keycode < 0x80 && keycode_to_char[keycode]) {
		if (keyboard_state.lshft || keyboard_state.rshft) {
			_r = keycode_to_char_shft[keycode];
		} else {
			_r = keycode_to_char[keycode];
		}

		if (keyboard_state.capslock) {
			if ((_r > 0x40) && (_r < 0x5B)) {
				_r += 0x20;
			} else if ((_r > 0x60) && (_r < 0x7B)) {
				_r -= 0x20;
			}
		}

		return _r;
	}

	return '\0';
}

void update_keyboard_state(uint8_t keycode)
{
	char _t;
	if (keyboard_state.halted) {
		return;
	}
	
	switch (keyboard_state.mode) {
	case KEYALL:
		if(enqueue(keycode)) {
		/* throw error */
			keyboard_state.halted = true;
			__keyerror__.halted = true;
		}
		break;
	case KEYDUMP:
		enqueue(keycode);
	case KEYSMASH:
		if (enqueue(keycode)) {
			dequeue();
			enqueue(keycode);
		}
		break;
	case TEXTALL:
		_t = keycode_to_text(keycode);
		if (_t && enqueue((uint8_t) _t)) {
			keyboard_state.halted = true;
			__keyerror__.halted = true;
		}
		break;
	case TEXTDUMP:
		_t = keycode_to_text(keycode);
		if (_t && enqueue((uint8_t) _t)) {}
		break;
	case TEXTSMASH:
		_t = keycode_to_text(keycode);
		if (_t && enqueue((uint8_t) _t)) {
			dequeue();
			enqueue((uint8_t) _t);
		}
		break;
	}
	
	switch (keycode) {
	case 69:
		keyboard_state.lctrl = true; 
		break;
	case 70:
		keyboard_state.lshft = true; 
		break;
	case 71:
		keyboard_state.rshft = true; 
		break;
	case 72:
		keyboard_state.lalt = true; 
		break;
	case 73:
		keyboard_state.capslock ^= 1; 
		break;
	case 84:
		keyboard_state.numlock ^= 1; 
		break;
	case 85:
		keyboard_state.scrolllock ^= 1; 
		break;
	case 90:
		keyboard_state.rctrl = true; 
		break;
	case 98:
		keyboard_state.ralt = true; 
		break;
	case 107:
		keyboard_state.insert ^= 1; 
		break;
	case 108:
		keyboard_state.del = true; 
		break;
	case 125:
		keyboard_state.paused ^= 1; 
		break;
	case 197:
		keyboard_state.lctrl = false; 
		break;
	case 198:
		keyboard_state.lshft = false; 
		break;
	case 199:
		keyboard_state.rshft = false; 
		break;
	case 200:
		keyboard_state.lalt = false; 
		break;
	case 218:
		keyboard_state.rctrl = false; 
		break;
	case 226:
		keyboard_state.ralt = false; 
		break;
	case 236:
		keyboard_state.del = false; 
		break;
	}

	keyboard_state.lastkey = keycode;
}

uint8_t next_keycode()
{
	return dequeue();
}

void keyboard_handler()
{
	/* check status register */
	uint8_t _stat = inb(0x64);
	uint8_t _keycode = 255;

	/* set errors */
	if (_stat & 0x80)
		__keyerror__.parity_error = true;
	if (_stat & 0x40)
		__keyerror__.timeout_error = true;

	/* read from 8042 output buffer */
	if (_stat & 0x01) {
		uint8_t _s = inb(0x60);
		//printf("%x ", _s);
		uint8_t _p;

		/* firstly check if sequence is multibyte */
		if (_s == 0xE0) {
			_s = inb(0x60);
			
			if (_s == 0x2A) {
				if ((inb(0x60) == 0xE0) && (inb(0x60) == 0x37)) {
					_keycode = 124; /* 124 is printscreen's keycode */
				}
			}
			else if (_s == 0xB7) {
				if ((inb(0x60) == 0xE0) && (inb(0x60) == 0xAA)) {
					_keycode = (124 | 0x80);
				}
			}
			else if (keystate_ext_table[_s & 0x7F]) {
				if (_s & 0x80) {
					_p = (_s ^ 0x80) / 32;
				} else {
					_p = _s / 32;
				}
	
				__keystate_ext__[_p] ^= (1 << (_s % 32));
				_keycode = keystate_ext_table[_s];
				
				if (_s & 0x80) {
					_keycode |= 0x80;
				}
			}
			else {
				__keyerror__.und_key = true;
				_keycode = 126; /* keycode for an undefined */
			}
			   
		}
		else if (_s == 0xE1) {
			if ((inb(0x60) == 0x1D) 
				&& (inb(0x60) == 0x1D) 
				&& (inb(0x60) == 0x1D) 
				&& (inb(0x60) == 0x1D) 
				&& (inb(0x60) == 0x1D)) {
				_keycode = 125; /* keycode for pause */
			} else {
				__keyerror__.und_key = true;
				_keycode = 126; /* keycode for an undefined */
			}
		}
		else if (keystate_table[_s & 0x7F]) {
			if (_s & 0x80) {
				_p = (_s ^ 0x80) / 32;
			} else {
				_p = _s / 32;
			}
	
			__keystate__[_p] ^= (1 << (_s % 32));
			_keycode = keystate_table[_s];
			//printf("%x", _keycode);
			if (_s & 0x80) {
				_keycode |= 0x80;
			}
		}
		else {
			__keyerror__.und_key = true;
			_keycode = 126; /* keycode for an undefined */
		}
	}

	/* update the keyboard_state */
	update_keyboard_state(_keycode);
}

void keyboard_install(enum keyboard_mode k, uint8_t *buf, size_t buf_sz)
{
#ifdef KEYBOARD
	irq_handler_install(0x01, keyboard_handler);
	//printf("Keyboard installed.\n");
#endif
	keybuf = buf;
	keybuf_size = (uint32_t) buf_sz;
	keyboard_state.mode = k;
}
