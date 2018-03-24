.section .init
.global main

 main:
    /* Set GPIO Pin 2 as Output */
    ldr r0,=0x20200000
    mov r1,#1
    lsl r1,#6
    str r1,[r0]

    mov r1,#1
    lsl r1,#2
infty:
    /* Set GPIO Pin 2 High */
    str r1,[r0,#0x1C]

    /* Set GPIO Pin 2 Low */
    str r1,[r0,#0x28]

    b   infty
