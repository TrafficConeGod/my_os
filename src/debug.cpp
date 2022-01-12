#include "debug.h"
#include "basic_string.h"

namespace dbg {
    template<>
    void write<bool>(bool val) {
        std::puts(val ? "true" : "false");
    }
}