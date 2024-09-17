#include <algorithm>
#include <iterator>
#include <vector>
#include <limits>
#include "dataStruct.hpp"

int main()
{
  using malanin::yaDataStruct;
  std::vector< yaDataStruct > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< yaDataStruct >(std::cin),
      std::istream_iterator< yaDataStruct >(),
      std::back_inserter(data)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< yaDataStruct >(std::cout, "\n")
  );
  return 0;
}
\0
