import "../header/ports.h"

Port8Bit pic_master_command(0x20);
Port8Bit pic_master_data(0x21);
Port8Bit pic_slave_command(0xa0);
Port8Bit pic_slave_data(0xa1);
    
void init_pic()
{
    /* Commands taken from http://skelix.net/skelixos/tutorial04_en.html */
    pic_master_command.Write(0x11);
    pic_slave_command.Write(0x11);
    pic_master_data.Write(0x20);
    pic_slave_data.Write(0x28);
    pic_master_data.Write(0x04);
    pic_slave_data.Write(0x02);
    pic_master_data.Write(0x01);
    pic_slave_data.Write(0x01);
}

uint64_t idt[GDT_ENTRIES];

void set_idt_entry(int i, uint32_t base, uint16_t selector)
{
    /* base is 32bit, limit is 20bit, flags are together 12 bits separated into
     * 1 byte describing the access and 4 bit for flags
     * 
     * 0:15     ->  base        0:15
     * 16:31    ->  selector    0:15
     * 32:39    ->  0 unused
     * 40:43    ->  1110 interrrupt gate 32bit / gate type
     * 44       ->  0 storage segment bit
     * 45:46    ->  00 privilege level
     * 47       ->  0 present bit
     * 48:63    ->  base        16:31
     * for a graphical bitmap and description see: https://wiki.osdev.org/IDT
     * */
    uint8_t zero = 0;
    
    idt[i] = base & 0xffffLL;
    idt[i] |= selector << 16;
    idt[i] |= zero << 32;
    idt[i] |= 0b00001110 << 40;
    idt[i] |= ((base >> 16) & 0xffffLL) << 48;
}
