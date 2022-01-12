#pragma once
#include "unowned_array.h"
#include <cwctype>
#include <cstdio>

template<typename T>
class basic_string : public unowned_array<T> {
    static std::size_t get_length(const T* str) {
        std::size_t i = 0;
        for (; str[i] != 0; i++);
        return i;
    }
    public:
        basic_string() {}
        basic_string(const T* str) : unowned_array<T>((T*)str, get_length(str)) {}

        inline operator T*() {
            return array_base<unowned_array<T>, T>::get_data();
        }
        inline operator const T*() const {
            return array_base<unowned_array<T>, T>::get_data();
        }

        void write() {
            for (auto ch : (*this)) {
                std::putchar(ch);
            }
        }
};

using string = basic_string<char>;
using wide_string = basic_string<wchar_t>;