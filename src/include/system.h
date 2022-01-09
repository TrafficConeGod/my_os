#pragma once
#include <cstdint>
#include <cstddef>
#include "function.h"

void putnum(uint32_t num, std::size_t base, std::size_t min_digits);

extern void move_csr();

extern void gdt_install();
extern void idt_install();
extern void isr_main();

struct registers {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void add_interrupt_handler(uint32_t interrupt_id, function<void(const registers&)> handler);

void timer_install(uint32_t frequency);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

void keyboard_install();