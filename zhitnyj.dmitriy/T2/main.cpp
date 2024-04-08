#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include "DataStruct.h"

int main()
{
  std::vector<DataStruct> dataVector;

  std::copy(std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(dataVector));

  std::sort(dataVector.begin(), dataVector.end(), [](const DataStruct& a, const DataStruct& b)
  {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
  });

  for (const auto& ds : dataVector)
  {
    std::cout << ds << (ds.key3.empty() ? "" : "\n");
  }

  return 0;
}
