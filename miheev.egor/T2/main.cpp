#include <iostream>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using namespace miheev;
  std::vector< DataStruct > data;
  std::copy(
    std::istream_iterator< DataStruct >{std::cin},
    std::istream_iterator< DataStruct >{},
    std::back_inserter(data)
  );
  std::cout << data[0] << '\n';

  return 0;
}
