#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DataStruct.hpp"

int main()
{
  using namespace lisitsyna;
  std::vector<Data> data;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy(
      std::istream_iterator<Data>(std::cin),
      std::istream_iterator<Data>(),
      std::back_inserter(data)
    );
  }
  std::sort(data.begin(), data.end());
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<Data>(std::cout, "\n")
  );
  return 0;
}
