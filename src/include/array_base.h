#pragma once
#include <cstddef>
#include "exception.h"
#include "debug.h"

template<typename S, typename T>
class array_base {
    inline T* data() const { return ((const S*)this)->base_data(); }
    inline std::size_t size() const { return ((const S*)this)->base_size(); }
    private:
        inline void in_range_check(std::size_t index) {
            if (!is_in_range(index)) {
                throw_index_out_of_bounds_exception(size(), index);
            }
        }
    public:
        inline T* get_data() { return data(); }
        inline const T* get_data() const { return data(); }
        inline std::size_t get_size() const { return size(); }

        inline bool is_in_range(std::size_t index) {
            return index < size();
        }

        T& operator[](std::size_t index) {
            in_range_check(index);
            return data()[index];
        }

        const T& operator[](std::size_t index) const {
            in_range_check(index);
            return data()[index];
        }


        
        class iterator {
            private:
                array_base& array_ref;
                size_t index;
            public:
                iterator(array_base& _array, size_t _index) : array_ref(_array), index(_index) {}

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
                const_iterator(const array_base& _array, size_t _index) : array_ref(_array), index(_index) {}

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