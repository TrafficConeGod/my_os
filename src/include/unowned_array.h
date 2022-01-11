#pragma once
#include "array_base.h"

template<typename T>
class unowned_array : public array_base<unowned_array<T>, T> {
    T* data;
    std::size_t size;
    public:
        unowned_array(T* _data, std::size_t _size) : data(_data), size(_size) {}

        inline T* base_data() const { return (T*)data; }
        inline std::size_t base_size() const { return size; }
};