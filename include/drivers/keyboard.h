/**
 * 
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/CarbonOS/
 * 
 */

#ifndef DRIVERS_KEYBOARD_H
#define DRIVERS_KEYBOARD_H

#include <hal.h>
#include <stdint.h>

#define KEY_RESERVED		0
#define KEY_ESC			1
#define KEY_1			2
#define KEY_2			3
#define KEY_3			4
#define KEY_4			5
#define KEY_5			6
#define KEY_6			7
#define KEY_7			8
#define KEY_8			9
#define KEY_9			10
#define KEY_0			11
#define KEY_MINUS		12
#define KEY_EQUAL		13
#define KEY_BACKSPACE		14
#define KEY_TAB			15
#define KEY_Q			16
#define KEY_W			17
#define KEY_E			18
#define KEY_R			19
#define KEY_T			20
#define KEY_Y			21
#define KEY_U			22
#define KEY_I			23
#define KEY_O			24
#define KEY_P			25
#define KEY_LEFTBRACKET		26
#define KEY_RIGHTBRACKET	27
#define KEY_ENTER		28
#define KEY_LEFTCTRL		29
#define KEY_A			30
#define KEY_S			31
#define KEY_D			32
#define KEY_F			33
#define KEY_G			34
#define KEY_H			35
#define KEY_J			36
#define KEY_K			37
#define KEY_L			38
#define KEY_SEMICOLON		39
#define KEY_APOSTROPHE		40
#define KEY_GRAVE		41
#define KEY_LEFTSHIFT		42
#define KEY_BACKSLASH		43
#define KEY_Z			44
#define KEY_X			45
#define KEY_C			46
#define KEY_V			47
#define KEY_B			48
#define KEY_N			49
#define KEY_M			50
#define KEY_COMMA		51
#define KEY_DOT			52
#define KEY_SLASH		53
#define KEY_RIGHTSHIFT		54
#define KEY_KPAD_ASTERIK	55
#define KEY_LEFTALT		56
#define KEY_SPACE		57
#define KEY_CAPSLOCK		58
#define KEY_F1			59
#define KEY_F2			60
#define KEY_F3			61
#define KEY_F4			62
#define KEY_F5			63
#define KEY_F6			64
#define KEY_F7			65
#define KEY_F8			66
#define KEY_F9			67
#define KEY_F10			68
#define KEY_NUMLOCK		69
#define KEY_SCRLOCK		70
#define KEY_KPAD_7		71
#define KEY_KPAD_8		72
#define KEY_KPAD_9		73
#define KEY_KPAD_MINUS		74
#define KEY_KPAD_4		75
#define KEY_KPAD_5		76
#define KEY_KPAD_6		77
#define KEY_KPAD_PLUS		78
#define KEY_KPAD_1		79
#define KEY_KPAD_2		80
#define KEY_KPAD_3		81
#define KEY_KPAD_0		82
#define KEY_KPAD_DOT		83
#define KEY_F11			84
#define KEY_F12			85
#define KEY_KPAD_ENTER		86
#define KEY_RIGHTCTRL		87
#define KEY_KPAD_SLASH		88
#define KEY_RIGHTALT		89
#define KEY_HOME		90
#define KEY_UP			91
#define KEY_PAGEUP		92
#define KEY_LEFT		93
#define KEY_RIGHT		94
#define KEY_END			95
#define KEY_DOWN		96
#define KEY_PAGEDOWN		97
#define KEY_INSERT		98
#define KEY_DELETE		99
#define KEY_APPS		100
#define KEY_PRINTSCREEN		101
#define KEY_PAUSE		102

extern uint16_t keyboard_stdin_read();
extern void keyboard_install();

#endif