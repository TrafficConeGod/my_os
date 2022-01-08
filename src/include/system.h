#pragma once
#include <cstdint>
#include "function.h"

typedef void* type_t;

extern void move_csr();

extern void gdt_install();
extern void idt_install();
extern void isrs_install();

struct registers {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void irq_install_handler(int32_t irq, function<void(registers*)> handler);
void irq_uninstall_handler(int32_t irq);
void irq_install();

void irs_install_handler(int32_t irs, function<void(registers*)> handler);

void timer_install(uint32_t frequency);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

void keyboard_install();