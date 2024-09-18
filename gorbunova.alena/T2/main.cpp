#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "yaDataStruct.hpp"

int main()
{
  std::vector<gorbunova::YaDataStruct> data;
  while (!std::cin.eof())
  {
    std::copy(
        std::istream_iterator<gorbunova::YaDataStruct>(std::cin),
        std::istream_iterator<gorbunova::YaDataStruct>(),
        std::back_inserter(data));
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator<gorbunova::YaDataStruct>(std::cout, "\n"));
  return 0;
}
