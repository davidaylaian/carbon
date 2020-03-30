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

volatile struct {
    bool parity_error;
    bool timeout_error;
    bool print_screen;
    bool und_key;
} __keyerror__;

uint8_t keystate_table[128] = 
{
    0, /* reserved */
    200, /* escape */
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', /*1-9, 0*/
    '-', /* -/_ key */
    '=', /* =/+ key */
    '\b', /* backspace */
    '\t', /* tab */
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']',
    '\n', /* enter */
    201, /* Left Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
    202, /* Left Shift */
    '\\',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',
    203, /* Right Shift */
    '*', /* Keypad * */
    204, /* Left Alt */
    ' ', /* Space */
    205, /* Capslock */
    211, 212, 213, 214, 215, 216, 217, 218, 219, 220, /* F1 - F10 */
    223, /* Number Lock */
    224, /* Scroll Lock */
    231,  /* Keypad 7 (HOME) */
    232,  /* Keypad 8 (ARROW UP) */
    233,  /* Keypad 9 (PGUP) */
    234, /* Keypad - */
    235, /* Keypad 4 (ARROW LEFT) */
    236, /* Keypad 5 */
    237, /* Keypad 6 (ARROW RIGHT) */
    238, /* Keypad + */
    239, /* Keypad 1 (END) */
    240, /* Keypad 2 (ARROW DOWN) */
    241, /* Keypad 3 (PGDN) */
    242, /* Keypad 0 (INS) */
    243, /* Keypad . (DEL) */
    0, 0, 0, /* reserved */
    221, 222, /* F11 and F12 */
    0, /* reserved */
};

uint8_t keystate_ext_table[128] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, /*0x07*/
    0, 0, 0, 0, 0, 0, 0, 0, /*0x0F*/
    1, /* previous track */
    0, 0, 0, 0, 0, 0, 0, /*0x17*/
    0,
    2, /* next track */
    0, 0,
    3, /* keypad enter */
    4, /* right control */
    0, 0, /*0x1F*/
    5, /* mute */
    6, /* calculator */
    7, /* play */
    0,
    8, /* stop */
    0, 0, 0, /*0x27*/
    0, 0, 0, 0, 0, 0,
    9, /* volume down */
    0, /*0x2F*/
    10, /* volume up */
    0,
    11, /* www home */
    0, 0,
    12, /* keypad / */
    0, 0, /*0x37*/
    13, /* right alt */
    0, 0, 0, 0, 0, 0, /*0x3F*/
    0, 0, 0, 0, 0, 0, 0,
    14, /* home */ /*0x47*/
    15, /* cursor up */
    16, /* page up */
    0, 
    17, /* cursor left */
    0,
    18, /* cursor right */
    0,
    19, /* end */ /*0x4F*/
    20, /* cursor down */
    21, /* page down */
    22, /* insert */
    23, /* delete */
    0, 0, 0, 0, /*0x57*/
    0, 0, 0,
    24, /* left GUI */
    25, /* right GUI */
    26, /* apps */
    27, /* ACPI power */
    28, /* ACPI sleep */ /*0x5F*/
    0, 0, 0,
    29, /* ACPI wake */
    0,
    30, /* WWW search */
    31, /* WWW favorites */
    32, /* WWW refresh */ /*0x67*/
    33, /* WWW stop */
    34, /* WWW forward */
    35, /* WWW back */
    36, /* my computer */
    37, /* email */
    38, /* media select */
    0, /* reserved */
};

void keyboard_handler()
{
    /* check status register */
    uint8_t _stat = inb(0x64);

    /* set errors */
    if (_stat & 0x80)
        __keyerror__.parity_error = true;
    if (_stat & 0x40)
        __keyerror__.timeout_error = true;

    /* read from 8042 output buffer */
    if (_stat & 0x01) {
        uint8_t _s = inb(0x60);
        uint8_t _p;

        /* firstly check if sequence is multibyte */
        if (_s == 0xE0) {
            _s = inb(0x60);
            
            if (_s == 0x2A) {
                if ((inb(0x60) == 0xE0) && (inb(0x60) == 0x37))
                    __keyerror__.print_screen = true;
            }
            else if (_s == 0xB7) {
                if ((inb(0x60) == 0xE0) && (inb(0x60) == 0xAA))
                    __keyerror__.print_screen = false;
            }
            else if (keystate_ext_table[_s]) {
                if (_s & 0x80)
                    _p = (_s ^ 0x80) / 32;
                else
                    _p = _s / 32;
    
                __keystate_ext__[_p] ^= (1 << (_s % 32));
            }
            else
                __keyerror__.und_key = true;
        }
        else if (_s == 0xE1) {
            if ((inb(0x60) == 0x1D) 
                && (inb(0x60) == 0x1D) 
                && (inb(0x60) == 0x1D) 
                && (inb(0x60) == 0x1D) 
                && (inb(0x60) == 0x1D))
                keyboard_state.lastkey = 255; /* pause */
            else
                __keyerror__.und_key = true;
        }
        else if (keystate_table[_s]) {
            if (_s & 0x80)
                _p = (_s ^ 0x80) / 32;
            else
                _p = _s / 32;
    
            __keystate__[_p] ^= (1 << (_s % 32));
        }
        else
            __keyerror__.und_key = true;
    }

/*
    switch (_s) {
    case 0xAA:
        keyboard_state.lshft = false;
    case 0xB6:
        keyboard_state.rshft = false;
    case 0x9D:
        keyboard_state.lctrl = false;
    case 0xB8:
        keyboard_state.lalt = false;
    case 0xD3:
        keyboard_state.del = false;
    case 0x2A:
        keyboard_state.lshft = true;
    case 0x36:
        keyboard_state.rshft = true;
    case 0x1D:
        keyboard_state.lctrl = true;
    case 0x38:
        keyboard_state.lalt = true;
    case 0x53:
        keyboard_state.del = true;
    
    }*/
}

void keyboard_install()
{
#if defined(KEYBOARD)
    irq_handler_install(0x01, (size_t) keyboard_handler);
#endif
}