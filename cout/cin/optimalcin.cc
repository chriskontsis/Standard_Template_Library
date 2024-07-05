#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <format>


class DataManager
{

};
class Data 
{
public:
    const inline bool isNotValid() 
    {
        return x < 0 || y < 0 || z < 0;
    }
    friend std::istream& operator>>(std::istream& is, Data& data) 
    {
        char comma1, comma2;
        is >> data.x >> comma1
           >> data.y >> comma2
           >> data.z;

        if(data.isNotValid()) 
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

class JobChain {

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

    // data was formatted incorrectly 
    if(std::cin.fail() && !std::cin.eof()) 
    {
        std::cout << "Invalid input format >> [x,y,z]\n";
        return -1;
    }

    // add all unused data to set, make sure that no two job ids are the same using a flag
    std::unordered_set<int> unusedData;
    int duplicateJobId {0};
    std::ranges::for_each(std::as_const(data), [&unusedData, &duplicateJobId](const Data& data) 
    {
        if(unusedData.contains(data.x)) 
        {
            std::cout << std::format("Job with id {} has appeared more than once\n", data.x);
            duplicateJobId = 1;
            return;
        }
        unusedData.insert(data.x);
    });

    if(duplicateJobId) 
        return -1;

    //collect all of tha parents for each job
    std::unordered_map<int, Data> previousData;
    std::ranges::for_each(std::as_const(data), [&previousData](const Data& data)
    {
        if(data.x != 0)
            previousData[data.x] = data;
    });


    std::vector<JobChain> jobChains;


    
    std::copy
    (
        begin(data),
        end(data),
        std::ostream_iterator<Data>(std::cout, "-\n")
    );

}