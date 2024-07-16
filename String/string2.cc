#include <cstring>
#include <iostream>



class String {
    public:
        String() 
        : data {nullptr}, length {0}
        {}

        String(const char* other) 
        : length {strlen(other)}
        {
            data =  new char[length + 1];
            strcpy(data, other);
        }


    private:
        char* data;
        std::size_t length;
};

int main() {

}