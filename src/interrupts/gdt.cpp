#include "../include/system.h"
#include "array.h"

extern "C" void gdt_flush();

namespace gdt {
    struct entry {
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_middle;
        uint8_t access;
        uint8_t granularity;
        uint8_t base_high;
    } __attribute__((packed));

    struct ptr {
        uint16_t limit;
        uint32_t base;
    } __attribute__ ((packed));
}

gdt::ptr gdt_ptr;

namespace gdt {

    array<entry, 5> gdt;

    void set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
        auto& entry = gdt[num];
        entry.base_low = (base & 0xFFFF);
        entry.base_middle = (base >> 16) & 0xFF;
        entry.base_high = (base >> 24) & 0xFF;

        entry.limit_low = (limit & 0xFFFF);
        entry.granularity = ((limit >> 16) & 0x0F);

        entry.granularity |= (gran & 0xF0);
        entry.access = access;
    }

    void main() {
        gdt_ptr.limit = (sizeof(entry) * 5) - 1;
        gdt_ptr.base = (uint32_t)&gdt;

        set_gate(0, 0, 0, 0, 0);                // Null segment

        set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment, 0x08 offset from GDT base

        set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment, 0x10 offset from GDT base

        set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment

        set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

        gdt_flush();
    }
}