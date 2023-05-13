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

    // Move Constructor
    String(String&& other) noexcept : s_length(0), s_data(nullptr) {
        swap(*this, other);
    }

    //Destructor
    ~String() {
        delete[] s_data;
    }

    //Copy Assignment
    String& operator=(const String& other) {
        String temp(other);
        swap(*this, temp);
        return *this;
    }
    
    // Move Assignment
    String& operator=(String&& other) {
        swap(*this, other);
        return *this;
    }

    int length() const {
        return s_length;
    }

    char& operator[](int idx) {
        return s_data[idx];
    }

    // declared friend because it needs to access private members of string class
    // swap is not a member function of the string class so it can't access them otherwise
    friend void swap(String& a, String& b) {
        using std::swap;
        swap(a.s_data, b.s_data);
        swap(a.s_length, b.s_length);
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str);
};