#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"

namespace panov
{
  int main()
  {
    std::vector<DataStruct> dataVec;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(dataVec));

    std::sort(dataVec.begin(), dataVec.end(), [](const DataStruct& lhs, const DataStruct& rhs)
      {
        if (lhs.key1 != rhs.key1)
        {
          return std::abs(lhs.key1) < std::abs(rhs.key1);
        }
        if (lhs.key2 != rhs.key2)
        {
          return lhs.key2 < rhs.key2;
        }
        return lhs.key3.size() < rhs.key3.size();
      });
    std::copy(dataVec.begin(), dataVec.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
  }
}
