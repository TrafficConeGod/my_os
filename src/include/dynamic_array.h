#pragma once
#include "array_base.h"
#include <cstdlib>
#include <cstring>
#include <initializer_list>

/**
 * @brief Dynamic heap-allocated array
 */
template<typename T>
class dynamic_array : public array_base<dynamic_array<T>, T> {
    T* data;
    std::size_t size;
    public:
        /**
         * @param _size The starting size of the array
         */
        dynamic_array(std::size_t _size) : data((T*)std::malloc(sizeof(T) * _size)), size(_size) {}

        /**
         * @param list The list to initialize the array with
         */
        dynamic_array(std::initializer_list<T> list) : data((T*)std::malloc(sizeof(T) * list.size())), size(list.size()) {
            array_base<dynamic_array<T>, T>::in_range_check(list.size() - 1);
            std::size_t index = 0;
            for (const auto& elem : list) {
                data[index] = elem;
                index++;
            }
        }

        /**
         * @param other The array to copy from
         */
        dynamic_array(const dynamic_array& other) : data((T*)std::malloc(sizeof(T) * other.size)), size(other.size) {
            std::memcpy(data, other.data, sizeof(T) * other.size);
        }
        inline ~dynamic_array() {
            std::free(data);
        }

        inline T* base_data() const { return (T*)data; }
        inline std::size_t base_size() const { return size; }

        /**
         * @brief Pushes an element to the end of the array
         */
        void push(const T& elem) {
            size++;
            data = (T*)realloc(data, sizeof(T) * size);
            data[size - 1] = elem;
        }

        /**
         * @brief Pushes a list of elements to the end of the array
         */
        void push(std::initializer_list<T> elems) {
            size += elems.size();
            data = (T*)realloc(data, sizeof(T) * size);
            std::size_t index = size - elems.size();
            for (const auto& elem : elems) {
                data[index] = elem;
                index++;
            }
        }

        /**
         * @brief Pushes an array of elements to the end of the array
         */
        template<typename U>
        void push(const U& array) {
            size += array.size();
            data = (T*)realloc(data, sizeof(T) * size);
            std::size_t index = size - array.size();
            for (const auto& elem : array) {
                data[index] = elem;
                index++;
            }
        }

        /**
         * @brief Pops the last element from the array
         */
        T pop() {
            T elem = data[size - 1];
            size--;
            data = (T*)realloc(data, sizeof(T) * size);
            return elem;
        }
};