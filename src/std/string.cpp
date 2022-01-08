#include <cstring>

void* memcpy(void* dest, const void* src, std::size_t count) {
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    while (count > 0) {
        *dp++ = *sp++;
        count--;
    }
    return dest;
}

void* memset(void* dest, int ch, std::size_t count) {
    char *temp = (char *)dest;
    while (count > 0) {
        *temp++ = ch;
        count--;
    }
    return dest;
}

std::size_t strlen(const char* str) {
    std::size_t i = 0;
    for (; str[i] != '\0'; i++);
    return i;
}