#include "../header/terminal.h"

extern "C" void kernel_main(void* multiboot, uint16_t magicnumber){
    Terminal terminal;
    terminal.clear();
    terminal.print("Welcome to NicOS!!\n\nThis is my personal learning OS and will probably never be useful!\n", 1);

    while(1);
}
