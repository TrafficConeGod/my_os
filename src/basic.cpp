#include <basic.h>

namespace port {
    uint8_t get_byte(uint16_t _port) {
        uint8_t rv;
        __asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (_port));
        return rv;
    }

    void put_byte(uint16_t _port, uint8_t _data) {
        __asm__ __volatile__("outb %1, %0" : : "dN" (_port), "a" (_data));
    }
};