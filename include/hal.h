#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <string.h>

// assembly interface
extern void enable();
extern void disable();
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t val);

// install hardware abstraction layer
extern void hal_install();

#endif
