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

//Layer 1 state
volatile uint32_t __keystate__[8] = {0};
volatile uint32_t __keystate_ext__[8] = {0};
volatile struct keyboard_error __keyerror__;

//static variables used for keycode queue
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
    KEYCODE_ESCAPE, KEYCODE_1, KEYCODE_2, KEYCODE_3, KEYCODE_4, KEYCODE_5,
    KEYCODE_6, KEYCODE_7, KEYCODE_8, KEYCODE_9, KEYCODE_0,
    KEYCODE_HYPHEN, KEYCODE_EQUALS, KEYCODE_BACKSPACE, KEYCODE_TAB,
    KEYCODE_Q, KEYCODE_W, KEYCODE_E, KEYCODE_R, KEYCODE_T, KEYCODE_Y, 
    KEYCODE_U, KEYCODE_I, KEYCODE_O, KEYCODE_P, 
    KEYCODE_LBRACK, KEYCODE_RBRACK, KEYCODE_ENTER, KEYCODE_LCONTROL, 
    KEYCODE_A, KEYCODE_S, KEYCODE_D, KEYCODE_F, KEYCODE_G, KEYCODE_H,
    KEYCODE_J, KEYCODE_K, KEYCODE_L, KEYCODE_SEMICOLON, KEYCODE_QUOTE, 
    KEYCODE_BACKTICK, KEYCODE_LSHIFT, KEYCODE_BACKSLASH,
    KEYCODE_Z, KEYCODE_X, KEYCODE_C, KEYCODE_V, KEYCODE_B, KEYCODE_N,
    KEYCODE_M, KEYCODE_COMMA, KEYCODE_PERIOD, KEYCODE_SLASH, KEYCODE_RSHIFT,
    KEYCODE_KEYPAD_MULTIPLY, KEYCODE_LALT, KEYCODE_SPACE, KEYCODE_CAPS_LOCK,
    KEYCODE_F1, KEYCODE_F2, KEYCODE_F3, KEYCODE_F4, KEYCODE_F5, KEYCODE_F6,
    KEYCODE_F7, KEYCODE_F8, KEYCODE_F9, KEYCODE_F10, 
    KEYCODE_NUMBER_LOCK, KEYCODE_SCROLL_LOCK,
    KEYCODE_KEYPAD_7, KEYCODE_KEYPAD_8, KEYCODE_KEYPAD_9, 
    KEYCODE_KEYPAD_SUBTRACT,
    KEYCODE_KEYPAD_4, KEYCODE_KEYPAD_5, KEYCODE_KEYPAD_6, KEYCODE_KEYPAD_ADD,
    KEYCODE_KEYPAD_1, KEYCODE_KEYPAD_2, KEYCODE_KEYPAD_3, KEYCODE_KEYPAD_0,
    KEYCODE_KEYPAD_DECIMAL,
    0, 0, 0, /* reserved */
    KEYCODE_F11, KEYCODE_F12,
    0, /* reserved */
};

uint8_t keystate_ext_table[128] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, /*0x07*/
    0, 0, 0, 0, 0, 0, 0, 0, /*0x0F*/
    KEYCODE_PREVIOUS_TRACK, 0, 0, 0, 0, 0, 0, 0, /*0x17*/
    0, KEYCODE_NEXT_TRACK, 0, 0, KEYCODE_KEYPAD_ENTER, KEYCODE_RCONTROL,
    0, 0, /*0x1F*/
    KEYCODE_MUTE, KEYCODE_CALCULATOR, KEYCODE_PLAY, 0, KEYCODE_STOP,
    0, 0, 0, /*0x27*/
    0, 0, 0, 0, 0, 0, KEYCODE_VOLUME_DOWN, 0, /*0x2F*/
    KEYCODE_VOLUME_UP, 0, KEYCODE_WWW_HOME, 0, 0, KEYCODE_KEYPAD_DIVIDE,
    0, 0, /*0x37*/
    KEYCODE_RALT, 0, 0, 0, 0, 0, 0, /*0x3F*/
    0, 0, 0, 0, 0, 0, 0, KEYCODE_HOME, /*0x47*/
    KEYCODE_UP, KEYCODE_PAGE_UP, 0, KEYCODE_LEFT, 0, KEYCODE_RIGHT, 0,
    KEYCODE_END, /*0x4F*/
    KEYCODE_DOWN, KEYCODE_PAGE_DOWN, KEYCODE_INSERT, KEYCODE_DELETE,
    0, 0, 0, 0, /*0x57*/
    0, 0, 0, KEYCODE_LEFT_GUI, KEYCODE_RIGHT_GUI, KEYCODE_APPS, 
    KEYCODE_ACPI_POWER, KEYCODE_ACPI_SLEEP, /*0x5F*/
    0, 0, 0, KEYCODE_ACPI_WAKE, 0, KEYCODE_WWW_SEARCH, KEYCODE_WWW_FAVORITES,
    KEYCODE_WWW_REFRESH, /*0x67*/
    KEYCODE_WWW_STOP, KEYCODE_WWW_FORWARD, KEYCODE_WWW_BACK,
    KEYCODE_MY_COMPUTER, KEYCODE_EMAIL, KEYCODE_MEDIA_SELECT, 
    0, /* reserved */
};

char keycode_to_text(uint8_t keycode)
{
    char _r;
    if(KEYCODE_IS_PRESS(keycode) && keycode_to_char[keycode]) {
        if (keyboard_state.lshft || keyboard_state.rshft) {
            _r = keycode_to_char_shft[keycode];
        } else {
            _r = keycode_to_char[keycode];
        }

        if (keyboard_state.capslock) {
            if (IS_UPPERCASE(_r)) {
                _r = UPPER_TO_LOWER(_r);
            } else if (IS_LOWERCASE(_r)) {
                _r = LOWER_TO_UPPER(_r);
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
    case KEYCODE_LCONTROL:
        keyboard_state.lctrl = true; 
        break;
    case KEYCODE_LSHIFT:
        keyboard_state.lshft = true; 
        break;
    case KEYCODE_RSHIFT:
        keyboard_state.rshft = true; 
        break;
    case KEYCODE_LALT:
        keyboard_state.lalt = true; 
        break;
    case KEYCODE_CAPS_LOCK:
        keyboard_state.capslock ^= 1; 
        break;
    case KEYCODE_NUMBER_LOCK:
        keyboard_state.numlock ^= 1; 
        break;
    case KEYCODE_SCROLL_LOCK:
        keyboard_state.scrolllock ^= 1; 
        break;
    case KEYCODE_RCONTROL:
        keyboard_state.rctrl = true; 
        break;
    case KEYCODE_RALT:
        keyboard_state.ralt = true; 
        break;
    case KEYCODE_INSERT:
        keyboard_state.insert ^= 1; 
        break;
    case KEYCODE_DELETE:
        keyboard_state.del = true; 
        break;
    case KEYCODE_PAUSE:
        keyboard_state.paused ^= 1; 
        break;
    case KEYCODE_MAKE_RELEASE(KEYCODE_LCONTROL):
        keyboard_state.lctrl = false; 
        break;
    case KEYCODE_MAKE_RELEASE(KEYCODE_LSHIFT):
        keyboard_state.lshft = false; 
        break;
    case KEYCODE_MAKE_RELEASE(KEYCODE_RSHIFT):
        keyboard_state.rshft = false; 
        break;
    case KEYCODE_MAKE_RELEASE(KEYCODE_LALT):
        keyboard_state.lalt = false; 
        break;
    case KEYCODE_MAKE_RELEASE(KEYCODE_RCONTROL):
        keyboard_state.rctrl = false; 
        break;
    case KEYCODE_MAKE_RELEASE(KEYCODE_RALT):
        keyboard_state.ralt = false; 
        break;
    case KEYCODE_MAKE_RELEASE(KEYCODE_DELETE):
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
    uint8_t _stat = inb(PS2_STATUS);
    uint8_t _keycode = KEYCODE_ERROR;

    /* set errors */
    if (PS2_ERR_PARITY(_stat)) {
        __keyerror__.parity_error = true;
    }

    if (PS2_ERR_TIMEOUT(_stat)) {
        __keyerror__.timeout_error = true;
    }

    /* read from 8042 output buffer */
    if (PS2_OUTPUT_BUFFER_FULL(_stat)) {
        uint8_t _s = inb(PS2_DATA);
        //printf("%x ", _s);
        uint8_t _p;

        /* firstly check if sequence is multibyte */
        if (PS2_IS_MULTIBYTE(_s)) {
            _s = inb(PS2_DATA);
            
            if (_s == SCANCODE_PRINT_SCREEN_PRESS) {
                if ((inb(PS2_DATA) == SCANCODE_MULTI) 
                    && (inb(PS2_DATA) == SCANCODE_PRINT_SCREEN_PRESS2)) {
                    _keycode = KEYCODE_PRINT_SCREEN; 
                }
            }
            else if (_s == SCANCODE_PRINT_SCREEN_RELEASE) {
                if ((inb(PS2_DATA) == SCANCODE_MULTI) 
                    && (inb(PS2_DATA) == SCANCODE_PRINT_SCREEN_RELEASE2)) {
                    _keycode = KEYCODE_MAKE_RELEASE(KEYCODE_PRINT_SCREEN);
                }
            }
            else if (keystate_ext_table[GET_RAW_SCANCODE(_s)]) {
                _p = GET_RAW_SCANCODE(_s) / 32;
    
                __keystate_ext__[_p] ^= (1 << (_s % 32));
                _keycode = keystate_ext_table[_s];
                
                if (SCANCODE_IS_RELEASE(_s)) {
                   _keycode = KEYCODE_MAKE_RELEASE(_keycode);
                }
            }
            else {
                __keyerror__.und_key = true;
                _keycode = KEYCODE_UNDEFINED;
            }
               
        }
        else if (PS2_IS_PAUSE(_s)) {
            if ((inb(PS2_DATA) == SCANCODE_PAUSE_1) 
                && (inb(PS2_DATA) == SCANCODE_PAUSE_2) 
                && (inb(PS2_DATA) == SCANCODE_PAUSE_3) 
                && (inb(PS2_DATA) == SCANCODE_PAUSE_4) 
                && (inb(PS2_DATA) == SCANCODE_PAUSE_5)) {
                _keycode = KEYCODE_PAUSE;
            } else {
                __keyerror__.und_key = true;
                _keycode = KEYCODE_UNDEFINED;
            }
        }
        else if (keystate_table[GET_RAW_SCANCODE(_s)]) {
            _p = GET_RAW_SCANCODE(_s) / 32;
    
            __keystate__[_p] ^= (1 << (_s % 32));
            _keycode = keystate_table[_s];
            //printf("%x", _keycode);
            if (SCANCODE_IS_RELEASE(_s)) {
                _keycode = KEYCODE_MAKE_RELEASE(_keycode);
            }
        }
        else {
            __keyerror__.und_key = true;
            _keycode = KEYCODE_UNDEFINED;
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
