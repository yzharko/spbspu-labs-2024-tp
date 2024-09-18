#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  std::vector< redko::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< redko::DataStruct >(std::cin),
      std::istream_iterator< redko::DataStruct >(),
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
    std::ostream_iterator< redko::DataStruct >(std::cout, "\n")
  );

  return 0;
}
