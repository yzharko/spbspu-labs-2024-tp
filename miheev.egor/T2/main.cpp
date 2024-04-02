#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
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

  std::sort(data.begin(), data.end());

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  // std::cout << data[0] << '\n' << data[1] << '\n';

  return 0;
}
