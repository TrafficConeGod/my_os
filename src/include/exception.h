#pragma once
#include <cstddef>

/**
 * @brief Throws exception with message
 */
void throw_exception(const char* message);

/**
 * @brief Throws index out of range exception
 * 
 * @param size The size to display
 * @param index The index to display
 */
void throw_index_out_of_range_exception(std::size_t size, std::size_t index);