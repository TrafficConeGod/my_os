#pragma once
#include <cstdint>
#include <cstring>

uint8_t inportb(uint16_t port);
void outportb(uint16_t port, uint8_t data);