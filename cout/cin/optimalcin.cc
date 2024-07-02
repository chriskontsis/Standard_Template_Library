#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Data 
{
public:
    const inline bool isValid() 
    {
        return x > 0 && y > 0 && z > 0;
    }
    friend std::istream& operator>>(std::istream& is, Data& data) 
    {
        char commas;
        is >> data.x
           >> commas
           >> data.y
           >> commas
           >> data.z;

        if(!data.isValid())
            is.setstate(std::ios::failbit);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Data& data) 
    {
        os << data.x << ", "
           << data.y << ", "
           << data.z << '\n';
        return os;
    }
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
    // read header cuz we don't need
    readHeader(std::cin);
    
    // insert all of the data into the vector
    std::vector<Data> data;
    std::copy
    (
        std::istream_iterator<Data>{std::cin},
        std::istream_iterator<Data>{},
        std::back_inserter(data)
    );

    if(std::cin.fail()) 
    {
        std::cout << "Input incorrect >> [x,y,z] all need to be > 0 \n";
        return 0;
    }

    std::unordered_set<int> unusedData;
    std::unordered_map<int, Data> parentData;
    std::for_each(cbegin(data), cend(data), [&unusedData, &parentData](const Data& data) 
    {
        if(data.x != 0)
            parentData[data.x] = data;
        unusedData.insert(data.x);
    });

    
    std::vector<Data> output;
    std::copy
    (
        begin(data),
        end(data),
        std::ostream_iterator<Data>(std::cout, "-\n")
    );

}