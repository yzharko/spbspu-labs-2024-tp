#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include "datastruct.hpp"

int main()
{
  using namespace taskaev;
  std::vector < DataStruct > data;
  while(!std::cin.eof())
  {
    std::cin.clear();
    std::copy(
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct>(),
      std::back_inserter(data)
    );
    if(!std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
