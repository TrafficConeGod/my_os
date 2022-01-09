#include "system.h"
#include <cstdio>

void syscall_handler(const registers& registers) {
    puts("syscall worked\n");
}

void syscall_install() {
    // isr_install_handler(0x80, syscall_handler);
}