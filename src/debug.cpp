#include "debug.h"

#define IMPLEMENT_NUMBER_WRITE(type) \
template<> \
void write<type>(type val) { \
    write_number<type, 10, 1>(val); \
} \

namespace dbg {
    template<>
    void write<char>(char val) {
        putchar(val);
    }

    template<>
    void write<const char*>(const char* val) {
        std::puts(val);
    }

    template<>
    void write<bool>(bool val) {
        std::puts(val ? "true" : "false");
    }

    IMPLEMENT_NUMBER_WRITE(uint8_t)
    IMPLEMENT_NUMBER_WRITE(int16_t)
    IMPLEMENT_NUMBER_WRITE(uint16_t)
    IMPLEMENT_NUMBER_WRITE(int32_t)
    IMPLEMENT_NUMBER_WRITE(uint32_t)
    // IMPLEMENT_NUMBER_WRITE(int64_t)
    // IMPLEMENT_NUMBER_WRITE(uint64_t)
    // IMPLEMENT_NUMBER_WRITE(float)
    // IMPLEMENT_NUMBER_WRITE(double)
}