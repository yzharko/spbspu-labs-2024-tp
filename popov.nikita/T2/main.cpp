#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>
#include "dataStruct.hpp"

int main()
{
  std::vector< popov::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator<popov::DataStruct>{std::cin},
      std::istream_iterator<popov::DataStruct>{},
      std::back_inserter(data)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<popov::DataStruct>(std::cout, "\n")
  );
  return 0;
}
