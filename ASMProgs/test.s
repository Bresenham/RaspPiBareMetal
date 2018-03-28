.section .init
.global main

 main:
    /* Set GPIO Pin 47 as Output */
    ldr r0,=0x20200010
    mov r1,#1
    lsl r1,#21
    str r1,[r0]

    mov r1,#1
    lsl r1,#15
infty:
    ldr r3,=0x00000000
    mov r4,#5
    str r4,[r3]
    ldr r5,[r3]
    cmp r5,r4
    beq  equal
    /* Set GPIO Pin 47 Low */
    str r1,[r0,#0x18]
    b   infty
equal:
    /* Set GPIO Pin 47 High */
    str r1,[r0,#0x10]
    b   infty
