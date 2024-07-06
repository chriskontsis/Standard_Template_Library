#include <cstring>
#include <utility>
#include <iostream>
#include <sstream>

class String {

    public:
        String() 
        : data {nullptr}
        , size {0}
        {}

        String(const char* other)
        : size ( strlen(other) )
        {
            std::cout << "String(const char*)\n";
            data = new char[size + 1];
            strcpy(data, other);
        }

        String(const String& other) 
        : size { other.size }
        {
            std::cout << "String(const String&)\n";
            data = new char[size+1];
            strcpy(data, other.data);
        }

        String(String&& other) noexcept 
        : String()
        {
            std::cout << "String(String&&)\n";
            swap(*this, other);
        }   

        ~String()
        {
            std::cout << "~String()\n";
            delete[] data;
        }

        String& operator=(String other)
        {
            std::cout << "String& operator=(String other)\n";
            swap(*this, other);
            return *this;
        }

        String& operator=(String&& other) noexcept
        {
            std::cout << "String& operator=(String&&)\n";
            swap(*this, other);
            return *this;
        }

        String operator+(const String& rhs) 
        {
            std::cout << "String operator+(const String& rhs)\n";
            size_t newLen = size + rhs.size + 1;
            char* newdata = new char[newLen];
            strcpy(newdata, data);
            strcat(newdata, rhs.data);
            String result(newdata);
            return result;
        }

        String& operator+=(const String& rhs) 
        {
            std::cout << "String& operator+=(const String& rhs)\n";
            size_t newLen = size + rhs.size + 1;
            char* newdata = new char[newLen];
            strcpy(newdata, data);
            strcat(newdata, rhs.data);
            delete[] data;
            data = newdata;
            size = newLen-1;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, String& str) 
        {
            os << str.data;
            return os;
        }

        friend void swap(String& a, String& b) {
            using std::swap;
            swap(a.size, b.size);
            swap(a.data, b.data);
        }


    private:
        char* data {nullptr};
        size_t size {0};
};

int main() {
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
    String s4;
    s4 = s3;
    std::cout << "s4: " << s4 << '\n';
    std::cout << "s3: " << s3 << "\n\n";
    // move assignment

    // String str2("World");
    // String s3 = str1 + " " + str2;
    // std::cout << s3 << '\n';

    // String s4(std::move(str2));
    // std::cout << s4 << '\n';

    // String s5 = str1;
    // std::cout << str1 << '\n';

    
}