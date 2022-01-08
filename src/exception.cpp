#include "exception.h"
#include <cstddef>
#include <cstdint>
#include "array.h"

std::size_t exception_level = 0;
unowned_array<uint16_t, 80 * 25> exception_frame_buffer = (uint16_t*)0xb8000;

void throw_exception(const char* message) {
    if (exception_level >= 3) {
        for (;;);
    }
    for (size_t i = 0; message[i] != '\0'; i++) {
        exception_frame_buffer[i] = (4 << 8 | message[i]);
    }
    for (;;) {}
}

void __stack_chk_fail_local() {
    throw_exception("STACK_CHECK_FAIL_LOCAL");
}