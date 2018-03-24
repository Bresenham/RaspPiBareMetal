ifeq ($(arg), c)
doingC:
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles  CProgs/test.c -o kernel.elf
	arm-none-eabi-objcopy kernel.elf -O binary kernel.img
endif
ifeq ($(arg), asm)
doingASM:
	arm-none-eabi-as ASMProgs/test.s -o ASMProgs/a.out
	arm-none-eabi-objcopy ASMProgs/a.out -O binary kernel.img
endif
