#pragma once
#include <cstddef>
#include <cstring>
#include "exception.h"
#include "debug.h"

template<typename S, typename T>
class array_base {
    inline T* data() const { return ((const S*)this)->base_data(); }
    inline std::size_t size() const { return ((const S*)this)->base_size(); }
    public:
        inline T* get_data() { return data(); }
        inline const T* get_data() const { return data(); }
        inline std::size_t get_size() const { return size(); }

        inline bool is_in_range(std::size_t index) const {
            return index < size();
        }

        inline void in_range_check(std::size_t index) const {
            if (!is_in_range(index)) {
                throw_index_out_of_bounds_exception(size(), index);
            }
        }

        T& operator[](std::size_t index) {
            in_range_check(index);
            return data()[index];
        }

        const T& operator[](std::size_t index) const {
            in_range_check(index);
            return data()[index];
        }

        template<typename U>
        U& at_as(std::size_t index) {
            in_range_check(index);
            in_range_check(index + sizeof(U) - 1);
            return (U&)data()[index];
        }

        template<typename U>
        const U& at_as(std::size_t index) const {
            in_range_check(index);
            in_range_check(index + sizeof(U) - 1);
            return (const U&)data()[index];
        }

        void set_range(std::size_t index, std::size_t count, const T& value) {
            in_range_check(index);
            in_range_check(index + count - 1);
            for (std::size_t i = index; i < (index + count); i++) {
                data()[i] = value;
            }
        }

        template<typename U>
        void copy_range(std::size_t index, std::size_t count, const U& array, std::size_t array_index) {
            in_range_check(index);
            in_range_check(index + count - 1);
            array.in_range_check(array_index);
            array.in_range_check(array_index + count - 1);
            for (std::size_t i = index; i < (index + count); i++) {
                data()[i] = array[(array_index + i) - index];
            }
        }

        bool compare_range_to_value(std::size_t index, std::size_t count, const T& value) const {
            in_range_check(index);
            in_range_check(index + count - 1);
            for (std::size_t i = index; i < (index + count); i++) {
                if (data()[i] != value) {
                    return false;
                }
            }
            return true;
        }

        template<typename U>
        bool compare_range_to_range(std::size_t index, std::size_t count, const U& array, std::size_t array_index) const {
            in_range_check(index);
            in_range_check(index + count - 1);
            array.in_range_check(array_index);
            array.in_range_check(array_index + count - 1);
            for (std::size_t i = index; i < (index + count); i++) {
                if (data()[i] != array[(array_index + i) - index]) {
                    return false;
                }
            }
            return true;
        }
        
        class iterator {
            private:
                array_base& array_ref;
                size_t index;
            public:
                inline iterator(array_base& _array, size_t _index) : array_ref(_array), index(_index) {}

                inline iterator& operator++() {
                    index++;
                    return *this;
                }

                inline bool operator!=(const iterator& it) const {
                    return index != it.index;
                }

                inline T& operator*() {
                    return array_ref.data()[index];
                }
        };
        
        class const_iterator {
            private:
                const array_base& array_ref;
                size_t index;
            public:
                inline const_iterator(const array_base& _array, size_t _index) : array_ref(_array), index(_index) {}

                inline const_iterator& operator++() {
                    index++;
                    return *this;
                }

                inline bool operator!=(const const_iterator& it) const {
                    return index != it.index;
                }

                inline const T& operator*() const {
                    return array_ref.data()[index];
                }
        };

        inline iterator begin() {
            return iterator(*this, 0);
        }

        inline iterator end() {
            return iterator(*this, size());
        }

        inline const const_iterator begin() const {
            return const_iterator(*this, 0);
        }

        inline const const_iterator end() const {
            return const_iterator(*this, size());
        }
};