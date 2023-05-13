#include <iostream>
#include <cstring>

class String {
private:
    char *s_data;
    int s_length;
public:
    String(): s_length(0), s_data(nullptr) {}

    // Constructur with char array
    String(const char* str) {
        s_length = std::strlen(str);
        s_data = new char[s_length+1];
        std::strcpy(s_data, str);
    }

    // Copy Constructor
    String(const String& other) : String(other.s_data) {}

    String(String&& other) noexcept : s_length(0), s_data(nullptr) {
        swap(*this, other);
    }



    friend void swap(String& a, String& b) {
        using std::swap;
        swap(a.s_data, b.s_data);
        swap(a.s_length, b.s_length);
    }
};