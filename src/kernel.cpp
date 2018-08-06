#include "../header/terminal.h"
#include "../header/stdlib.h"

extern "C" void kernel_main(void* multiboot, uint16_t magicnumber){
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

    //while(1);
}
