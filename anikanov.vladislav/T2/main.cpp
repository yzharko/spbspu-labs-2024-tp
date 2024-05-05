#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "dataStruct.cpp"
#include "mainExtension.cpp"

int main()
{
  using namespace anikanov;

  std::vector< anikanov::DataStruct > dataStruct;

  while (std::cin.good())
  {
    std::copy(
        std::istream_iterator< anikanov::DataStruct >(std::cin),
        std::istream_iterator< anikanov::DataStruct >(),
        std::back_inserter(dataStruct)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore();
    }
  }

  std::sort(dataStruct.begin(), dataStruct.end(), anikanov::dataStructComparator);

  std::copy(
      std::begin(dataStruct),
      std::end(dataStruct),
      std::ostream_iterator< anikanov::DataStruct >(std::cout, "\n")
  );
  return 0;
}
