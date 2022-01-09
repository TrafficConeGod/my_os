#pragma once
#include <cstdint>
#include <cstddef>
#include "function.h"

void putnum(uint32_t num, std::size_t base, std::size_t min_digits);

extern void move_csr();

namespace gdt {
    void main();
};

namespace idt {
    void main();

    void set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
};

namespace isr {
    void main();

    struct registers {
        uint32_t gs, fs, es, ds;
        uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
        uint32_t int_no, err_code;
        uint32_t eip, cs, eflags, useresp, ss;
    };

    void set_handler(uint32_t interrupt_id, function<void(const registers&)> handler);
    void remove_handler(uint32_t interrupt_id);
};

namespace timer {
    void main(uint32_t frequency);
};

namespace keyboard {
    void main();
};

namespace syscall {
    void main();
};