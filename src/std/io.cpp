#include <cstdio>
#include <cstdarg>
#include <cstdint>
#include <cstddef>
#include "basic.h"
#include "unowned_array.h"

FILE* stdout = nullptr; // i love the c++ version of the c standard library

unowned_array<uint16_t> frame_buffer((uint16_t*)0xb8000, 80 * 25);
const size_t frame_buffer_width = 80;
const size_t frame_buffer_height = 25;
const size_t frame_buffer_size = frame_buffer_width * frame_buffer_height;
size_t frame_buffer_position = 0;

void move_csr() {
    port::put_byte(0x3D4, 14);
    port::put_byte(0x3D5, frame_buffer_position >> 8);
    port::put_byte(0x3D4, 15);
    port::put_byte(0x3D5, frame_buffer_position);
}

int putchar(int ch) {
    switch (ch) {
        case '\n':
            frame_buffer_position += frame_buffer_width - (frame_buffer_position % frame_buffer_width);
            return 1;
        case '\0': return 0;
        default:
            frame_buffer[frame_buffer_position] = (7 << 8 | ch);
            frame_buffer_position++;
            frame_buffer_position %= frame_buffer_size;
            return 1;
    }
    move_csr();
    return 0;
}

int putc(int ch, FILE* stream) { // same here fun fun fun fun
    return putchar(ch);
}

int puts_nnl(const char* str) {
    while (putchar(*str++));
    return 1;
}

int puts(const char* str) {
    while (putchar(*str++));
    return 1;
}

void putnum(uint32_t num, size_t base, size_t min_digits) {
    uint32_t digits = 0;
    uint32_t cur = num;
    while (cur != 0) {
        cur /= base;
        digits++;
    }

    if (digits < min_digits) {
        digits = min_digits;
    }

    char str[digits + 1];
    str[digits] = '\0';

    for (uint32_t i = 0; i < digits; i++) {
        // get the value of the digit
        uint32_t digit = num % base;
        num /= base;

        char ch;
        if (digit >= 10) {
            ch = 0x41 + (digit - 10);
        } else {
            ch = 0x30 + digit;
        }
        str[(digits - 1) - i] = ch;
    }
    puts_nnl(str);
}

// doesnt work :(
    
// int printf(const char* fmt, ...) {
//     va_list args;
//     va_start(args, fmt);

//     while (*fmt != '\0') {
//         if (*fmt != '%') {
//             if (!putchar(*fmt)) {
//                 break;
//             }
//             fmt++;
//             continue;
//         }
//         fmt++;
//         switch (*fmt) {
//             case 'c': putchar(va_arg(args, int)); break;
//             case 's': puts_nnl(va_arg(args, const char*)); break;
//             case 'd': putnum(va_arg(args, uint32_t), 10, 1); break;
//             case 'x': putnum(va_arg(args, uint32_t), 16, 1); break;
//         }
//         fmt++;
//     }

//     va_end(args);
//     return 0;
// }

// int __printf_chk(int, const char* fmt, ...) {
//     va_list args;
//     va_start(args, fmt);

//     printf(fmt, args);

//     va_end(args);
//     return 0;
// }