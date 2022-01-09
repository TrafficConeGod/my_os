#include "system.h"
#include "debug.h"

namespace syscall {
    void handler(const isr::registers& registers) {
        dbg::print("Hello!");
    }

    void main() {
        isr::set_handler(0x80, handler);
    }
};