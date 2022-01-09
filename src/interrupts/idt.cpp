#include <system.h>
#include "array.h"
#include <cstring>

extern "C" void idt_load();

namespace idt {
    struct entry {
        uint16_t base_lo;
        uint16_t sel;
        uint8_t always0;
        uint8_t flags;
        uint16_t base_hi;
    } __attribute__ ((packed));

    struct ptr {
        uint16_t limit;
        uint32_t base;
    } __attribute__ ((packed));
}

idt::ptr idt_ptr;

namespace idt {
    array<entry, 256> idt;

    void set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
        auto& entry = idt[num];
        entry.base_lo = base & 0xFFFF;
        entry.base_hi = (base >> 16) & 0xFFFF;
        entry.always0 = 0;
        entry.sel = sel;
        entry.flags = flags;
    }

    void main() {
        idt_ptr.limit = (sizeof(entry) * 256) - 1;
        idt_ptr.base = (uint32_t)&idt;

        memset(&idt, 0, sizeof(entry) * 256);

        idt_load();
    }
}