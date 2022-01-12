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
        /**
         * @brief Data pointer getter
         */
        inline T* get_data() { return data(); }
        /**
         * @brief Data pointer getter
         */
        inline const T* get_data() const { return data(); }
        /**
         * @brief Array size getter
         */
        inline std::size_t get_size() const { return size(); }

        /**
         * @brief Returns whether an index is in range of the array or not
         */
        inline bool is_in_range(std::size_t index) const {
            return index < size();
        }

        /**
         * @brief Throws exception if index is out of range
         */
        inline void in_range_check(std::size_t index) const {
            if (!is_in_range(index)) {
                throw_index_out_of_range_exception(size(), index);
            }
        }

        /**
         * @brief Safe getter of element at index
         */
        T& operator[](std::size_t index) {
            in_range_check(index);
            return data()[index];
        }

        /**
         * @brief Safe getter of element at index
         */
        const T& operator[](std::size_t index) const {
            in_range_check(index);
            return data()[index];
        }

        /**
         * @brief Safe getter of element of reinterpret casted type at index
         */
        template<typename U>
        U& at_as(std::size_t index) {
            in_range_check(index);
            in_range_check(index + sizeof(U) - 1);
            return (U&)data()[index];
        }


        /**
         * @brief Safe getter of element of reinterpret casted type at index
         */
        template<typename U>
        const U& at_as(std::size_t index) const {
            in_range_check(index);
            in_range_check(index + sizeof(U) - 1);
            return (const U&)data()[index];
        }

        /**
         * @brief Sets a range in array to a value
         * 
         * @param index The start index
         * @param count The amount of elements to set
         * @param value The value to set to
         */
        void set_range(std::size_t index, std::size_t count, const T& value) {
            in_range_check(index);
            in_range_check(index + count - 1);
            for (std::size_t i = index; i < (index + count); i++) {
                data()[i] = value;
            }
        }

        /**
         * @brief Copies a range in array from another array range
         * 
         * @param index The start index
         * @param count The size of both ranges
         * @param array The other array
         * @param other_index The start index of the other array
         */
        template<typename U>
        void copy_range(std::size_t index, std::size_t count, const U& array, std::size_t array_index) {
            in_range_check(index);
            in_range_check(index + count - 1);
            array.in_range_check(array_index);
            array.in_range_check(array_index + count - 1);
            for (std::size_t i = index; i < (index + count); i++) {
                data()[i] = array.get_data()[(array_index + i) - index];
            }
        }

        /**
         * @brief Compares a range in array to a value
         * 
         * @param index The start index
         * @param count The amount of elements to compare
         * @param value The value to compare to
         * @return true If the entire range equals value
         */
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

        /**
         * @brief Compares a range in array from another array range
         * 
         * @param index The start index
         * @param count The size of both ranges
         * @param array The other array
         * @param other_index The start index of the other array
         * @return true If both ranges are equal
         */
        template<typename U>
        bool compare_range_to_range(std::size_t index, std::size_t count, const U& array, std::size_t array_index) const {
            in_range_check(index);
            in_range_check(index + count - 1);
            array.in_range_check(array_index);
            array.in_range_check(array_index + count - 1);
            for (std::size_t i = index; i < (index + count); i++) {
                if (data()[i] != array.get_data()[(array_index + i) - index]) {
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