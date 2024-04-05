#include <iostream>
// #include <sstream>
#include <vector>
// #include <cctype>
#include <algorithm>
#include <limits>
#include <complex>
#include <iterator>
#include <string>
// #include <iomanip> // setpresition()
#include <stdlib.h>
#include <stdio.h>
#include "dataStruct.hpp"

int main()
{
  using mihalchenko::DataStruct;

  std::vector<DataStruct> dataStruct;

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator<mihalchenko::DataStruct>{std::cin},
      std::istream_iterator<mihalchenko::DataStruct>{},
      std::back_inserter(dataStruct));
    if (std::cin.fail() && !std::cin.eof())
    {
      // std::cout << "kjvkghvh" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(dataStruct.begin(), dataStruct.end());
  std::copy(
    std::begin(dataStruct),
    std::end(dataStruct),
    std::ostream_iterator<mihalchenko::DataStruct>(std::cout, "\n"));
  return 0;
}
