#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"

int main(){
  std::vector< kaseev::DataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
        std::istream_iterator< kaseev::DataStruct >{std::cin},
        std::istream_iterator< kaseev::DataStruct >{},
        std::back_inserter(data)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator< kaseev::DataStruct >(std::cout, "\n")
  );
  return 0;
}
