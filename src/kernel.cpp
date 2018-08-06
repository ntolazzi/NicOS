#include "../header/terminal.h"
#include "../header/stdlib.h"

extern "C" void kernel_main(void* multiboot, uint16_t magicnumber){
    Terminal terminal;
    terminal.clear();
    terminal.print("Welcome to NicOS!!\n\nThis is my personal learning OS and will probably never be useful!\n", 1);
    char buf[10];
    for(int i=0;i<20;i++)
    {
        itoa(i, buf);
        terminal.print(buf,0);
        terminal.print(" with strlen ",0);
        int len = strlen(buf);
        itoa(len, buf);
        terminal.print(buf, 0);
        terminal.print("\n",0);
    }

    //while(1);
}
