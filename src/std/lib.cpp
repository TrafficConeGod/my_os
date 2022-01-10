#include <cstdlib>
#include "array.h"

extern void* end;
unowned_array<char> heap((char*)end, 0x10000);
std::size_t current_heap_index = 0;

// void* malloc(std::size_t size) {
    
// }

// void free(void* ptr) {

// }

// void* realloc(void* ptr, std::size_t size) {

// }