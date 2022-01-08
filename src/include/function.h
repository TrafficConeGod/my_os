#pragma once

template<typename X>
class function;

template<typename Return, typename... Args>
class function<Return(Args...)> {
    Return (*ptr)(Args...);
    public:
        function(Return (*_ptr)(Args...)) : ptr(_ptr) {}
        function(void* _ptr) : ptr((Return(*)(Args...))_ptr) {}
        function() : ptr(nullptr) {}
        inline Return operator()(Args... args) const { return ptr(args...); }

        inline operator bool() const { return ptr != nullptr; }

        template<typename T>
        inline operator T*() const { return (T*)ptr; }
};