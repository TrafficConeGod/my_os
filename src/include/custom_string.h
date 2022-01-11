#pragma once
#include "unowned_array.h"

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