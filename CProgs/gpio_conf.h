/* INTERRUPT HANDLING ADDRESSES */
#define INTR_BASE           0x2000b000
#define INTR_PENDING        0x2000b200
#define INTR_ENABLE_1       0x2000b210
#define INTR_ENABLE_2       0x2000b214
#define INTR_ENABLE_BASE    0x2000b218

/* INTERRUPT HANDLING BITS */
#define INTR_ENABLE_BASE_TIMER_IRQ  0

/* TIMER ADDRESSES */
#define TIMER_BASE          0x2000b000
#define TIMER_LOAD          0x2000b400
#define TIMER_CTRL          0x2000b408
#define TIMER_CLEAR_IRQ     0x2000b40C
#define TIMER_READ_IRQ      0x2000b410

/* TIMER BITS */
#define TIMER_ENABLE        7
#define TIMER_IRQ_ENABLE    5
#define TIMER_32BIT_MODE    1

/* MINI-UART ADDRESSES */
#define AUX_MU_LCR_REG      0x2021504C
#define AUX_MU_BAUD         0x20215068
#define AUX_MU_CNTL_REG     0x20215060

/* MINI-UART BITS */
#define AUX_MU_LCR_REG_8BIT_MODE        0
#define AUX_MU_CNTL_REG_ENABLE_TRANS    1
#define AUX_MU_CNTL_REG_ENABLE_RECV     0

/* GPIO ADDRESSES */
#define GPIO_BASE       0x20200000

/* GPIO ADDRESSES - FUNCTION SELECT */
#define GPFSEL0         0x20200000
#define GPFSEL1         0x20200004
#define GPFSEL2         0x20200008
#define GPFSEL3         0x2020000C
#define GPFSEL4         0x20200010

/* GPIO ADDRESSES - PIN OUTPUT SET */
#define GPSET0          0x2020001C
#define GPSET1          0x20200020

/* GPIO ADDRESSES - PIN OUTPUT CLEAR */
#define GPCLR0          0x20200028
#define GPCLR1          0x2020002C

/* GPIO BITS */
#define GPIO2_GPFSEL_OUT       6
#define GPIO2                  2
#define GPIO14_GPFSEL_ALT0      14
#define GPIO15_GPFSEL_ALT0      17

#define GPIO47_GPFSEL_OUT       21
#define GPIO47                  15
