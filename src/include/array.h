#pragma once
#include "array_base.h"
#include <initializer_list>

/**
 * @brief Array with a fixed size
 * 
 * @tparam T The type of the array
 */
template<typename T, std::size_t size>
class array : public array_base<array<T, size>, T> {
    T data[size];
    public:
        inline array() {}
        /**
         * @param list The list to initialize the array with
         */
        array(std::initializer_list<T> list) {
            array_base<array<T, size>, T>::in_range_check(list.size() - 1);
            std::size_t index = 0;
            for (const auto& elem : list) {
                data[index] = elem;
                index++;
            }
        }
        array(const array&) = delete;

        inline T* base_data() const { return (T*)data; }
        inline std::size_t base_size() const { return size; }
};