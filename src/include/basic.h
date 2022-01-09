#pragma once
#include <cstdint>
#include <cstring>

namespace port {
    uint8_t get_byte(uint16_t port);
    void put_byte(uint16_t port, uint8_t value);
}