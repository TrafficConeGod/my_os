#include "array.h"

string::string() : unowned_array((char*)nullptr, 0) {}
string::string(const char* str) : unowned_array((char*)str, std::strlen(str)) {}