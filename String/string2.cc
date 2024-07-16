#include <cstring>
#include <iostream>
#include <algorithm>
class String {
    public:
        String() 
        : data {nullptr}, length {0}
        {
            std::cout << "String()\n";
        }

        String(const char* other) 
        : length {strlen(other)}
        {
            std::cout << "const char* other\n";
            data =  new char[length + 1];
            strcpy(data, other);
        }

        String(const String& other)
        : length { other.length }
        {
            std::cout << "const String& other\n";
            data = new char[length+1];
            strcpy(data, other.data);
        }

        String(String&& other) noexcept
        : data { other.data }, length { other.length } 
        {
            std::cout << "String&& other\n";
            other.data = nullptr;
            other.length = 0;
        }

        String& operator=(String other) 
        {
            std::cout << "operator=(String other)\n";
            if(this != &other)
                swap(*this, other);
            return *this;
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
    // String()
    String s1;
    std::cout << "----\n";

    // const char *
    String s2("Hello");
    std::cout << "----\n";

    // const String& other
    String s3 = s2;
    std::cout << "----\n";

    // String&& other
    String s4 = std::move(s3);
    std::cout << "----\n";

    // copy assignment
    // String() then const String& other then operator=(String other)
    String s5;
    s5 = s4;

    std::cout << "----\n";
    // move assignment
    String s6;
    s6 = std::move(s4);
    std::cout << "----\n";
}