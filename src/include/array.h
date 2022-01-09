#pragma once
#include <initializer_list>
#include <cstdio>
#include <cstring>
#include "debug.h"
#include "exception.h"

template<typename T, std::size_t _size>
class array {
    T data[_size];
    public:
        array() {}
        array(std::initializer_list<T> list) {
            std::size_t index = 0;
            for (const auto& elem : list) {
                (*this)[index] = elem;
                index++;
            }
        }

        inline std::size_t size() const { return _size; }

        inline T& operator[](std::size_t index) {
            if (index >= _size) {
                dbg::print("Index out of bounds:", index, ">=", _size);
                throw_exception("Array index out of bounds");
            }
            return data[index];
        }

        inline const T& operator[](std::size_t index) const {
            if (index >= _size) {
                dbg::print("Index out of bounds:", index, ">=", _size);
                throw_exception("Array index out of bounds");
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
                    return array_ref[index];
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
                    return array_ref[index];
                }
        };

        inline iterator begin() {
            return iterator(*this, 0);
        }

        inline iterator end() {
            return iterator(*this, _size);
        }

        inline const const_iterator begin() const {
            return const_iterator(*this, 0);
        }

        inline const const_iterator end() const {
            return const_iterator(*this, _size);
        }
};

template<typename T, std::size_t _size>
class unowned_array {
    T* data;
    public:
        unowned_array(T* _data) : data(_data) {}

        inline std::size_t size() const { return _size; }

        inline T& operator[](std::size_t index) {
            if (index >= _size) {
                throw_exception("Array index out of bounds");
            }
            return data[index];
        }

        inline const T& operator[](std::size_t index) const {
            if (index >= _size) {
                throw_exception("Array index out of bounds");
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
                    return array_ref[index];
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
                    return array_ref[index];
                }
        };

        inline iterator begin() {
            return iterator(*this, 0);
        }

        inline iterator end() {
            return iterator(*this, _size);
        }

        inline const const_iterator begin() const {
            return const_iterator(*this, 0);
        }

        inline const const_iterator end() const {
            return const_iterator(*this, _size);
        }
};