#include <cstring>
#include <utility>
#include <iostream>

class String {
    private:
        char* data;
        int length;
    public:

        String(): data(nullptr), length(0) {}

        String(const char* other): length(strlen(other)){
            data = new char[length+1];
            strcpy(data, other);
        }

        String(const String& other) {
            String temp(other.data);
            swap(*this, temp);
        }

        ~String() {
            delete[] data;
        }

        String& operator=(const String& other) {
            String temp(other.data);
            swap(*this, temp);
            return *this;
        }


        String& operator+=(const String& other) {
            size_t new_length = length + strlen(other.data);
            char* newData = new char[new_length+1];
            strcpy(newData, data);
            strcat(newData, other.data);
            delete[] data;
            data = newData;
            length = new_length;
        }
        

        friend void swap(String& a,  String& b) {
            using std::swap;
            swap(a.data, b.data);
            swap(a.length, b.length);
        }

        friend std::ostream& operator<<(std::ostream& os, String& s) {
            os << s.data;
            return os;
        }

        friend std::istream& operator>>(std::istream& is, String& s) {
            is >> s.data;
            return is;
        }
};