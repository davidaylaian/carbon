/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/davidaylaian/carbon/
 * Licensed under the Apache License 2.0
 *
 */

#include <stdio.h>
#include <hal.h>
#include "regs.h"

// see wrappers.asm
void isr_wrapper_0();
void isr_wrapper_1();
void isr_wrapper_2();
void isr_wrapper_3();
void isr_wrapper_4();
void isr_wrapper_5();
void isr_wrapper_6();
void isr_wrapper_7();
void isr_wrapper_8();
void isr_wrapper_9();
void isr_wrapper_10();
void isr_wrapper_11();
void isr_wrapper_12();
void isr_wrapper_13();
void isr_wrapper_14();
void isr_wrapper_15();
void isr_wrapper_16();
void isr_wrapper_17();
void isr_wrapper_18();
void isr_wrapper_19();
void isr_wrapper_20();
void isr_wrapper_21();
void isr_wrapper_22();
void isr_wrapper_23();
void isr_wrapper_24();
void isr_wrapper_25();
void isr_wrapper_26();
void isr_wrapper_27();
void isr_wrapper_28();
void isr_wrapper_29();
void isr_wrapper_30();
void isr_wrapper_31();

// install isr wrappers into their slots in the idt
void isr_install()
{
	setvect(0, (unsigned) isr_wrapper_0);
	setvect(1, (unsigned) isr_wrapper_1);
	setvect(2, (unsigned) isr_wrapper_2);
	setvect(3, (unsigned) isr_wrapper_3);
	setvect(4, (unsigned) isr_wrapper_4);
	setvect(5, (unsigned) isr_wrapper_5);
	setvect(6, (unsigned) isr_wrapper_6);
	setvect(7, (unsigned) isr_wrapper_7);
	setvect(8, (unsigned) isr_wrapper_8);
	setvect(9, (unsigned) isr_wrapper_9);
	setvect(10, (unsigned) isr_wrapper_10);
	setvect(11, (unsigned) isr_wrapper_11);
	setvect(12, (unsigned) isr_wrapper_12);
	setvect(13, (unsigned) isr_wrapper_13);
	setvect(14, (unsigned) isr_wrapper_14);
	setvect(15, (unsigned) isr_wrapper_15);
	setvect(16, (unsigned) isr_wrapper_16);
	setvect(17, (unsigned) isr_wrapper_17);
	setvect(18, (unsigned) isr_wrapper_18);
	setvect(19, (unsigned) isr_wrapper_19);
	setvect(20, (unsigned) isr_wrapper_20);
	setvect(21, (unsigned) isr_wrapper_21);
	setvect(22, (unsigned) isr_wrapper_22);
	setvect(23, (unsigned) isr_wrapper_23);
	setvect(24, (unsigned) isr_wrapper_24);
	setvect(25, (unsigned) isr_wrapper_25);
	setvect(26, (unsigned) isr_wrapper_26);
	setvect(27, (unsigned) isr_wrapper_27);
	setvect(28, (unsigned) isr_wrapper_28);
	setvect(29, (unsigned) isr_wrapper_29);
	setvect(30, (unsigned) isr_wrapper_30);
	setvect(31, (unsigned) isr_wrapper_31);
}

// handles an isr
void isr_handler(struct hal_registers* regs)
{
	printf("Received isr %d, error code %x\n", regs->intn, regs->error_code);
}
