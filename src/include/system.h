#pragma once
#include <cstdint>

typedef void* type_t;

extern void move_csr();
extern void init_video();

extern void gdt_install();
extern void idt_install();
extern void isrs_install();

typedef struct regs
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} register_t;

void irq_install_handler(int32_t irq, void (*handler)(register_t *r));
void irq_uninstall_handler(int32_t irq);
void irq_install();

void irs_install_handler(int32_t irs, void (*handler)(register_t *r));

void timer_install(uint32_t frequency);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

void keyboard_install();