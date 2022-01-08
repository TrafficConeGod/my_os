#include <system.h>
#include "array.h"

struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__ ((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed));

array<idt_entry, 256> idt;
idt_ptr idtp;

extern "C" void idt_load();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].always0 = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

void* memset(void *s, int c,  unsigned int len) {
    unsigned char* p = (uint8_t*)s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}


void idt_install() {
    idtp.limit = (sizeof(idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    memset(&idt, 0, sizeof(idt_entry) * 256);

    idt_load();
}