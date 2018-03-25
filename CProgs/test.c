#include "gpio_conf.h"
#include "stdbool.h"

static volatile bool led_on = false;

void SET(unsigned int addr, unsigned int val){
    volatile unsigned int *ptr = (unsigned int*)addr;
    *ptr = val;
}
unsigned int GET(unsigned int addr){
    volatile unsigned int *ptr = (unsigned int*)addr;
    return *ptr;
}

__attribute__ ((naked, aligned(32))) static void interrupt_vectors(void)
{
	asm volatile("b bad_exception\n"	/* RESET */
		"b bad_exception\n"	/* UNDEF */
		"b interrupt_swi\n"
		"b interrupt_prefetch_abort \n"
		"b interrupt_data_abort \n"
		"b bad_exception;\n"	/* Unused vector */
		"b interrupt_irq \n"
		"b bad_exception\n"	/* FIQ */
	);
}

/* Unhandled exceptions */
__attribute__ ((naked)) void bad_exception(void){}
__attribute__ ((interrupt ("SWI"))) void interrupt_swi(void){}
__attribute__ ((interrupt ("ABORT"))) void interrupt_data_abort(void){}
__attribute__ ((interrupt ("ABORT"))) void interrupt_prefetch_abort(void){}


/* IRQs flash the OK LED */
__attribute__ ((interrupt ("IRQ"))) void interrupt_irq(void)
{
    if(GET(TIMER_READ_IRQ)){
        if(led_on)
            SET(GPCLR1, 1 << GPIO47);
        else
            SET(GPSET1, 1 << GPIO47);
        led_on = !led_on;
        SET(TIMER_CLEAR_IRQ, 0);
    }
}

int main(void)
{
    SET(GPFSEL4, 1 << GPIO47_GPFSEL_OUT);

    asm volatile("mcr p15, 0, %[addr], c12, c0, 0" : : [addr] "r" (&interrupt_vectors));
    asm volatile("cpsie i");
    SET(INTR_ENABLE_BASE, 1 << INTR_ENABLE_BASE_TIMER_IRQ);
    SET(TIMER_LOAD, 0x00020000);
    SET(TIMER_CTRL, (1 << TIMER_32BIT_MODE) | (1 << TIMER_IRQ_ENABLE) | (1 << TIMER_ENABLE));

    while(1)
        ;
}
