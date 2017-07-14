#include <hal.h>

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
void irq_handler() {
	printfln("Received irq");
}
