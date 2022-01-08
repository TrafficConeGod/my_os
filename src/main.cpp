#include "include/system.h"
#include <cstdio>
#include <cstring>

extern "C" void k_main() {
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();

    keyboard_install();

    __asm__ __volatile__("sti");
    std::puts("System Start!\n");

    for(;;);
}