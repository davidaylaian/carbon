#include <hal.h>

// see wrappers.asm
extern void isr_wrapper_0();
extern void isr_wrapper_1();
extern void isr_wrapper_2();
extern void isr_wrapper_3();
extern void isr_wrapper_4();
extern void isr_wrapper_5();
extern void isr_wrapper_6();
extern void isr_wrapper_7();
extern void isr_wrapper_8();
extern void isr_wrapper_9();
extern void isr_wrapper_10();
extern void isr_wrapper_11();
extern void isr_wrapper_12();
extern void isr_wrapper_13();
extern void isr_wrapper_14();
extern void isr_wrapper_15();
extern void isr_wrapper_16();
extern void isr_wrapper_17();
extern void isr_wrapper_18();
extern void isr_wrapper_19();
extern void isr_wrapper_20();
extern void isr_wrapper_21();
extern void isr_wrapper_22();
extern void isr_wrapper_23();
extern void isr_wrapper_24();
extern void isr_wrapper_25();
extern void isr_wrapper_26();
extern void isr_wrapper_27();
extern void isr_wrapper_28();
extern void isr_wrapper_29();
extern void isr_wrapper_30();
extern void isr_wrapper_31();

void isrs_install()
{
	// install isrs into their corresponding slots in the idt
	setvect(0, (unsigned)isr_wrapper_0);
	setvect(1, (unsigned)isr_wrapper_1);
	setvect(2, (unsigned)isr_wrapper_2);
	setvect(3, (unsigned)isr_wrapper_3);
	setvect(4, (unsigned)isr_wrapper_4);
	setvect(5, (unsigned)isr_wrapper_5);
	setvect(6, (unsigned)isr_wrapper_6);
	setvect(7, (unsigned)isr_wrapper_7);
	setvect(8, (unsigned)isr_wrapper_8);
	setvect(9, (unsigned)isr_wrapper_9);
	setvect(10, (unsigned)isr_wrapper_10);
	setvect(11, (unsigned)isr_wrapper_11);
	setvect(12, (unsigned)isr_wrapper_12);
	setvect(13, (unsigned)isr_wrapper_13);
	setvect(14, (unsigned)isr_wrapper_14);
	setvect(15, (unsigned)isr_wrapper_15);
	setvect(16, (unsigned)isr_wrapper_16);
	setvect(17, (unsigned)isr_wrapper_17);
	setvect(18, (unsigned)isr_wrapper_18);
	setvect(19, (unsigned)isr_wrapper_19);
	setvect(20, (unsigned)isr_wrapper_20);
	setvect(21, (unsigned)isr_wrapper_21);
	setvect(22, (unsigned)isr_wrapper_22);
	setvect(23, (unsigned)isr_wrapper_23);
	setvect(24, (unsigned)isr_wrapper_24);
	setvect(25, (unsigned)isr_wrapper_25);
	setvect(26, (unsigned)isr_wrapper_26);
	setvect(27, (unsigned)isr_wrapper_27);
	setvect(28, (unsigned)isr_wrapper_28);
	setvect(29, (unsigned)isr_wrapper_29);
	setvect(30, (unsigned)isr_wrapper_30);
	setvect(31, (unsigned)isr_wrapper_31);
}

void isr_handler() {
	printf("Received isr");
}
