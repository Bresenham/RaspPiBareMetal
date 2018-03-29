#include "registers.h"
#include "stdbool.h"
#include "string.h"

void writeString(char *c);

static volatile bool led_on = false;

void SET(unsigned int addr, unsigned int val){ asm volatile(" str %0,[%1] " : : "r" (val), "r" (addr));}
unsigned int GET(unsigned int addr){
    volatile unsigned int res;
    asm volatile(" ldr %0,[%0] " : "=r" (res) : "r" (addr));
    return res;
}

__attribute__ ((naked, aligned(32))) static void interrupt_vectors(void)
{
	asm volatile(
        "b bad_exception\n"	/* RESET */
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
        if(led_on) {
            SET(GPCLR1, 1 << GPIO47);
            writeString("LED IS ON\n");
        }
        else {
            SET(GPSET1, 1 << GPIO47);
            writeString("LED IS OFFF\n");
        }
        led_on = !led_on;
        SET(TIMER_CLEAR_IRQ, 0);
    }
}

void writeString(char *str) {
    while(*str) {
        if((GET(AUX_MU_LSR_REG) & (1 << AUX_MU_LSR_REG_TRANS_EMPTY)));
            SET(AUX_MU_IO_REG,*str++);
    }
    //while(!(GET(AUX_MU_LSR_REG) & (1 << AUX_MU_LSR_REG_TRANS_IDLE)));
}

/*
 * ((250,000,000/460800)/8)-1 = 67 
 */ 
void initUART() {
    int ra;
    SET(AUX_EN_REG, 1 << AUX_EN_REG_ENABLE);
    SET(AUX_MU_IER_REG, 0);
    SET(AUX_MU_CNTL_REG, 0);
    SET(AUX_MU_LCR_REG, 3 << AUX_MU_LCR_REG_8BIT_MODE);
    SET(AUX_MU_MCR_REG, 0);
    SET(AUX_MU_IER_REG, 0);
    SET(AUX_MU_IIR_REG, 0xC6);
    SET(AUX_MU_BAUD_REG, 67);
    
    SET(GPFSEL1, (1 << GPIO14_GPFSEL_ALT5) | (1 << GPIO15_GPFSEL_ALT5));
    
    SET(GPPUD,0);
    for(ra=0;ra<150;ra++) asm volatile ("nop");
    SET(GPPUDCLK0,(1<<GPPUDCLK0_LINE14_CLK));
    for(ra=0;ra<150;ra++) asm volatile ("nop");
    SET(GPPUDCLK0,0);
    
    SET(AUX_MU_CNTL_REG, 1 << AUX_MU_CNTL_REG_ENABLE_TRANS);
}

int main(void)
{
    SET(GPFSEL4, 1 << GPIO47_GPFSEL_OUT);

    asm volatile("mcr p15, 0, %[addr], c12, c0, 0" : : [addr] "r" (&interrupt_vectors));
    asm volatile("cpsie i");
    SET(INTR_ENABLE_BASE, 1 << INTR_ENABLE_BASE_TIMER_IRQ);
    SET(TIMER_LOAD, 0x00020000);
    SET(TIMER_CTRL, (1 << TIMER_32BIT_MODE) | (1 << TIMER_IRQ_ENABLE) | (1 << TIMER_ENABLE));
    
    initUART();
    
    while(1)
        ;
}
