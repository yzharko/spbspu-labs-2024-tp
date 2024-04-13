#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using mihalchenko::DataStruct;
  std::vector<DataStruct> dataStruct;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator<mihalchenko::DataStruct>{std::cin},
      std::istream_iterator<mihalchenko::DataStruct>{},
      std::back_inserter(dataStruct));
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(dataStruct.begin(), dataStruct.end());
  std::copy(
    std::begin(dataStruct),
    std::end(dataStruct),
    std::ostream_iterator<mihalchenko::DataStruct>(std::cout, "\n"));
  return 0;
}
