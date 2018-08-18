#ifndef GDT_H 
#define GDT_H
#include <stdint.h>
#define GDT_ENTRIES 3
void init_gdt();
void load_gdt();
void set_gdt_entry(int, uint32_t, unsigned int, int);
extern uint64_t gdt[GDT_ENTRIES];
#endif
