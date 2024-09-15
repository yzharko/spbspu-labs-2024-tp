#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
  using itInp = std::istream_iterator< zasulsky::DataStruct >;
  using itOut = std::ostream_iterator< zasulsky::DataStruct >;
  std::deque< zasulsky::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(itInp(std::cin), itInp(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), zasulsky::compare);
  std::copy(std::begin(data), std::end(data), itOut(std::cout, "\n"));
  return 0;
}
