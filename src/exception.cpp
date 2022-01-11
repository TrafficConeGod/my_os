#include "exception.h"
#include <cstddef>
#include <cstdint>
#include "debug.h"

std::size_t exception_level = 0;

void throw_exception(const char* message) {
    if (exception_level >= 3) {
        for (;;);
    }
    exception_level++;
    dbg::print("Exception: ", message, "\n");
    for (;;) {}
}

void throw_index_out_of_bounds_exception(std::size_t size, std::size_t index) {
    if (index >= size) {
        dbg::print("Index out of bounds: ", index, " >= ", size, "\n");
        throw_exception("Array index out of bounds");
    }
}

void __stack_chk_fail_local() {
    throw_exception("STACK_CHECK_FAIL_LOCAL");
}