#include "dataStruct.hpp"
#include "comparator.hpp"
#include <algorithm>
#include <iterator>
#include <vector>
#include <limits>

// формат ввода:
// (:key1 5.45e-2:key2 0b1000101:key3 "Data":)

int main()
{
  using ponomarev::Data;
  std::vector< Data > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< Data >(std::cin),
      std::istream_iterator< Data >(),
      std::back_inserter(data)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), ponomarev::compare_entry);
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< Data >(std::cout, "\n")
  );

  return 0;
}
