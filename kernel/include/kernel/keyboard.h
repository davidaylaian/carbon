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
 * keyboard.h - contains functions for setting up basic keyboard utilities.
 *
 */

#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

//this allows keyboard driver to be installed
#define KEYBOARD

#include <stdint.h>
#include <stdbool.h>

enum keyboard_mode { KEYALL, KEYDUMP, KEYSMASH, TEXTALL, TEXTDUMP, TEXTSMASH };

struct keyboard_state {
    bool lshft, rshft;
    bool lctrl, rctrl;
    bool lalt, ralt;
    bool del;
    bool numlock, scrolllock, capslock;
    bool paused;
    bool insert;
    bool halted;
    uint8_t lastkey;
    enum keyboard_mode mode;
};

struct keyboard_error {
    bool parity_error;
    bool timeout_error;
    bool und_key;
    bool halted;
};

volatile struct keyboard_state keyboard_state;

volatile uint32_t __keystate__[8];
volatile uint32_t __keystate_ext[8];
volatile struct keyboard_error __keyerror__;

void keyboard_install(enum keyboard_mode k, uint8_t *buf, size_t buf_sz);
uint8_t next_keycode();
char keycode_to_text(uint8_t keycode);

/*
 * Keyboard I/O macros.
 */
#define PS2_STATUS 0x64
#define PS2_COMMAND 0x64
#define PS2_DATA 0x64

#define PS2_OUTPUT_BUFFER_FULL(s) ((s) & 0x01)
#define PS2_INPUT_BUFFER_FULL(s) ((s) & 0x02)
#define PS2_SYSTEM_FLAG_SET(s) ((s) & 0x04)
#define PS2_IS_COMMAND(s) ((s) & 0x08)
#define PS2_IS_DATA(s) (!((s) & 0x08))
#define PS2_KEYBOARD_LOCK(s) ((s) & 0x10)
#define PS2_RECEIVE_TIMEOUT(s) ((s) & 0x20)
#define PS2_AUXILLARY_BUFFER_FULL(s) ((s) & 0x20)
#define PS2_ERR_TIMEOUT(s) ((s) & 0x40)
#define PS2_ERR_PARITY(s) ((s) & 0x80)

#define SCANCODE_MULTI 0xE0
#define PS2_IS_MULTIBYTE(k) ((k) == 0xE0)
#define PS2_IS_PAUSE(k)  ((k) == 0xE1)

#define SCANCODE_PRINT_SCREEN_PRESS 0x2A
#define SCANCODE_PRINT_SCREEN_PRESS2 0x37
#define SCANCODE_PRINT_SCREEN_RELEASE 0xB7
#define SCANCODE_PRINT_SCREEN_RELEASE2 0xAA
#define SCANCODE_PAUSE_1 0x1D
#define SCANCODE_PAUSE_2 0x45
#define SCANCODE_PAUSE_3 0xE1
#define SCANCODE_PAUSE_4 0x9D
#define SCANCODE_PAUSE_5 0xC5

#define GET_RAW_SCANCODE(k) ((k) & 0x7F)
#define SCANCODE_IS_PRESS(k) ((k) < 0x80)
#define SCANCODE_IS_RELEASE(k) ((k) & 0x80)
#define SCANCODE_MAKE_PRESS(k) ((k) & 0x7F)
#define SCANCODE_MAKE_RELEASE(k) ((k) | 0x80)

/*
 * Huge swath of macros for keycodes.
 */
#define KEYCODE_NULL 0
#define KEYCODE_1 1
#define KEYCODE_EXCLAMATION_MARK 1
#define KEYCODE_2 2
#define KEYCODE_AT 2
#define KEYCODE_3 3
#define KEYCODE_HASHTAG 3
#define KEYCODE_4 4
#define KEYCODE_DOLLAR 4
#define KEYCODE_5 5
#define KEYCODE_PERCENT 5
#define KEYCODE_6 6
#define KEYCODE_CARAT 6
#define KEYCODE_7 7
#define KEYCODE_AMPERSAND 7
#define KEYCODE_8 8
#define KEYCODE_ASTERISK 8
#define KEYCODE_9 9
#define KEYCODE_LPAREN 9
#define KEYCODE_0 10
#define KEYCODE_RPAREN 10
#define KEYCODE_HYPHEN 11
#define KEYCODE_MINUS 11
#define KEYCODE_UNDERSCORE 11
#define KEYCODE_EQUALS 12
#define KEYCODE_PLUS 12
#define KEYCODE_BACKSPACE 13
#define KEYCODE_TAB 14
#define KEYCODE_Q 15
#define KEYCODE_W 16
#define KEYCODE_E 17
#define KEYCODE_R 18
#define KEYCODE_T 19
#define KEYCODE_Y 20
#define KEYCODE_U 21
#define KEYCODE_I 22
#define KEYCODE_O 23
#define KEYCODE_P 24
#define KEYCODE_LBRACK 25
#define KEYCODE_LCURL 25
#define KEYCODE_LBRACE 25
#define KEYCODE_RBRACK 26
#define KEYCODE_RCURL 26
#define KEYCODE_RBRACE 26
#define KEYCODE_ENTER 27
#define KEYCODE_A 28
#define KEYCODE_S 29
#define KEYCODE_D 30
#define KEYCODE_F 31
#define KEYCODE_G 32
#define KEYCODE_H 33
#define KEYCODE_J 34
#define KEYCODE_K 35
#define KEYCODE_L 36
#define KEYCODE_SEMICOLON 37
#define KEYCODE_COLON 37
#define KEYCODE_APOSTROPHE 38
#define KEYCODE_QUOTE 38
#define KEYCODE_BACKTICK 39
#define KEYCODE_TILDE 39
#define KEYCODE_BACKSLASH 40
#define KEYCODE_PIPE 40
#define KEYCODE_Z 41
#define KEYCODE_X 42
#define KEYCODE_C 43
#define KEYCODE_V 44
#define KEYCODE_B 45
#define KEYCODE_N 46
#define KEYCODE_M 47
#define KEYCODE_COMMA 48
#define KEYCODE_LESS_THAN 48
#define KEYCODE_PERIOD 49
#define KEYCODE_GREATER_THAN 49
#define KEYCODE_SLASH 50
#define KEYCODE_FORWARD_SLASH 50
#define KEYCODE_QUESTION_MARK 50
#define KEYCODE_KEYPAD_MULTIPLY 51
#define KEYCODE_SPACE 52
#define KEYCODE_KEYPAD_7 53
#define KEYCODE_KEYPAD_HOME 53
#define KEYCODE_KEYPAD_8 54
#define KEYCODE_KEYPAD_UP 54
#define KEYCODE_KEYPAD_9 55
#define KEYCODE_KEYPAD_PAGE_UP 55
#define KEYCODE_KEYPAD_SUBTRACT 56
#define KEYCODE_KEYPAD_4 57
#define KEYCODE_KEYPAD_LEFT 57
#define KEYCODE_KEYPAD_5 58
#define KEYCODE_KEYPAD_6 59
#define KEYCODE_KEYPAD_RIGHT 59
#define KEYCODE_KEYPAD_ADD 60
#define KEYCODE_KEYPAD_1 61
#define KEYCODE_KEYPAD_END 61
#define KEYCODE_KEYPAD_2 62
#define KEYCODE_KEYPAD_DOWN 62
#define KEYCODE_KEYPAD_3 63
#define KEYCODE_KEYPAD_PAGE_DOWN 63
#define KEYCODE_KEYPAD_0 64
#define KEYCODE_KEYPAD_INSERT 64
#define KEYCODE_KEYPAD_DECIMAL 65
#define KEYCODE_KEYPAD_DELETE 65
#define KEYCODE_KEYPAD_ENTER 66
#define KEYCODE_KEYPAD_DIVIDE 67
#define KEYCODE_ESCAPE 68
#define KEYCODE_LCONTROL 69
#define KEYCODE_LSHIFT 70
#define KEYCODE_RSHIFT 71
#define KEYCODE_LALT 72
#define KEYCODE_CAPS_LOCK 73
#define KEYCODE_F1 74
#define KEYCODE_F2 75
#define KEYCODE_F3 76
#define KEYCODE_F4 77
#define KEYCODE_F5 78
#define KEYCODE_F6 79
#define KEYCODE_F7 80
#define KEYCODE_F8 81
#define KEYCODE_F9 82
#define KEYCODE_F10 83
#define KEYCODE_NUMBER_LOCK 84
#define KEYCODE_SCROLL_LOCK 85
#define KEYCODE_F11 86
#define KEYCODE_F12 87
#define KEYCODE_PREVIOUS_TRACK 88
#define KEYCODE_NEXT_TRACK 89
#define KEYCODE_RCONTROL 90
#define KEYCODE_MUTE 91
#define KEYCODE_CALCULATOR 92
#define KEYCODE_PLAY 93
#define KEYCODE_STOP 94
#define KEYCODE_VOLUME_DOWN 95
#define KEYCODE_VOLUME_UP 96
#define KEYCODE_WWW_HOME 97
#define KEYCODE_RALT 98
#define KEYCODE_HOME 99
#define KEYCODE_CURSOR_UP 100
#define KEYCODE_UP 100
#define KEYCODE_PAGE_UP 101
#define KEYCODE_CURSOR_LEFT 102
#define KEYCODE_LEFT 102
#define KEYCODE_CURSOR_RIGHT 103
#define KEYCODE_RIGHT 103
#define KEYCODE_END 104
#define KEYCODE_CURSOR_DOWN 105
#define KEYCODE_DOWN 105
#define KEYCODE_PAGE_DOWN 106
#define KEYCODE_INSERT 107
#define KEYCODE_DELETE 108
#define KEYCODE_LEFT_GUI 109
#define KEYCODE_RIGHT_GUI 110
#define KEYCODE_APPS 111
#define KEYCODE_ACPI_POWER 112
#define KEYCODE_ACPI_SLEEP 113
#define KEYCODE_ACPI_WAKE 114
#define KEYCODE_WWW_SEARCH 115
#define KEYCODE_WWW_FAVORITES 116
#define KEYCODE_WWW_REFRESH 117
#define KEYCODE_WWW_STOP 118
#define KEYCODE_WWW_FORWARD 119
#define KEYCODE_WWW_BACK 120
#define KEYCODE_MY_COMPUTER 121
#define KEYCODE_EMAIL 122
#define KEYCODE_MEDIA_SELECT 123
#define KEYCODE_PRINT_SCREEN 124
#define KEYCODE_PAUSE 125
#define KEYCODE_BREAK 125
#define KEYCODE_UNDEFINED 126
#define KEYCODE_HALT 127
#define KEYCODE_ERROR 255

/*
 * Macro functions for keycodes.
 */
#define KEYCODE_IS_PRESS(k) ((k) < 0x80)
#define KEYCODE_IS_RELEASE(k) ((k) & 0x80)
#define GET_RAW_KEYCODE(k) ((k) & 0x7F)
#define KEYCODE_IS_PRINTABLE(k) ((k) < 68)
#define KEYCODE_IS_SHIFT(k) (((k) == 70) || ((k) == 71))
#define KEYCODE_MAKE_PRESS(k) ((k) & 0x7F)
#define KEYCODE_MAKE_RELEASE(k) ((k) | 0x80)

/*
 * Basic utilities for keyboard.c's functions.
 */
#define IS_UPPERCASE(t) (((t) > 0x40) && ((t) < 0x5B))
#define IS_LOWERCASE(t) (((t) > 0x60) && ((t) < 0x7B))
#define UPPER_TO_LOWER(t) ((t) | 0x20)
#define LOWER_TO_UPPER(t) ((t) & 0xDF)

#endif
