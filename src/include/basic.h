#pragma once
#include <cstdint>
#include <cstring>

namespace port {
    /**
     * @brief Get the byte at a port
     */
    uint8_t get_byte(uint16_t port);
    /**
     * @brief Put the byte at a port
     */
    void put_byte(uint16_t port, uint8_t value);
}