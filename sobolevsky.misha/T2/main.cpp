#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
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
  }

  std::copy(
    vec.cbegin(),
    vec.cend(),
    std::ostream_iterator< sobolevsky::DataStruct >(std::cout, "\n")
  );

  return 0;
}
