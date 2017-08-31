/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

// assembly interface
extern void enable();
extern void disable();
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t val);

// interrupts
extern void gdt_install();
extern void idt_install();
extern void pic_remap();
extern void install_ir(uint32_t i, uint64_t base, uint16_t flags, uint16_t sel);
extern void setvect(uint8_t intn, uint64_t handler);
extern void isr_install();
extern void irq_install();
extern void irq_handler_install(uint8_t irq, void(*handler)());

// install hardware abstraction layer
extern void hal_install();

#endif
