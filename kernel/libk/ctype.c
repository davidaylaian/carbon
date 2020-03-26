/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

/*
 * Every character falls into one or more of these categories.
 * We assign each category 1 bit and use bitwise operators to test if
 * a selected character falls into that category.
 */

#define  SPECIAL	0b00000000
#define  UPPER		0b00000001
#define  LOWER		0b00000010
#define  DIGIT		0b00000100
#define  SPACE		0b00001000
#define  PUNCT		0b00010000
#define  CONTROL	0b00100000
#define  BLANK		0b01000000
#define  HEX		0b10000000

/*
 * There are 257 characters in ASCII.
 * Characters that aren't given values fall into SPECIAL.
 */

uint8_t ctype[257] = {
	CONTROL,		// 00 NUL
	CONTROL,		// 01 SOH
	CONTROL,		// 02 STX
	CONTROL,		// 03 ETX
	CONTROL,		// 04 EOT
	CONTROL,		// 05 ENQ
	CONTROL,		// 06 ACK
	CONTROL,		// 07 BEL
	CONTROL,		// 08 BS
	CONTROL + SPACE,	// 09 TAB
	CONTROL + SPACE,	// 0A LF
	CONTROL + SPACE,	// 0B VT
	CONTROL + SPACE,	// 0C FF
	CONTROL + SPACE,	// 0D CR
	CONTROL,		// 0E SI
	CONTROL,		// 0F SO
	CONTROL,		// 10 DLE
	CONTROL,		// 11 DC1
	CONTROL,		// 12 DC2
	CONTROL,		// 13 DC3
	CONTROL,		// 14 DC4
	CONTROL,		// 15 NAK
	CONTROL,		// 16 SYN
	CONTROL,		// 17 ETB
	CONTROL,		// 18 CAN
	CONTROL,		// 19 EM
	CONTROL,		// 1A SUB
	CONTROL,		// 1B ESC
	CONTROL,		// 1C FS
	CONTROL,		// 1D GS
	CONTROL,		// 1E RS
	CONTROL,		// 1F US
	SPACE + BLANK,		// 20 Space
	PUNCT,			// 21 !
	PUNCT,			// 22 "
	PUNCT,			// 23 #
	PUNCT,			// 24 $
	PUNCT,			// 25 %
	PUNCT,			// 26 &
	PUNCT,			// 27 '
	PUNCT,			// 28 (
	PUNCT,			// 29 )
	PUNCT,			// 2A *
	PUNCT,			// 2B +
	PUNCT,			// 2C ,
	PUNCT,			// 2D -
	PUNCT,			// 2E .
	PUNCT,			// 2F /
	DIGIT + HEX,		// 30 0
	DIGIT + HEX,		// 31 1
	DIGIT + HEX,		// 32 2
	DIGIT + HEX,		// 33 3
	DIGIT + HEX,		// 34 4
	DIGIT + HEX,		// 35 5
	DIGIT + HEX,		// 36 6
	DIGIT + HEX,		// 37 7
	DIGIT + HEX,		// 38 8
	DIGIT + HEX,		// 39 9
	PUNCT,			// 3A :
	PUNCT,			// 3B ;
	PUNCT,			// 3C <
	PUNCT,			// 3D =
	PUNCT,			// 3E >
	PUNCT,			// 3F ?
	PUNCT,			// 40 @
	UPPER + HEX,		// 41 A
	UPPER + HEX,		// 42 B
	UPPER + HEX,		// 43 C
	UPPER + HEX,		// 44 D
	UPPER + HEX,		// 45 E
	UPPER + HEX,		// 46 F
	UPPER,			// 47 G
	UPPER,			// 48 H
	UPPER,			// 49 I
	UPPER,			// 4A J
	UPPER,			// 4B K
	UPPER,			// 4C L
	UPPER,			// 4D M
	UPPER,			// 4E N
	UPPER,			// 4F O
	UPPER,			// 50 P
	UPPER,			// 51 Q
	UPPER,			// 52 R
	UPPER,			// 53 S
	UPPER,			// 54 T
	UPPER,			// 55 U
	UPPER,			// 56 V
	UPPER,			// 57 W
	UPPER,			// 58 X
	UPPER,			// 59 Y
	UPPER,			// 5A Z
	PUNCT,			// 5B [
	PUNCT,			// 5C \ 
	PUNCT,			// 5D ]
	PUNCT,			// 5E ^
	PUNCT,			// 5F _
	PUNCT,			// 60 `
	LOWER + HEX,		// 61 a
	LOWER + HEX,		// 62 b
	LOWER + HEX,		// 63 c
	LOWER + HEX,		// 64 d
	LOWER + HEX,		// 65 e
	LOWER + HEX,		// 66 f
	LOWER,			// 67 g
	LOWER,			// 68 h
	LOWER,			// 69 i
	LOWER,			// 6A j
	LOWER,			// 6B k
	LOWER,			// 6C l
	LOWER,			// 6D m
	LOWER,			// 6E n
	LOWER,			// 6F o
	LOWER,			// 70 p
	LOWER,			// 71 q
	LOWER,			// 72 r
	LOWER,			// 73 s
	LOWER,			// 74 t
	LOWER,			// 75 u
	LOWER,			// 76 v
	LOWER,			// 77 w
	LOWER,			// 78 x
	LOWER,			// 79 y
	LOWER,			// 7A z
	PUNCT,			// 7B {
	PUNCT,			// 7C |
	PUNCT,			// 7D }
	PUNCT,			// 7E ~
	CONTROL			// 7F DEL
};

/*
 * Now that we have a list of what categories all 257 characters are
 * in, we can simply check if a character includes the bit for a
 * category and if it does, it is in that category.
 */

bool isupper(int c) {
	return ctype[c] & UPPER;
}

bool islower(int c) {
	return ctype[c] & LOWER;
}

bool isdigit(int c) {
	return ctype[c] & DIGIT;
}

bool isspace(int c) {
	return ctype[c] & SPACE;
}

bool ispunct(int c) {
	return ctype[c] & PUNCT;
}

bool iscntrl(int c) {
	return ctype[c] & DIGIT;
}

bool ishex(int c) {
	return ctype[c] & HEX;
}

bool isspecial(int c) {
	return ctype[c] == SPECIAL;
}

bool isalpha(int c) {
	return ctype[c] & (LOWER | UPPER);
}

bool isalnum(int c) {
	return ctype[c] & (LOWER | UPPER | DIGIT);
}

// tests for a character that has a graphical representation
bool isgraph(int c) {
	return ctype[c] & (LOWER | UPPER | DIGIT | PUNCT);
}

// tests for any printable character
bool isprint(int c) {
	return ctype[c] & (LOWER | UPPER | DIGIT | PUNCT | BLANK);
}

// converts a lowercase character to uppercase
int toupper(int c) {
	if (islower(c))
		return c - ('a' - 'A');
	else
		return c;
}

// converts an uppercase character to lowercase
int tolower(int c) {
	if (isupper(c))
		return c - ('A' - 'a');
	else
		return c;
}
