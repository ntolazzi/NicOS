#ifndef __PORT_H
#define __PORT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
/*Base class from which other classes derive*/
class Port
{
    protected:
        Port(uint16_t portnumber);
        ~Port();
        uint16_t portnumber;
};

class Port8Bit : public Port
{

    public:
        Port8Bit(uint16_t portnumber);
        ~Port8Bit();

        uint8_t Read();
        void Write(uint8_t data);
};
class Port16Bit : public Port
{

    public:
        Port16Bit(uint16_t portnumber);
        ~Port16Bit();

        uint16_t Read();
        void Write(uint16_t data);
};
class Port32Bit : public Port
{

    public:
        Port32Bit(uint16_t portnumber);
        ~Port32Bit();

        uint32_t Read();
        void Write(uint32_t data);
};

#endif
