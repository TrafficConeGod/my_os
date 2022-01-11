#pragma once
#include "array_base.h"
#include <initializer_list>

template<typename T, std::size_t size>
class array : public array_base<array<T, size>, T> {
    T data[size];
    public:
        array() {}
        array(std::initializer_list<T> list) {
            std::size_t index = 0;
            for (const auto& elem : list) {
                (*this)[index] = elem;
                index++;
            }
        }
        array(const array&) = delete;

        inline T* base_data() const { return (T*)data; }
        inline std::size_t base_size() const { return size; }
};