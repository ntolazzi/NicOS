#include "../header/terminal.h"
#include "../header/stdlib.h"
#include <stdint.h>
#include "../header/ports.h"
#include "../header/gdt.h"

extern "C" void kernel_main(void* multiboot, uint16_t magicnumber){
    load_gdt();
    Terminal terminal;
    terminal.clear();
    terminal.printColorful("Welcome to NicOS!!\n\nThis is my personal learning OS and will probably never be useful!\n\n");
    char buf[10];
    for(int i=-5;i<6;i++)
    {
        itoa(i, buf);
        terminal.print(buf);
        terminal.print("\n");
    }
    
    terminal.moveCursor(5, 5);
    

    //while(1);
}
