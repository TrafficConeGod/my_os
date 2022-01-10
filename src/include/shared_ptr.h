#pragma once

template<typename T>
class shared_ptr {
    T* data;
    std::size_t* reference_count;
    public:
        shared_ptr(T* _data) : data(_data) {
            reference_count = new std::size_t(1);
        }
        shared_ptr(const shared_ptr& other) : data(other.data), reference_count(other.reference_count) {}

        ~shared_ptr() {
            *reference_count--;
            if (*reference_count == 0) {
                delete data;
                delete reference_count;
            }
        }

        T* operator *() {
            return data;
        }
        const T* operator *() const {
            return data;
        }
};