#include "../header/ports.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*These are the asm routines that access hardware ports*/
static inline uint8_t Read8(uint16_t port)
{
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}
static inline uint16_t Read16(uint16_t port)
{
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}
static inline uint32_t Read32(uint16_t port)
{
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}

static inline void Write8(uint16_t port, uint8_t data)
{
    __asm__ volatile("outb %0, %1" : : "a"(data), "Nd" (port));
}
static inline void Write16(uint16_t port, uint16_t data)
{
    __asm__ volatile("outw %0, %1" : : "a"(data), "Nd" (port));
}
static inline void Write32(uint16_t port, uint32_t data)
{
    uint32_t result;
    __asm__ volatile("outl %0, %1" : : "a"(data), "Nd" (port));
}





/*Base class from which other classes derive*/
Port::Port(uint16_t portnumber)
{
        this->portnumber = portnumber;
}

Port::~Port()
{
}

Port8Bit::Port8Bit(uint16_t portnumber)
        : Port(portnumber)
{
}

Port8Bit::~Port8Bit()
{
}

void Port8Bit::Write(uint8_t data)
{
        Write8(portnumber, data);
}

uint8_t Port8Bit::Read()
{
        return Read8(portnumber);
}

Port16Bit::Port16Bit(uint16_t portnumber)
        : Port(portnumber)
{
}

Port16Bit::~Port16Bit()
{
}

void Port16Bit::Write(uint16_t data)
{
        Write16(portnumber, data);
}

uint16_t Port16Bit::Read()
{
        return Read16(portnumber);
}

Port32Bit::Port32Bit(uint16_t portnumber)
        : Port(portnumber)
{
}

Port32Bit::~Port32Bit()
{
}

void Port32Bit::Write(uint32_t data)
{
        Write32(portnumber, data);
}

uint32_t Port32Bit::Read()
{
        return Read32(portnumber);
}
