#pragma once

/**
 * @brief Reference counted pointer (smart pointer)
 * @tparam T The data type
 */
template<typename T>
class shared_ptr {
    T* data;
    std::size_t* reference_count;
    public:
        /**
         * @param _data The data that the shared ptr now owns
         */
        shared_ptr(T* _data) : data(_data) {
            reference_count = new std::size_t(1);
        }

        /**
         * @param other The shared ptr to copy (but not the data)
         */
        shared_ptr(const shared_ptr& other) : data(other.data), reference_count(other.reference_count) {}

        ~shared_ptr() {
            *reference_count--;
            if (*reference_count == 0) {
                delete data;
                delete reference_count;
            }
        }

        /**
         * @brief Raw data getter
         */
        T* operator *() {
            return data;
        }

        /**
         * @brief Raw data getter
         */
        const T* operator *() const {
            return data;
        }
};