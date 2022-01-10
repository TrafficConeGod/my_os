#pragma once
#include <initializer_list>
#include <cstdio>
#include <cstring>
#include "exception.h"
#include "debug.h"

template<typename T>
class unowned_array {
    T* data;
    std::size_t size;
    public:
        unowned_array(T* _data, std::size_t _size) : data(_data), size(_size) {}

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
        
        class iterator {
            private:
                unowned_array& array_ref;
                size_t index;
            public:
                iterator(unowned_array& _array, size_t _index) : array_ref(_array), index(_index) {}

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
                const unowned_array& array_ref;
                size_t index;
            public:
                const_iterator(const unowned_array& _array, size_t _index) : array_ref(_array), index(_index) {}

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

class string : public unowned_array<char> {
    public:
        string();
        string(const char* str);

        inline operator char*() {
            return get_data();
        }
        inline operator const char*() const {
            return get_data();
        }
};

template<typename T, std::size_t size>
class array {
    T data[size];
    public:
        array() {}
        array(std::initializer_list<T> list) {
            std::size_t index = 0;
            for (const auto& elem : list) {
                (*this)[index] = elem;
                index++;
            }
        }
        array(const array&) = delete;

        inline T* get_data() { return data; }
        inline const T* get_data() const { return data; }
        inline std::size_t get_size() const { return size; }

        inline unowned_array<T> get_unowned_array() {
            return unowned_array<T>(data, size);
        }

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
        
        class iterator {
            private:
                array& array_ref;
                size_t index;
            public:
                iterator(array& _array, size_t _index) : array_ref(_array), index(_index) {}

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
                const array& array_ref;
                size_t index;
            public:
                const_iterator(const array& _array, size_t _index) : array_ref(_array), index(_index) {}

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