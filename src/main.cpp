#include "include/system.h"
#include <cstring>
#include "array.h"
#include "function.h"
#include "debug.h"


using constructor = function<void()>;
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

array<uint32_t, 10> array_test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

extern "C" void k_main() {
    gdt::main();
    idt::main();
    isr::main();
    keyboard::main();

    __asm__ __volatile__("sti");
    dbg::print("System started successfully!\n");
    for (;;);
}