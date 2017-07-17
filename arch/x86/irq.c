#include <hal.h>
#include "regs.h"

// see wrappers.asm
extern void irq_wrapper_0();
extern void irq_wrapper_1();
extern void irq_wrapper_2();
extern void irq_wrapper_3();
extern void irq_wrapper_4();
extern void irq_wrapper_5();
extern void irq_wrapper_6();
extern void irq_wrapper_7();
extern void irq_wrapper_8();
extern void irq_wrapper_9();
extern void irq_wrapper_10();
extern void irq_wrapper_11();
extern void irq_wrapper_12();
extern void irq_wrapper_13();
extern void irq_wrapper_14();
extern void irq_wrapper_15();

// install irqs into their corresponding slots in the idt
void irq_install()
{
	setvect(32, (unsigned)irq_wrapper_0);
	setvect(33, (unsigned)irq_wrapper_1);
	setvect(34, (unsigned)irq_wrapper_2);
	setvect(35, (unsigned)irq_wrapper_3);
	setvect(36, (unsigned)irq_wrapper_4);
	setvect(37, (unsigned)irq_wrapper_5);
	setvect(38, (unsigned)irq_wrapper_6);
	setvect(39, (unsigned)irq_wrapper_7);
	setvect(40, (unsigned)irq_wrapper_8);
	setvect(41, (unsigned)irq_wrapper_9);
	setvect(42, (unsigned)irq_wrapper_10);
	setvect(43, (unsigned)irq_wrapper_11);
	setvect(44, (unsigned)irq_wrapper_12);
	setvect(45, (unsigned)irq_wrapper_13);
	setvect(46, (unsigned)irq_wrapper_14);
	setvect(47, (unsigned)irq_wrapper_15);
}


// handles an irq
void irq_handler(struct regs *val)
{
	printfln("Received irq %d", val->intn - 32);
	uint8_t scan_code = inb(0x60);
	if(val->intn > 39) outb(0xA0, 0x20);
	outb(0x20, 0x20);
}
