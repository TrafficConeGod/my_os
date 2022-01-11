#pragma once
#include "array_base.h"
#include <cstdlib>
#include <cstring>
#include <initializer_list>

template<typename T>
class dynamic_array : public array_base<dynamic_array<T>, T> {
    T* data;
    std::size_t size;
    public:
        dynamic_array(std::size_t _size) : data((T*)malloc(sizeof(T) * _size)), size(_size) {}
        dynamic_array(std::initializer_list<T> list) : data((T*)malloc(sizeof(T) * list.size())), size(list.size()) {
            std::size_t index = 0;
            for (const auto& elem : list) {
                (*this)[index] = elem;
                index++;
            }
        }
        dynamic_array(const dynamic_array& other) : data((T*)malloc(sizeof(T) * other.size)), size(other.size) {
            std::memcpy(data, other.data, sizeof(T) * other.size);
        }
        ~dynamic_array() {
            std::free(data);
        }

        inline T* base_data() const { return (T*)data; }
        inline std::size_t base_size() const { return size; }

        void push(const T& elem) {
            size++;
            data = (T*)realloc(data, sizeof(T) * size);
            data[size - 1] = elem;
        }

        T pop() {
            T elem = data[size - 1];
            size--;
            data = (T*)realloc(data, sizeof(T) * size);
            return elem;
        }
};