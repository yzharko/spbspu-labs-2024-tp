#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "dataStruct.hpp"
#include "helpStructs.hpp"

int main()
{
  std::vector< sobolevsky::DataStruct > vec;

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< sobolevsky::DataStruct >{std::cin},
      std::istream_iterator< sobolevsky::DataStruct >{},
      std::back_inserter(vec)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(vec.begin(), vec.end());

  std::copy(
    vec.cbegin(),
    vec.cend(),
    std::ostream_iterator< sobolevsky::DataStruct >(std::cout, "\n")
  );

  return 0;
}
