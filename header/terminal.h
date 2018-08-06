#ifndef __TERMINAL_H
#define __TERMINAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

class Terminal
{
    const static unsigned short COLS=80;
    const static unsigned short ROWS=25;
    public:
        Terminal();
        ~Terminal();
        void clear();
        void print(char*);
        void printColorful(char*);
        void setColor(uint8_t, uint8_t);
        void resetColor();
        void writeTo(char*, uint8_t, uint8_t);
    private:
        uint16_t* VideoMemory;
        void putChar(char);
        uint8_t currentCol;
        uint8_t currentRow;
        uint8_t Color;
};

#endif
