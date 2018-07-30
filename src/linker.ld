/* The bootloader looks for symbol _start as the entry point*/
ENTRY(_start)

SECTIONS
{
    /*Bootloader usually loads us to 1MiB*/
    . = 1M;

    .text BLOCK(4k) : ALIGN(4k)
    {
        /* Put multiboot header first as it is necessary for the bootloader to 
         * recognize the file*/
        *(.multiboot)
        *(.text)
    }

    /* All the following sections are necessary for producing a proper ELF binary*/
    /* Read-only data */
    .rodata BLOCK(4k) : ALIGN(4k)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
