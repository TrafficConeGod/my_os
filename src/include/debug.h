#pragma once
#include <cstdint>
#include <cstdio>

class string;

#define DEFINE_WRITE(type) \
template<> \
void write<type>(type val);

namespace dbg {
    template<typename T>
    void write(T val) {
        val.write();
    }

    template<typename T, size_t base, size_t min_digits>
    void write_number(T number) {
        size_t digits = 0;
        T current = number;

        while (current != 0) {
            current /= base;
            digits++;
        }

        if (digits < min_digits) {
            digits = min_digits;
        }
        if (number == 0 && digits == 0) {
            digits = 1;
        }

        char chars[digits + 1];
        chars[digits] = '\0';

        for (size_t i = 0; i < digits; i++) {
            size_t digit = number % (T)base;
            number /= (T)base;

            char ch;
            if (digit >= 10) {
                ch = 0x41 + (digit - 10);
            } else {
                ch = 0x30 + digit;
            }
            chars[(digits - 1) - i] = ch;
        }
        std::puts(chars);
    }

    template<typename T, size_t base, size_t min_digits>
    class number_writer {
        T val;
        public:
            number_writer(T _val) : val(_val) {}

            inline void write() {
                write_number<T, base, min_digits>(val);
            }
    };

    DEFINE_WRITE(char)
    DEFINE_WRITE(bool)
    DEFINE_WRITE(const char*)
    DEFINE_WRITE(string)
    
    DEFINE_WRITE(uint8_t)
    DEFINE_WRITE(int16_t)
    DEFINE_WRITE(uint16_t)
    DEFINE_WRITE(int32_t)
    DEFINE_WRITE(uint32_t)
    DEFINE_WRITE(int64_t)
    DEFINE_WRITE(uint64_t)
    DEFINE_WRITE(float)
    DEFINE_WRITE(double)

    inline void sub_print() {}

    template<typename T, typename ...Types>
    void sub_print(T arg, Types... args) {
        write<T>(arg);
        write<char>(' ');
        sub_print(args...);
    }

    template<typename ...Types>
    void print(Types... args) {
        sub_print(args...);
        write<char>('\n');
    }
};