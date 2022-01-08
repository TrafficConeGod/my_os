#include "include/system.h"
#include <cstdio>
#include <cstring>
#include "array.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void k_main() {
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();

    keyboard_install();

    __asm__ __volatile__("sti");
    std::puts("System Start!\n");

    for (;;);
}