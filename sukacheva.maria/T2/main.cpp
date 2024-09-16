#include <iosfwd>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
  using namespace sukacheva;
  std::vector< DataStruct > vectorOfData;
  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator< DataStruct >(std::cin), std::istream_iterator< DataStruct >(), std::back_inserter(vectorOfData));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(vectorOfData.begin(), vectorOfData.end());
  std::copy(vectorOfData.cbegin(), vectorOfData.cend(), std::ostream_iterator< DataStruct >{ std::cout, "\n" });

  return 0;
}
