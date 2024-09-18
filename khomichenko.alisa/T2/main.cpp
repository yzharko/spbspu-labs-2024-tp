#include <limits>
#include <iterator>
#include <vector>
#include <algorithm>
#include "dataStruct.hpp"

int main()
{
  using namespace khomichenko;
  std::vector < DataStruct > vector;
  using input_t = std::istream_iterator< DataStruct >;
  using output_t = std::ostream_iterator< DataStruct >;
  while(!std::cin.eof())
  {
    std::copy (input_t{std::cin}, input_t{}, std::back_inserter(vector));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), output_t{std::cout, "\n"});
  return 0;
}
