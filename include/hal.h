#ifndef HAL_H
#define HAL_H

#include <stdint.h>

// asm.c
extern void enable();
extern void disable();
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t val);

#endif
