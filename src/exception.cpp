#include "exception.h"
#include <cstddef>
#include <cstdint>

uint16_t* exception_frame_buffer = (uint16_t*)0xb8000;

void throw_exception(const char* message) {
    for (size_t i = 0; message[i] != '\0'; i++) {
        exception_frame_buffer[i] = (4 << 8 | message[i]);
    }
    for (;;) {}
}

void __stack_chk_fail_local() {
    throw_exception("STACK_CHECK_FAIL_LOCAL");
}