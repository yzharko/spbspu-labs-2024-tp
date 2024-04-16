#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "DataStruct.h"

int main()
{
  std::vector<DataStruct> dataVector;

  std::copy(std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(dataVector));

  std::sort(dataVector.begin(), dataVector.end());

  for (const auto& ds : dataVector)
  {
    std::cout << ds << (ds.key3.empty() ? "" : "\n");
  }

  return 0;
}
