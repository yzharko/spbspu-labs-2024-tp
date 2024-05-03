#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "yaDataStruct.hpp"

int main()
{
  using namespace hohlova;
  std::vector< Data > data;

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator<Data>{std::cin},
      std::istream_iterator<Data>{},
      std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<Data>(std::cout, "\n"));

  return 0;
}
