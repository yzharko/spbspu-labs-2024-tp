#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <iterator>
#include <cassert>

int main()
{
    std::vector< DataStruct > data;
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );
    std::cout << "Data:\n";
    std::sort(data.begin(), data.end(), compare);
    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
    return 0;
}
