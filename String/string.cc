#include <iostream>
#include <algorithm>
#include <cstddef>
#include <cstring>


class String {
    public:
        String() 
        : data {nullptr}, length {0} 
        {
            std::cout << "String()\n";
        }

        String(const char* other) 
        : length(std::strlen(other)) 
        {
            std::cout << "String(const char*)\n";
            data = new char[length + 1];
            std::copy(other, other+length+1, data);
        }

        String(const String& other) 
        : length {other.length}
        {
            std::cout << "String(const String& other)\n";
            data = new char[length + 1];
            std::copy(other.data, other.data+other.length+1, data);
        }

        String(String&& other) noexcept 
        : data{other.data}, length {other.length}
        {
            std::cout << "String(String&& other)\n";
            other.data = nullptr;
            other.length = 0;
        }

        ~String() 
        {
            std::cout << "~String()\n";
            delete[] data;    
        }

        String& operator=(String other) 
        {
            std::cout << "String operator=()\n";
            if(this != &other)
                swap(*this, other);
            return *this;
        }

        bool operator==(const String& rhs) const
        {
            if(this == &rhs) return true;
            if(length != rhs.length) return false;
            return std::strcmp(data, rhs.data) == 0;
        }

        friend std::ostream& operator<<(std::ostream& os, String& str)
        {
            os << str.data;
            return os;
        }

        friend void swap(String& lhs, String& rhs)
        {   
            using std::swap;
            swap(lhs.length, rhs.length);
            swap(lhs.data, rhs.data);
        }

    private:
        char* data;
        std::size_t length;
};


int main() {
    // Default ctor
    String s1;

    // const char *
    String s2("Hello");

    // copy ctor
    String s3(s2);

    // move ctor
    String s4(std::move(s3));

    // copy assn
    String s5;
    s5 = s4;

    // move assn
    String s6;
    s6 = std::move(s4);

    // equality check operator==
    std::cout << "Operator==\n";
    String s7 = s6;
    std::cout << std::boolalpha;
    std::cout << (s7 == s6) << '\n';
    String s8 = "World";
    std::cout << (s7 == s8) << '\n';
    
    // operator+

    // operator+=

    std::cout << '\n';
}