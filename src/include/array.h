#pragma once
#include <initializer_list>
#include <cstdio>
#include "exception.h"

template<typename T, std::size_t size>
class array {
    T data[size];
    public:
        array() {}
        array(const std::initializer_list<T>& list) {
            for (const T& elem : list) {
                (*this)[size] = elem;
            }
        }

        inline T& operator[](std::size_t index) {
            if (index >= size) {
                throw_exception("array index out of bounds");
            }
            return data[index];
        }

        inline const T& operator[](std::size_t index) const {
            if (index >= size) {
                throw_exception("array index out of bounds");
            }
            return data[index];
        }
};