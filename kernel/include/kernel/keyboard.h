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
#define KEYBOARD_DEBUG

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

extern volatile struct keyboard_state keyboard_state;

extern volatile uint32_t __keystate__[8];
extern volatile uint32_t __keystate_ext[8];
extern volatile struct keyboard_error __keyerror__;

void keyboard_install(enum keyboard_mode k, uint8_t *buf, size_t buf_sz);
uint8_t next_keycode();
char keycode_to_text(uint8_t keycode);

#endif