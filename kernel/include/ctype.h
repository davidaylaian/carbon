/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef _CTYPE_H
#define _CTYPE_H

#include <stdbool.h>

// boolean functions
bool isupper(int c);
bool islower(int c);
bool isdigit(int c);
bool isspace(int c);
bool ispunct(int c);
bool iscntrl(int c);
bool ishex(int c);
bool isspecial(int c);
bool isalpha(int c);
bool isalnum(int c);
bool isgraph(int c);
bool isprint(int c);

// intacter functions
int toupper(int c);
int tolower(int c);

#endif
