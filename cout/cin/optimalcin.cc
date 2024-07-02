#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

class Data 
{
public:
    friend std::istream& operator>>(std::istream& is, Data& data) 
    {
        char commas;
        is >> data.x
           >> commas
           >> data.y
           >> commas
           >> data.z;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Data& data) 
    {
        os << data.x << ", "
           << data.y << ", "
           << data.z << '\n';
        return os;
    }

private:
    int x;
    int y;
    int z;
};

void readHeader(std::istream& is) 
{
    std::string header;
    getline(is, header);
}

int main()
{
    readHeader(std::cin);
    std::vector<Data> data;
    std::copy
    (
        std::istream_iterator<Data>{std::cin},
        std::istream_iterator<Data>{},
        std::back_inserter(data)
    );

    
    std::vector<Data> output;
    std::copy
    (
        begin(data),
        end(data),
        std::ostream_iterator<Data>(std::cout, "-\n")
    );

}