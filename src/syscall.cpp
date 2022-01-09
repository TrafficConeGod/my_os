#include "system.h"
#include <cstdio>

namespace syscall {
    void handler(const isr::registers& registers) {
        puts("syscall worked\n");
    }

    void main() {
        isr::set_handler(0x80, handler);
    }
};