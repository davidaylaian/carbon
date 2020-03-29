/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#ifndef _KERNEL_HAL_H
#define _KERNEL_HAL_H

#include <stddef.h>
#include <stdint.h>

#define TIMER_RATE 1000

void hal_initialize();

// interrupts
void enable();
void disable();
void setvect(size_t intn, size_t handler);

// outport
void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);

// inport
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

// timer utilities
uint32_t get_timer_tick();
uint16_t get_timer_rate();

#endif
