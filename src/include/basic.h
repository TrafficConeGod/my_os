#pragma once
#include <cstdint>
#include <cstring>

uint8_t inportb(uint16_t _port);
void outportb(uint16_t _port, uint8_t _data);