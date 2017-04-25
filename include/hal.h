#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdnoreturn.h>

// assembly interface
extern void enable();
extern void disable();
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t val);

// interrupts
void setvect(uint8_t intn, uint64_t handler);

// install hardware abstraction layer
extern void hal_install();

#endif
