#include <iterator>
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include "delimiter.hpp"
#include "datastruct.hpp"


int main()
{
  std::vector< sadofeva::DataStruct> data;
  while (!std::sin.eof())
  {
    std::copy(
      std::istream_iterator< sadofeva::DataStruct>{std::cin},
      std::istream_iterator< sadofeva::DataStruct>{},
      std::back_inserter(data)
    );
    if (!std::cin.good())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),"\n");
    }
  }
  std::sort(data.begin(),data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< sadofeva::DataStruct>(std::cout,"\n")
  );
  return 0;
}
