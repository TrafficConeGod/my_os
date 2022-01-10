#pragma once
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include "exception.h"

template<typename T>
class dynamic_array {
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
            free(data);
        }

        inline T* get_data() { return data; }
        inline const T* get_data() const { return data; }
        inline std::size_t get_size() const { return size; }

        T& operator[](std::size_t index) {
            if (index >= size) {
                throw_index_out_of_bounds_exception(size, index);
            }
            return data[index];
        }

        const T& operator[](std::size_t index) const {
            if (index >= size) {
                throw_index_out_of_bounds_exception(size, index);
            }
            return data[index];
        }

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
        
        class iterator {
            private:
                dynamic_array& array_ref;
                size_t index;
            public:
                iterator(dynamic_array& _array, size_t _index) : array_ref(_array), index(_index) {}

                inline iterator& operator++() {
                    index++;
                    return *this;
                }

                inline bool operator!=(const iterator& it) const {
                    return index != it.index;
                }

                inline T& operator*() {
                    return array_ref.data[index];
                }
        };
        
        class const_iterator {
            private:
                const dynamic_array& array_ref;
                size_t index;
            public:
                const_iterator(const dynamic_array& _array, size_t _index) : array_ref(_array), index(_index) {}

                inline const_iterator& operator++() {
                    index++;
                    return *this;
                }

                inline bool operator!=(const const_iterator& it) const {
                    return index != it.index;
                }

                inline const T& operator*() const {
                    return array_ref.data[index];
                }
        };

        inline iterator begin() {
            return iterator(*this, 0);
        }

        inline iterator end() {
            return iterator(*this, size);
        }

        inline const const_iterator begin() const {
            return const_iterator(*this, 0);
        }

        inline const const_iterator end() const {
            return const_iterator(*this, size);
        }
};