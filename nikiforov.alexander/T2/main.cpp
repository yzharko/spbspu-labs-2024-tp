#include <iostream>
#include <iterator>
#include <vector>
#include <limits>
#include <algorithm>
#include "dataStruct.hpp"

int main()
{
  using structData = nikiforov::Data;

  std::vector< structData > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< structData >(std::cin),
      std::istream_iterator< structData >(),
      std::back_inserter(data)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< structData >(std::cout, "\n")
  );

  return 0;
}
