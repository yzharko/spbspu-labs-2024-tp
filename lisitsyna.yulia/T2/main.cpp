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
    std::vector< Data > data;
    std::copy(
        std::istream_iterator<Data>(std::cin),
        std::istream_iterator<Data>(),
        std::back_inserter(data)
    );
    std::cout << "Data:\n";
    std::sort(data.begin(), data.end(), comp);
    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< Data >(std::cout, "\n")
    );
    return 0;
}
