#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iterator>
#include "data_struct.hpp"

int main()
{
  using namespace kovshikov;
  using input_it = std::istream_iterator< DataStruct >;
  std::vector< DataStruct > data;

  while(!std::cin.eof())
  {
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(data));
    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  using output_it = std::ostream_iterator< DataStruct >;
  std::copy(data.cbegin(), data.cend(), output_it{std::cout, "\n"});

  return 0;
}
