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
 * pit.c - contains functions for setting up the Programmable Interval Timer
 * and functions for it to serve.
 * 
 */

#include <hal.h>
/*
 * Stores tick count. Volatile uint32.
 * Stores tick rate. Volatile uint16.
 */
static volatile uint32_t __pitc__ = 0;
static volatile uint16_t __pitr__ = _PIT_RATE;

/*
 * Sets timer rate. For use inside this file only.
 */
static void set_pit_rate(size_t hz)
{
    __pitr__ = (uint16_t) (1193180 / ((uint32_t) hz));
    outb(0x43, 0x36);
    outb(0x40, (uint8_t) (__pitr__ & 0xFF));
    outb(0x40, (uint8_t) (__pitr__ >> 8));
}

/*
 * returns uint32 with the current tick count.
 */
uint32_t get_pit_tick(void)
{
    return __pitc__;
}

/*
 * returns uint32 with the current rate in hz.
 */
uint16_t get_pit_rate(void)
{
    return __pitr__;
}

/*
 * to be called every time pit fires.
 */
void pit_handler(void)
{
    __pitc__++;
}

/*
 * to be called by hal_initialize
 */
void pit_install(void)
{
    //first, install PIT handler to IRQ0
    irq_handler_install(0x00, pit_handler);
    set_pit_rate(__pitr__);
}
