#include <cstring>
#include <algorithm>
#include <iostream>

class String {
private:
    char* data;
    size_t size;

public:
    // Default constructor
    String() : data(nullptr), size(0) {
        std::cout << "Default constructor\n";
    }

    // Constructor from C-string
    String(const char* str) : size(strlen(str)) {
        std::cout << "Constructor from C-string\n";
        data = new char[size + 1];
        std::strcpy(data, str);
    }

    // Destructor
    ~String() {
        std::cout << "Destructor\n";
        delete[] data;
    }

    // Copy constructor
    String(const String& other) : size(other.size) {
        std::cout << "Copy constructor\n";
        data = new char[size + 1];
        std::strcpy(data, other.data);
    }

    // Move constructor
    String(String&& other) noexcept : data(other.data), size(other.size) {
        std::cout << "Move constructor\n";
        other.data = nullptr;
        other.size = 0;
    }

    // Copy assignment operator
    String& operator=(String other) {
        std::cout << "Copy assignment operator\n";
        swap(*this, other);
        return *this;
    }

    // Swap function
    friend void swap(String& first, String& second) noexcept {
        using std::swap;
        swap(first.data, second.data);
        swap(first.size, second.size);
    }

    // Utility functions
    size_t length() const { return size; }

    const char* c_str() const { return data; }

    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << (str.data ? str.data : "");
        return os;
    }
};

int main()
{
    // const char *
    String str1("Hello");
    std::cout << str1 << "\n\n";

    // copy construct
    String s2(str1);
    std::cout << s2 << "\n\n";

    // move construct
    String s3(std::move(s2));
    std::cout << s3 << "\n\n";

    // copy assignment
    String s4 = s3;
    std::cout << "s4: " << s4 << '\n';
    std::cout << "s3: " << s3 << "\n\n";

    // move assignment
    String s5;
    s5 = std::move(s4);
    std::cout << "s5: " << s5 << "\n\n";

}

