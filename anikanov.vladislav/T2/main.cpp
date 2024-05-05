#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "dataStruct.hpp"
#include "inOutPut.hpp"

#include "iofmtguard.cpp"
#include "dataStruct.cpp"

int main()
{
  using namespace anikanov;

  std::vector< DataStruct > dataStruct;

  while (std::cin.good()) {
    std::copy(
        std::istream_iterator< DataStruct >(std::cin),
        std::istream_iterator< DataStruct >(),
        std::back_inserter(dataStruct)
    );
    if (std::cin.fail() && !std::cin.eof()) {
      std::cin.clear();
      std::cin.ignore();
    }
  }

  std::sort(dataStruct.begin(), dataStruct.end());

  std::copy(
      std::begin(dataStruct),
      std::end(dataStruct),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
