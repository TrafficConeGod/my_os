#include "exception.h"
#include <cstddef>
#include <cstdint>
#include "debug.h"
#include "array.h"

std::size_t exception_level = 0;

void throw_exception(const char* message) {
    if (exception_level >= 3) {
        for (;;);
    }
    exception_level++;
    dbg::print("Exception: ", message, "\n");
    for (;;) {}
}

void __stack_chk_fail_local() {
    throw_exception("STACK_CHECK_FAIL_LOCAL");
}