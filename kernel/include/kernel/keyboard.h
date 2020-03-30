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

#if !defined(KEYBOARD_H)
#define KEYBOARD_H

//this allows keyboard driver to be installed
#define KEYBOARD

#include <stdint.h>

struct keyboard_state {
    bool lshft, rshft;
    bool lctrl, rctrl;
    bool lalt, ralt;
    bool del;
    bool numlock, scrolllock, capslock;
    uint8_t lastkey;
};
extern volatile struct keyboard_state keyboard_state;

#endif