#include "gpio_conf.h"
#include "stdbool.h"

/* GPIO REGS */
static volatile unsigned int* gpfsel4 = (unsigned int*)GPFSEL4;
static volatile unsigned int* gpset1 = (unsigned int*)GPSET1;
static volatile unsigned int* gpclr1 = (unsigned int*)GPCLR1;

/* TIMER REGS */
static volatile unsigned int* timer_load = (unsigned int*)TIMER_LOAD_ADDR;
static volatile unsigned int* timer_ctrl = (unsigned int*)TIMER_CTRL_ADDR;
static volatile unsigned int* timer_clear_irq = (unsigned int*)TIMER_CLEAR_IRQ;
static volatile unsigned int* timer_read_irq = (unsigned int*)TIMER_READ_IRQ;

/* INTERRUPT REGS */
static volatile unsigned int* intr_pending = (unsigned int*)INTR_PENDING_ADDR;
static volatile unsigned int* intr_enable_1 = (unsigned int*)INTR_ENABLE_1_ADDR;
static volatile unsigned int* intr_enable_2 = (unsigned int*)INTR_ENABLE_2_ADDR;
static volatile unsigned int* intr_enable_base = (unsigned int*)INTR_ENABLE_BASE_ADDR;

static volatile bool led_on = false;

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
    /* It's an ARM-Timer interrupt */
    if(*timer_read_irq){
        if(led_on)
            *gpclr1 |= (1 << LED_GPIO);
        else
            *gpset1 |= (1 << LED_GPIO);
        led_on = !led_on;
        *timer_clear_irq = 0;
    }
}

int main(void)
{
    /* Set LED-Pin as output */
    *gpfsel4 |= (1 << LED_GPFSEL);
    
    asm volatile("mcr p15, 0, %[addr], c12, c0, 0" : : [addr] "r" (&interrupt_vectors));
    asm volatile("cpsie i");
    
    *intr_enable_base = 1;
    *timer_load = 0x00020000;
    *timer_ctrl = (1 << TIMER_32BIT_MODE) | (1 << TIMER_IRQ_ENABLE) | (1 << TIMER_ENABLE);
    
    while(1)
        ;
}
