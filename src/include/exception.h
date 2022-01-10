#pragma once
#include <cstddef>

void throw_exception(const char* message);
void throw_index_out_of_bounds_exception(std::size_t size, std::size_t index);