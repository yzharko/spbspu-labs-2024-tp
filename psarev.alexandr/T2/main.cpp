#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "dataStruct.hpp"

int main()
{
  std::vector< psarev::DataStruct > dataVec;

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< psarev::DataStruct >(std::cin),
      std::istream_iterator< psarev::DataStruct >(),
      std::back_inserter(dataVec)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(dataVec.begin(), dataVec.end());
  std::copy(
    std::begin(dataVec),
    std::end(dataVec),
    std::ostream_iterator< psarev::DataStruct >(std::cout, "\n")
  );

  return 0;
}
