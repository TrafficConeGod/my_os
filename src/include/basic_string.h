#pragma once
#include "unowned_array.h"
#include <cwctype>
#include <cstdio>

/**
 * @brief The string class for any character type (char, wchar_t, etc.)
 * 
 * @tparam T The type of the string
 */
template<typename T>
class basic_string : public unowned_array<T> {
    static std::size_t get_length(const T* str) {
        std::size_t i = 0;
        for (; str[i] != 0; i++);
        return i;
    }
    public:
        basic_string() {}
        /**
         * @param str The string pointer to use
         */
        basic_string(const T* str) : unowned_array<T>((T*)str, get_length(str)) {}

        /**
         * @brief Casts the raw string pointer
         */
        inline operator T*() {
            return array_base<unowned_array<T>, T>::get_data();
        }

        /**
         * @brief Casts the raw string pointer
         */
        inline operator const T*() const {
            return array_base<unowned_array<T>, T>::get_data();
        }

        /**
         * @brief Write function for debug library
         */
        void write() {
            for (auto ch : (*this)) {
                std::putchar(ch);
            }
        }
};

using string = basic_string<char>;
using wide_string = basic_string<wchar_t>;