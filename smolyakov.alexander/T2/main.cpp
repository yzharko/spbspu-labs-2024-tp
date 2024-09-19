#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "DataStruct.hpp"

int main()
{
  std::vector<smolyakov::DataStruct> data;

  while (!std::cin.eof())
  {
    std::copy(std::istream_iterator<smolyakov::DataStruct>{std::cin},
	std::istream_iterator<smolyakov::DataStruct>{},
	std::back_inserter(data));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore();
    }
  }

  std::cout << data[0].key3 << '\n';

  return 0;
}
