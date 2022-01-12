#include <cstdlib>
#include "basic.h"
#include "unowned_array.h"

extern void* end;
unowned_array<char> heap((char*)end, 0x10000);
std::size_t current_heap_index = 0;

struct chunk_header {
    std::size_t size;
};

void* malloc(std::size_t size) {
    while (!heap.compare_range_to_value(current_heap_index, sizeof(chunk_header) + size, 0x00)) {
        current_heap_index += size;
        current_heap_index %= heap.get_size(); // this and below are risky cause this could literally just cause a stack overflow if the heap is full
    }

    auto& header = heap.at_as<chunk_header>(current_heap_index);
    header.size = size;

    current_heap_index += sizeof(chunk_header);
    void* ptr = (void*)&heap[current_heap_index];
    current_heap_index += size;
    return ptr;
}

void free(void* ptr) {
    std::size_t index = (std::uintptr_t)ptr - (std::size_t)heap.get_data();
    index -= sizeof(chunk_header);
    auto header = heap.at_as<chunk_header>(index);
    heap.set_range(index, sizeof(chunk_header) + header.size, 0x00);
}

void* realloc(void* ptr, std::size_t size) {
    std::size_t old_index = (std::uintptr_t)ptr - (std::size_t)heap.get_data();

    void* new_ptr = std::malloc(size);
    std::size_t new_index = (std::uintptr_t)new_ptr - (std::size_t)heap.get_data();

    heap.copy_range(new_index, size, heap, old_index);

    std::free(ptr);
    return new_ptr;
}