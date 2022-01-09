#include "include/system.h"
// #include <cstdio>
#include <cstring>
#include "array.h"
#include "function.h"


using constructor = function<void()>;
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void k_main() {
    gdt::main();
    idt::main();
    isr::main();
    keyboard::main();

    __asm__ __volatile__("sti");
    std::puts("System Start!\n\n");
    for (;;);
}