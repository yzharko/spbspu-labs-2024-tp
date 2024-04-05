#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
  std::vector< lisitsyna::DataStruct> data;
   while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      std::istream_iterator< lisitsyna::DataStruct >(std::cin),
      std::istream_iterator< lisitsyna::DataStruct >(),
      std::back_inserter(data)
    );
  }
  std::sort(std::begin(data), std::end(data));
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< lisitsyna::DataStruct >(std::cout, "\n")
  );
  return 0;
}
