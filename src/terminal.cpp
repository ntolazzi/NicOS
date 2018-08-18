#include "../header/terminal.h"

Terminal::Terminal()
    : Color(0x0F), VideoMemory((uint16_t*)0xb8000), fb_control(0x3D4), fb_data(0x3D5) {}

Terminal::~Terminal(){}

void Terminal::clear()
{
    for(int col=0; col<COLS;col++){
        for(int row =0; row<ROWS;row++){
            unsigned int index = COLS*row+col;
            VideoMemory[index] = ((uint16_t)Color <<8) | ' ';
        }
    }
}

void Terminal::setColor(uint8_t fg, uint8_t bg)
{
    Color = bg<<4 | fg;
}

void Terminal::resetColor(){Color=0x0F;}

void Terminal::putChar(char c)
{
    switch(c)
    {
        case '\n':
            {
                currentCol = 0;
                currentRow++;
                break;
            }
        default:
            {
                unsigned int index = COLS*currentRow+currentCol;
                VideoMemory[index] = ((uint16_t)Color <<8) | c;
                currentCol++;
            }
        if(currentCol >= COLS)
        {
            currentCol=0;
            currentRow++;
        }
        if(currentRow >= ROWS)
        {
            scrollLine();
            currentRow--;
        }
    }
}

void Terminal::scrollLine()
{
    for(int i=0;i<COLS*(ROWS);i++)
    {
        VideoMemory[i] = VideoMemory[i+COLS];
    }
    //for(int i=COLS*(ROWS-1); i<COLS*ROWS;i++)
    //{
        //VideoMemory[i] == ((uint16_t)Color <<8) | ' ';
    //}

}

void Terminal::writeTo(char* str, uint8_t col,uint8_t row)
{
    //uint8_t rowBefore = currentRow;
    //uint8_t colBefore = currentCol;
    currentRow = row;
    currentCol = col;
    for(int i=0; str[i]!='\0';i++)
        putChar(str[i]);
    //currentRow = rowBefore;
    //currentCol = colBefore;
}

void Terminal::moveCursor(int x, int y)
{
    unsigned int index = COLS*y+x;
    fb_control.Write(0x0F);
    fb_data.Write((uint8_t) (165 & 0xFF));
    fb_control.Write(0x0E);
    fb_data.Write((uint8_t) ((165 >> 8) & 0xFF));
}

void Terminal::print(char* str)
{
    resetColor();
    for(int i=0; str[i]!='\0';i++)
    {
        putChar(str[i]);
    }
}

void Terminal::printColorful(char* str)
{
    unsigned int color_wheel = 1;
    uint8_t fg;
    uint8_t bg = 0;
    for(int i=0; str[i]!='\0';i++)
    {
        fg = color_wheel;
        if(color_wheel>14)
        {
            color_wheel = 0;
            bg++;
        }
        if(bg>14)
            bg=0;
        setColor(fg, 0);
        color_wheel++;
        putChar(str[i]);
    }
}
