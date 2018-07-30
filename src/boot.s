/*This is all defined in the multiboot standard*/
/*This defines constants related to the multiboot header*/
.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO     /*Add configuration flags*/
.set MAGIC,     0x1BADB002          /*this number is necessary so the bootloader finds the kernel*/
.set CHECKSUM,  -(MAGIC + FLAGS)

/*Add the above defined values to the assembly*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


/*Reserve space for the stack*/
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:


/*
The linker script specifies _start as the entry point to the kernel and the
bootloader will jump to this position.
*/
.section .text
.global _start
.type _start, @function
_start:
    /*
    The bootloader has loaded us into 32-bit protected mode on a x86
    machine. Interrupts are disabled. Paging is disabled. The processor
    state is as defined in the multiboot standard.*/

    /*Now we set the stack pointer register(esp) to our above defined stack,
    as a stack is necessary for languages like C to work*/

    mov $stack_top, %esp
    
    /*Entry point to kernel. If we unexpectedly return from it, put 
    the system into an infinite loop*/
    call kernel_main

    cli
1:  hlt
    jmp 1b


