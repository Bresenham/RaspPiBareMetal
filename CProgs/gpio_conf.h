/* INTERRUPT HANDLING ADDRESSES */
#define INTR_BASE_ADDR          0x2000b000UL
#define INTR_PENDING_ADDR       0x2000b200UL
#define INTR_ENABLE_1_ADDR      0x2000b210UL
#define INTR_ENABLE_2_ADDR      0x2000b214UL
#define INTR_ENABLE_BASE_ADDR   0x2000b218UL

/* TIMER ADDRESSES */
#define TIMER_BASE_ADDR 0x2000b000UL
#define TIMER_LOAD_ADDR 0x2000b400UL
#define TIMER_CTRL_ADDR 0x2000b408UL
#define TIMER_CLEAR_IRQ 0x2000b40CUL
#define TIMER_READ_IRQ  0x2000b410UL

/* TIMER BITS */
#define TIMER_ENABLE        7
#define TIMER_IRQ_ENABLE    5
#define TIMER_32BIT_MODE    1

/* GPIO ADDRESSES */
#define GPIO_BASE       0x20200000UL

#define GPFSEL4         0x20200010UL
#define GPSET1          0x20200020UL
#define GPCLR1          0x2020002CUL

#define LED_GPFSEL      21
#define LED_GPIO        15

#define LED_GPSET       GPIO_GPSET1
#define LED_GPCLR       GPIO_GPCLR1

#define GPIO_GPFSEL0    0
#define GPIO_GPFSEL1    1
#define GPIO_GPFSEL2    2
#define GPIO_GPFSEL3    3
#define GPIO_GPFSEL4    4
#define GPIO_GPFSEL5    5

#define GPIO_GPSET0     7
#define GPIO_GPSET1     8

#define GPIO_GPCLR0     10
#define GPIO_GPCLR1     11

#define GPIO_GPLEV0     13
#define GPIO_GPLEV1     14

#define GPIO_GPEDS0     16
#define GPIO_GPEDS1     17

#define GPIO_GPREN0     19
#define GPIO_GPREN1     20

#define GPIO_GPFEN0     22
#define GPIO_GPFEN1     23

#define GPIO_GPHEN0     25
#define GPIO_GPHEN1     26

#define GPIO_GPLEN0     28
#define GPIO_GPLEN1     29

#define GPIO_GPAREN0    31
#define GPIO_GPAREN1    32

#define GPIO_GPAFEN0    34
#define GPIO_GPAFEN1    35

#define GPIO_GPPUD      37
#define GPIO_GPPUDCLK0  38
#define GPIO_GPPUDCLK1  39 
