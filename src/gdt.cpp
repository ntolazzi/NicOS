#include "../header/gdt.h"

uint64_t gdt[GDT_ENTRIES];

void set_gdt_entry(int i, uint32_t base, unsigned int limit, int flags)
{
    /* base is 32bit, limit is 20bit, flags are together 12 bits separated into
     * 1 byte describing the access and 4 bit for flags
     * 
     * 0:15     ->  limit   0:15
     * 16:39    ->  base    0:23
     * 40:47    ->  flags   0:7     Access byte
     * 48:51    ->  limit   16:19
     * 52:55    ->  flags   8:11    Flags
     * 56:63    ->  base    24:31
     * for a graphical bitmap and description see: https://wiki.osdev.org/GDT
     * */
    gdt[i] = limit & 0xffffLL;
    gdt[i] |= (base & 0xffffffLL) << 16;
    gdt[i] |= (flags & 0xffLL) << 40;
    gdt[i] |= ((limit >> 16) & 0xfLL) << 48;
    gdt[i] |= ((flags >> 8 )& 0xffLL) << 52;
    gdt[i] |= ((base >> 24) & 0xffLL) << 56;
}

void init_gdt()
{
    set_gdt_entry(0, 0, 0, 0); //Data Segment
    set_gdt_entry(1, 0, 0xffffffff, 0xC92); //Data Segment
    set_gdt_entry(2, 0, 0xffffffff, 0xC9A); //Code Segment
}

void load_gdt()
{
    init_gdt();
    /* Define a struct with excactly the right structure for the GDT*/
    struct {
        uint16_t limit;
        void* pointer;
    }__attribute__((packed)) gdtp = {
        .limit = GDT_ENTRIES * 8 -1, .pointer=gdt
    };
    asm volatile("lgdt %0" : : "m" (gdtp));
    /* Reload registers */
    asm volatile("mov $0x08, %eax"); //0x08 point at the new data selector
    asm volatile("mov %eax, %ds");
    asm volatile("mov %eax, %es");
    asm volatile("mov %eax, %fs");
    asm volatile("mov %eax, %gs");
    asm volatile("mov %eax, %ss");
    asm volatile("ljmpl $0x10, $1f\n\t 1:"); //points at the new code selector
}
