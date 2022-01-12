#include "include/system.h"
#include <cstring>
#include "array.h"
#include "function.h"
#include "debug.h"
#include "dynamic_array.h"

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
    syscall::main();
    keyboard::main();

    __asm__ __volatile__("sti");
    dbg::print("System started successfully!\n");

    dynamic_array<int> arr = { 1, 2, 3 };

    arr.push({ 4, 5, 6 });
    arr.push({ 1, 2, 4 });

    for (auto i : arr) {
        dbg::print(i, ", ");
    }
    dbg::print("\n");

    asm volatile("int $0x80");
    for (;;);
}