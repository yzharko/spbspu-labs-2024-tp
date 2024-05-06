#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
  std::vector< DataStruct > dataVector;

  while(!std::cin.eof())
  {
    std::copy(std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(dataVector));
    if(std::cin.rdstate() == std::ios::failbit)
    {
      std::cin.clear();
    }
  }

  std::sort(dataVector.begin(), dataVector.end());

  for (const auto& ds : dataVector)
  {
    std::cout << ds << "\n";
  }

  return 0;
}
